#!/usr/bin/env pwsh
# Windows-/PowerShell-вариант tests/verify.sh:
# генерирует примеры программ и компилирует каждую её реальным тулчейном,
# доказывая требование — весь сгенерированный код должен компилироваться без ошибок.

$ErrorActionPreference = 'Stop'

$Root = Split-Path -Parent $PSScriptRoot
$Work = Join-Path $Root '.codegen-tmp'

if (Test-Path $Work) { Remove-Item -Recurse -Force $Work }
New-Item -ItemType Directory -Force -Path $Work | Out-Null

$fail = 0
function Pass($m) { Write-Host "  PASS $m" -ForegroundColor Green }
function Bad($m)  { Write-Host "  FAIL $m" -ForegroundColor Red; $script:fail = 1 }

function Need($exe) { $null -ne (Get-Command $exe -ErrorAction SilentlyContinue) }

$emitExe = Join-Path $Work 'emit.exe'
$sources = @(
    (Join-Path $Root 'tools/emit.cpp'),
    (Join-Path $Root 'examples.cpp')
) + (Get-ChildItem -Path (Join-Path $Root 'src') -Filter '*.cpp').FullName `
  + (Get-ChildItem -Path (Join-Path $Root 'src') -Directory |
        ForEach-Object { (Get-ChildItem -Path $_.FullName -Filter '*.cpp').FullName })

Write-Host '==> Building the generator and emitting sample sources'
& g++ -std=c++17 -I "$(Join-Path $Root 'src')" -I "$Root" -o $emitExe @sources
if ($LASTEXITCODE -ne 0) { exit 1 }
& $emitExe (Join-Path $Work 'out')
if ($LASTEXITCODE -ne 0) { exit 1 }

Write-Host '==> C++ (g++ -std=c++17)'
& g++ -std=c++17 -fsyntax-only (Join-Path $Work 'out/cpp/MyClass.cpp')
if ($LASTEXITCODE -eq 0) { Pass 'cpp/MyClass.cpp' } else { Bad 'cpp/MyClass.cpp' }

Write-Host '==> Java (javac)'
if (Need 'javac') {
    $classes = Join-Path $Work 'out/java/classes'
    $javaFiles = (Get-ChildItem -Path (Join-Path $Work 'out/java') -Filter '*.java').FullName
    & javac -d $classes @javaFiles
    if ($LASTEXITCODE -eq 0) { Pass 'java/*.java' } else { Bad 'java/*.java' }
} else {
    Write-Host '  SKIP javac not found'
}

Write-Host '==> C# (dotnet build, library)'
if (Need 'dotnet') {
    $proj = Join-Path $Work 'out/csharp'
    @'
<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <TargetFramework>net8.0</TargetFramework>
    <OutputType>Library</OutputType>
    <Nullable>disable</Nullable>
    <ImplicitUsings>disable</ImplicitUsings>
  </PropertyGroup>
</Project>
'@ | Set-Content -Path (Join-Path $proj 'Gen.csproj')
    $log = Join-Path $Work 'csharp.log'
    & dotnet build $proj -nologo > $log 2>&1
    if ($LASTEXITCODE -eq 0) { Pass 'csharp/*.cs' } else { Bad 'csharp/*.cs'; Get-Content $log }
} else {
    Write-Host '  SKIP dotnet not found'
}

Write-Host ''
if ($fail -eq 0) {
    Write-Host 'All generated programs compiled successfully.'
} else {
    Write-Host 'Some generated programs failed to compile.'
}
exit $fail
