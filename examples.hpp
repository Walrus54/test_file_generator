#pragma once

/**
 * @file examples.hpp
 * @brief Переиспользуемые сборщики демонстрационных программ.
 *
 * Все сборщики зависят только от AbstractFactory, поэтому один и тот же код даёт
 * программу на C++, C# или Java в зависимости от переданной фабрики.
 */

#include <string>

#include "codegen/factory.hpp"

namespace codegen {

/**
 * @brief Переносимая демо-программа из лабораторной работы.
 *
 * Строит класс MyClass только через AbstractFactory, поэтому идентичный вызов
 * порождает C++, C# или Java.
 * @param factory Конкретная фабрика целевого языка.
 * @return Сгенерированный текст программы.
 */
inline std::string generateProgram( const AbstractFactory& factory ) {
    auto myClass = factory.createClass( "MyClass" );

    myClass->add( factory.createMethod( "testFunc1", "void", 0 ), PUBLIC );
    myClass->add( factory.createMethod( "testFunc2", "void", MM_STATIC ), PRIVATE );
    myClass->add( factory.createMethod( "testFunc3", "void", MM_VIRTUAL | MM_CONST ), PUBLIC );

    auto method = factory.createMethod( "testFunc4", "void", MM_STATIC );
    method->add( factory.createPrintOperator( R"(Hello, world!\n)" ) );
    myClass->add( method, PROTECTED );

    return myClass->compile();
}

/**
 * @brief Демонстрация модификаторов класса и метода, специфичных для C#.
 *
 * Результат компилируется как библиотека C#.
 * @param factory Фабрика C#.
 * @return Сгенерированный текст класса-демонстрации.
 */
inline std::string generateCSharpShowcase( const AbstractFactory& factory ) {
    auto showcase = factory.createClass( "CSharpShowcase", CM_ABSTRACT | CM_PARTIAL );

    showcase->add( factory.createMethod( "Process", "void", MM_ABSTRACT ), PUBLIC );

    auto render = factory.createMethod( "Render", "void", MM_VIRTUAL );
    render->add( factory.createPrintOperator( "render" ) );
    showcase->add( render, PUBLIC );

    showcase->add( factory.createMethod( "Helper", "void", MM_STATIC ), PRIVATE );
    showcase->add( factory.createMethod( "Tick", "void", MM_ASYNC ), INTERNAL );
    showcase->add( factory.createMethod( "Reset", "void", 0 ), PROTECTED_INTERNAL );

    return showcase->compile();
}

/**
 * @brief Демонстрация модификаторов класса и метода, специфичных для Java.
 *
 * Результат компилируется компилятором javac.
 * @param factory Фабрика Java.
 * @return Сгенерированный текст класса-демонстрации.
 */
inline std::string generateJavaShowcase( const AbstractFactory& factory ) {
    auto showcase = factory.createClass( "JavaShowcase", CM_ABSTRACT | CM_STRICTFP );

    showcase->add( factory.createMethod( "process", "void", MM_ABSTRACT ), PUBLIC );

    auto render = factory.createMethod( "render", "void", MM_FINAL );
    render->add( factory.createPrintOperator( "render" ) );
    showcase->add( render, PUBLIC );

    showcase->add( factory.createMethod( "helper", "void", MM_STATIC ), PUBLIC );
    showcase->add( factory.createMethod( "lowLevel", "void", MM_NATIVE ), PROTECTED );
    showcase->add( factory.createMethod( "packageLocal", "void", 0 ), PACKAGE_PRIVATE );

    return showcase->compile();
}

} // namespace codegen
