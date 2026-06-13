/**
 * @file emit.cpp
 * @brief Запись сгенерированных программ на диск для проверки компиляции.
 *
 * Помещает вывод генератора в файлы, чтобы tests/verify.sh мог передать их
 * настоящим компиляторам C++, C# и Java. Использование: emit <каталог-вывода>
 */

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

/**
 * @brief Записать строку в файл, создав при необходимости родительские каталоги.
 * @param path    Путь к файлу.
 * @param content Содержимое файла.
 */
void writeFile( const fs::path& path, const std::string& content ) {
    fs::create_directories( path.parent_path() );
    std::ofstream out( path );
    out << content;
}

} // namespace

/**
 * @brief Точка входа утилиты.
 * @param argc Число аргументов.
 * @param argv Аргументы; argv[1] — каталог для записи результатов.
 * @return Код возврата процесса.
 */
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
    writeFile( root / "cpp" / "MyClass.cpp",
               "#include <cstdio>\n\n" + generateProgram( cppFactory ) );

    // C#: библиотека классов, по одному типу на файл.
    writeFile( root / "csharp" / "MyClass.cs", generateProgram( csharpFactory ) );
    writeFile( root / "csharp" / "CSharpShowcase.cs", generateCSharpShowcase( csharpFactory ) );

    // Java: один класс на файл, имя файла совпадает с именем класса.
    writeFile( root / "java" / "MyClass.java", generateProgram( javaFactory ) );
    writeFile( root / "java" / "JavaShowcase.java", generateJavaShowcase( javaFactory ) );

    std::cout << "emitted generated sources into " << root << "\n";
    return 0;
}
