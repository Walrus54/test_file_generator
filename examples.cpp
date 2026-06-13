/// @file examples.cpp
/// @brief Реализация обобщённого сборщика и демо-спецификаций.
#include "examples.h"

namespace codegen {

std::string buildClass( const AbstractFactory& factory, const ClassSpec& spec ) {
    auto classUnit = factory.createClass( spec.name, spec.classFlags );

    for( const auto& method : spec.methods ) {
        auto methodUnit = factory.createMethod( method.name, method.returnType, method.flags );
        for( const auto& text : method.prints ) {
            methodUnit->add( factory.createPrintOperator( text ) );
        }
        classUnit->add( methodUnit, method.access );
    }

    return classUnit->compile();
}

ClassSpec programSpec() {
    return {
        "MyClass",
        CM_UNKNOWN,
        {
            { "testFunc1", "void", 0, PUBLIC, {} },
            { "testFunc2", "void", MM_STATIC, PRIVATE, {} },
            { "testFunc3", "void", MM_VIRTUAL | MM_CONST, PUBLIC, {} },
            { "testFunc4", "void", MM_STATIC, PROTECTED, { "Hello, world!\n" } },
        },
    };
}

ClassSpec csharpShowcaseSpec() {
    // abstract-класс с abstract/virtual/static методами и C#-модификаторами доступа.
    return {
        "CSharpShowcase",
        CM_ABSTRACT,
        {
            { "Process", "void", MM_ABSTRACT, PUBLIC, {} },
            { "Render", "void", MM_VIRTUAL, PUBLIC, { "render" } },
            { "Helper", "void", MM_STATIC, PRIVATE, {} },
            { "Internal", "void", 0, INTERNAL, {} },
            { "Mixed", "void", 0, PROTECTED_INTERNAL, {} },
            { "Restricted", "void", 0, PRIVATE_PROTECTED, {} },
        },
    };
}

ClassSpec javaShowcaseSpec() {
    // abstract-класс с abstract/final/static методами и package-private доступом.
    return {
        "JavaShowcase",
        CM_ABSTRACT,
        {
            { "process", "void", MM_ABSTRACT, PUBLIC, {} },
            { "render", "void", MM_FINAL, PUBLIC, { "render" } },
            { "helper", "void", MM_STATIC, PUBLIC, {} },
            { "packageLocal", "void", 0, ACCESS_UNKNOWN, {} },
        },
    };
}

} // namespace codegen
