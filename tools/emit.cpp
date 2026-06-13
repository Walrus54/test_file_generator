// Writes every generated program to disk so that tests/verify.sh can feed the
// output to the real C++, C# and Java compilers. Usage: emit <output-dir>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "codegen/cpp/cpp_factory.hpp"
#include "codegen/csharp/csharp_factory.hpp"
#include "codegen/java/java_factory.hpp"
#include "examples.hpp"

using namespace codegen;
namespace fs = std::filesystem;

namespace {

void writeFile( const fs::path& path, const std::string& content ) {
    fs::create_directories( path.parent_path() );
    std::ofstream out( path );
    out << content;
}

} // namespace

int main( int argc, char** argv ) {
    if( argc < 2 ) {
        std::cerr << "usage: emit <output-dir>\n";
        return 1;
    }
    fs::path root( argv[ 1 ] );

    cpp::CppFactory cppFactory;
    csharp::CSharpFactory csharpFactory;
    java::JavaFactory javaFactory;

    // C++: printf needs a declaration for the translation unit to compile.
    writeFile( root / "cpp" / "MyClass.cpp",
               "#include <cstdio>\n\n" + generateProgram( cppFactory ) );

    // C#: a class library, one type per file.
    writeFile( root / "csharp" / "MyClass.cs", generateProgram( csharpFactory ) );
    writeFile( root / "csharp" / "CSharpShowcase.cs", generateCSharpShowcase( csharpFactory ) );

    // Java: one class per file, file name matches the class name.
    writeFile( root / "java" / "MyClass.java", generateProgram( javaFactory ) );
    writeFile( root / "java" / "JavaShowcase.java", generateJavaShowcase( javaFactory ) );

    std::cout << "emitted generated sources into " << root << "\n";
    return 0;
}
