#pragma once

#include "codegen/csharp/csharp_units.hpp"
#include "codegen/factory.hpp"

namespace codegen::csharp {

// Concrete factory producing the C# family of Units.
class CSharpFactory : public AbstractFactory {
public:
    std::shared_ptr< ClassUnit > createClass(
        const std::string& name, Flags flags = 0 ) const override {
        return std::make_shared< CSharpClassUnit >( name, flags );
    }

    std::shared_ptr< MethodUnit > createMethod(
        const std::string& name, const std::string& returnType, Flags flags = 0 ) const override {
        return std::make_shared< CSharpMethodUnit >( name, returnType, flags );
    }

    std::shared_ptr< FieldUnit > createField(
        const std::string& name, const std::string& type, Flags flags = 0 ) const override {
        return std::make_shared< CSharpFieldUnit >( name, type, flags );
    }

    std::shared_ptr< PrintOperatorUnit > createPrintOperator(
        const std::string& text ) const override {
        return std::make_shared< CSharpPrintOperatorUnit >( text );
    }
};

} // namespace codegen::csharp
