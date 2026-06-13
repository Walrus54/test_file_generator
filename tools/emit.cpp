/// @file emit.cpp
/// @brief Запись сгенерированных программ на диск для проверки компиляции.
///
/// Использование: emit <каталог-вывода>
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

/// @brief Записать строку в файл, создав родительские каталоги.
void writeFile( const fs::path& path, const std::string& content ) {
    fs::create_directories( path.parent_path() );
    std::ofstream out( path );
    out << content;
}

} // namespace

/// @brief Точка входа утилиты.
/// @param argc Число аргументов.
/// @param argv argv[1] — каталог для записи результатов.
int main( int argc, char** argv ) {
    if( argc < 2 ) {
        std::cerr << "usage: emit <output-dir>\n";
        return 1;
    }
    fs::path root( argv[ 1 ] );

    cpp::CppFactory cppFactory;
    csharp::CSharpFactory csharpFactory;
    java::JavaFactory javaFactory;

    // C++: для компиляции единицы трансляции printf требуется объявление.
    writeFile( root / "cpp" / "MyClass.cpp", "#include <cstdio>\n\n" + generateProgram( cppFactory ) );

    // C#: библиотека классов, по одному типу на файл.
    writeFile( root / "csharp" / "MyClass.cs", generateProgram( csharpFactory ) );
    writeFile( root / "csharp" / "CSharpShowcase.cs", generateCSharpShowcase( csharpFactory ) );

    // Java: один класс на файл, имя файла совпадает с именем класса.
    writeFile( root / "java" / "MyClass.java", generateProgram( javaFactory ) );
    writeFile( root / "java" / "JavaShowcase.java", generateJavaShowcase( javaFactory ) );

    std::cout << "emitted generated sources into " << root << "\n";
    return 0;
}
