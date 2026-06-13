#!/usr/bin/env bash
# Generates the sample programs and compiles each with its real toolchain to
# prove the requirement: every generated program must compile without errors.
set -u

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
WORK="${ROOT}/.codegen-tmp"

rm -rf "${WORK}"
mkdir -p "${WORK}"

fail=0
pass() { printf '  \033[32mPASS\033[0m %s\n' "$1"; }
bad()  { printf '  \033[31mFAIL\033[0m %s\n' "$1"; fail=1; }

echo "==> Building the generator and emitting sample sources"
g++ -std=c++17 -I "${ROOT}/src" -I "${ROOT}" -o "${WORK}/emit" \
    "${ROOT}/tools/emit.cpp" "${ROOT}/examples.cpp" "${ROOT}"/src/*.cpp "${ROOT}"/src/*/*.cpp || exit 1
"${WORK}/emit" "${WORK}/out" || exit 1

echo "==> C++ (g++ -std=c++17)"
if g++ -std=c++17 -fsyntax-only "${WORK}/out/cpp/MyClass.cpp"; then
    pass "cpp/MyClass.cpp"
else
    bad "cpp/MyClass.cpp"
fi

echo "==> Java (javac)"
if command -v javac >/dev/null; then
    if javac -d "${WORK}/out/java/classes" "${WORK}"/out/java/*.java; then
        pass "java/*.java"
    else
        bad "java/*.java"
    fi
else
    echo "  SKIP javac not found"
fi

echo "==> C# (dotnet build, library)"
if command -v dotnet >/dev/null; then
    proj="${WORK}/out/csharp"
    cat > "${proj}/Gen.csproj" <<'EOF'
<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <TargetFramework>net8.0</TargetFramework>
    <OutputType>Library</OutputType>
    <Nullable>disable</Nullable>
    <ImplicitUsings>disable</ImplicitUsings>
  </PropertyGroup>
</Project>
EOF
    if dotnet build "${proj}" -nologo >/dev/null 2>"${WORK}/csharp.log"; then
        pass "csharp/*.cs"
    else
        bad "csharp/*.cs"
        cat "${WORK}/csharp.log"
    fi
else
    echo "  SKIP dotnet not found"
fi

echo
if [ "${fail}" -eq 0 ]; then
    echo "All generated programs compiled successfully."
else
    echo "Some generated programs failed to compile."
fi
exit "${fail}"
