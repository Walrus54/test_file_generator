// Запись сгенерированных программ на диск для проверки компиляции.
// Использование: emit <каталог-вывода>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "cpp/cpp_factory.h"
#include "csharp/csharp_factory.h"
#include "examples.h"
#include "java/java_factory.h"

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

    const ClassSpec program = programSpec();

    // C++: для компиляции единицы трансляции printf требуется объявление.
    writeFile( root / "cpp" / "MyClass.cpp", "#include <cstdio>\n\n" + buildClass( cppFactory, program ) );

    // C#: библиотека классов, по одному типу на файл.
    writeFile( root / "csharp" / "MyClass.cs", buildClass( csharpFactory, program ) );
    writeFile( root / "csharp" / "CSharpShowcase.cs", buildClass( csharpFactory, csharpShowcaseSpec() ) );

    // Java: один класс на файл, имя файла совпадает с именем класса.
    writeFile( root / "java" / "MyClass.java", buildClass( javaFactory, program ) );
    writeFile( root / "java" / "JavaShowcase.java", buildClass( javaFactory, javaShowcaseSpec() ) );

    std::cout << "emitted generated sources into " << root << "\n";
    return 0;
}
