/// @file main.cpp
/// @brief Точка входа: демонстрация генерации программ на C++, C# и Java.
#include <iostream>

#include "cpp/cpp_factory.h"
#include "csharp/csharp_factory.h"
#include "examples.h"
#include "java/java_factory.h"

using namespace codegen;

namespace {

/// @brief Напечатать озаглавленный блок сгенерированного кода.
void printSection( const std::string& title, const std::string& code ) {
    std::cout << "// ===== " << title << " =====\n" << code << "\n";
}

} // namespace

/// @brief Точка входа программы.
int main() {
    cpp::CppFactory cppFactory;
    csharp::CSharpFactory csharpFactory;
    java::JavaFactory javaFactory;

    // Один и тот же вызов generateProgram() порождает все три языка.
    printSection( cppFactory.languageName() + " : MyClass", generateProgram( cppFactory ) );
    printSection( csharpFactory.languageName() + "  : MyClass", generateProgram( csharpFactory ) );
    printSection( javaFactory.languageName() + " : MyClass", generateProgram( javaFactory ) );

    // Демонстрации модификаторов, специфичных для каждого языка.
    printSection( csharpFactory.languageName() + "  : modifier showcase", generateCSharpShowcase( csharpFactory ) );
    printSection( javaFactory.languageName() + " : modifier showcase", generateJavaShowcase( javaFactory ) );

    return 0;
}
