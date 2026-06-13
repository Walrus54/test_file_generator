#pragma once

#include "codegen/cpp/cpp_units.hpp"
#include "codegen/factory.hpp"

namespace codegen::cpp {

// Concrete factory producing the C++ family of Units.
class CppFactory : public AbstractFactory {
public:
    std::shared_ptr< ClassUnit > createClass(
        const std::string& name, Flags flags = 0 ) const override {
        return std::make_shared< CppClassUnit >( name, flags );
    }

    std::shared_ptr< MethodUnit > createMethod(
        const std::string& name, const std::string& returnType, Flags flags = 0 ) const override {
        return std::make_shared< CppMethodUnit >( name, returnType, flags );
    }

    std::shared_ptr< FieldUnit > createField(
        const std::string& name, const std::string& type, Flags flags = 0 ) const override {
        return std::make_shared< CppFieldUnit >( name, type, flags );
    }

    std::shared_ptr< PrintOperatorUnit > createPrintOperator(
        const std::string& text ) const override {
        return std::make_shared< CppPrintOperatorUnit >( text );
    }
};

} // namespace codegen::cpp
