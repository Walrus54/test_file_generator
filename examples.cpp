/// @file examples.cpp
/// @brief Реализация сборщиков демонстрационных программ.
#include "examples.h"

namespace codegen {

std::string generateProgram( const AbstractFactory& factory ) {
    auto myClass = factory.createClass( "MyClass" );

    myClass->add( factory.createMethod( "testFunc1", "void", 0 ), PUBLIC );
    myClass->add( factory.createMethod( "testFunc2", "void", MM_STATIC ), PRIVATE );
    myClass->add( factory.createMethod( "testFunc3", "void", MM_VIRTUAL | MM_CONST ), PUBLIC );

    auto method = factory.createMethod( "testFunc4", "void", MM_STATIC );
    method->add( factory.createPrintOperator( R"(Hello, world!\n)" ) );
    myClass->add( method, PROTECTED );

    return myClass->compile();
}

std::string generateCSharpShowcase( const AbstractFactory& factory ) {
    // abstract-класс с abstract/virtual/static методами и C#-модификаторами доступа.
    auto showcase = factory.createClass( "CSharpShowcase", CM_ABSTRACT );

    showcase->add( factory.createMethod( "Process", "void", MM_ABSTRACT ), PUBLIC );

    auto render = factory.createMethod( "Render", "void", MM_VIRTUAL );
    render->add( factory.createPrintOperator( "render" ) );
    showcase->add( render, PUBLIC );

    showcase->add( factory.createMethod( "Helper", "void", MM_STATIC ), PRIVATE );
    showcase->add( factory.createMethod( "Internal", "void", 0 ), INTERNAL );
    showcase->add( factory.createMethod( "Mixed", "void", 0 ), PROTECTED_INTERNAL );
    showcase->add( factory.createMethod( "Restricted", "void", 0 ), PRIVATE_PROTECTED );

    return showcase->compile();
}

std::string generateJavaShowcase( const AbstractFactory& factory ) {
    // abstract-класс с abstract/final/static методами и package-private доступом.
    auto showcase = factory.createClass( "JavaShowcase", CM_ABSTRACT );

    showcase->add( factory.createMethod( "process", "void", MM_ABSTRACT ), PUBLIC );

    auto render = factory.createMethod( "render", "void", MM_FINAL );
    render->add( factory.createPrintOperator( "render" ) );
    showcase->add( render, PUBLIC );

    showcase->add( factory.createMethod( "helper", "void", MM_STATIC ), PUBLIC );
    showcase->add( factory.createMethod( "packageLocal", "void", 0 ), ACCESS_UNKNOWN );

    return showcase->compile();
}

} // namespace codegen
