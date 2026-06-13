#pragma once

#include "codegen/factory.hpp"
#include "codegen/java/java_units.hpp"

namespace codegen::java {

// Concrete factory producing the Java family of Units.
class JavaFactory : public AbstractFactory {
public:
    std::shared_ptr< ClassUnit > createClass(
        const std::string& name, Flags flags = 0 ) const override {
        return std::make_shared< JavaClassUnit >( name, flags );
    }

    std::shared_ptr< MethodUnit > createMethod(
        const std::string& name, const std::string& returnType, Flags flags = 0 ) const override {
        return std::make_shared< JavaMethodUnit >( name, returnType, flags );
    }

    std::shared_ptr< FieldUnit > createField(
        const std::string& name, const std::string& type, Flags flags = 0 ) const override {
        return std::make_shared< JavaFieldUnit >( name, type, flags );
    }

    std::shared_ptr< PrintOperatorUnit > createPrintOperator(
        const std::string& text ) const override {
        return std::make_shared< JavaPrintOperatorUnit >( text );
    }
};

} // namespace codegen::java
