/**
 * @file main.cpp
 * @brief Точка входа: демонстрация генерации программ на C++, C# и Java.
 */

#include <iostream>

#include "codegen/cpp/cpp_factory.hpp"
#include "codegen/csharp/csharp_factory.hpp"
#include "codegen/java/java_factory.hpp"
#include "examples.hpp"

using namespace codegen;

namespace {

/**
 * @brief Напечатать озаглавленный блок сгенерированного кода.
 * @param title Заголовок блока.
 * @param code  Сгенерированный код.
 */
void printSection( const std::string& title, const std::string& code ) {
    std::cout << "// ===== " << title << " =====\n" << code << "\n";
}

} // namespace

/**
 * @brief Точка входа программы.
 * @return Код возврата процесса.
 */
int main() {
    cpp::CppFactory cppFactory;
    csharp::CSharpFactory csharpFactory;
    java::JavaFactory javaFactory;

    // Один и тот же вызов generateProgram() порождает все три языка.
    printSection( "C++  : MyClass", generateProgram( cppFactory ) );
    printSection( "C#   : MyClass", generateProgram( csharpFactory ) );
    printSection( "Java : MyClass", generateProgram( javaFactory ) );

    // Демонстрации модификаторов, специфичных для каждого языка.
    printSection( "C#   : modifier showcase", generateCSharpShowcase( csharpFactory ) );
    printSection( "Java : modifier showcase", generateJavaShowcase( javaFactory ) );

    return 0;
}
