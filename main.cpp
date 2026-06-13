#include <iostream>

#include "codegen/cpp/cpp_factory.hpp"
#include "codegen/factory.hpp"

using namespace codegen;

// Language-agnostic program builder: it only talks to the AbstractFactory, so
// the very same code generates C++, C# or Java depending on which concrete
// factory it is handed.
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

int main() {
    cpp::CppFactory cppFactory;
    std::cout << generateProgram( cppFactory ) << std::endl;
    return 0;
}
