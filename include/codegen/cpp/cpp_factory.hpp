#pragma once

/**
 * @file cpp_factory.hpp
 * @brief Конкретная фабрика узлов для языка C++.
 */

#include "codegen/cpp/cpp_units.hpp"
#include "codegen/factory.hpp"

namespace codegen::cpp {

/**
 * @brief Конкретная фабрика, порождающая семейство узлов C++.
 */
class CppFactory : public AbstractFactory {
public:
    /// @copydoc AbstractFactory::createClass
    std::shared_ptr< ClassUnit > createClass(
        const std::string& name, Flags flags = 0 ) const override {
        return std::make_shared< CppClassUnit >( name, flags );
    }

    /// @copydoc AbstractFactory::createMethod
    std::shared_ptr< MethodUnit > createMethod(
        const std::string& name, const std::string& returnType, Flags flags = 0 ) const override {
        return std::make_shared< CppMethodUnit >( name, returnType, flags );
    }

    /// @copydoc AbstractFactory::createField
    std::shared_ptr< FieldUnit > createField(
        const std::string& name, const std::string& type, Flags flags = 0 ) const override {
        return std::make_shared< CppFieldUnit >( name, type, flags );
    }

    /// @copydoc AbstractFactory::createPrintOperator
    std::shared_ptr< PrintOperatorUnit > createPrintOperator(
        const std::string& text ) const override {
        return std::make_shared< CppPrintOperatorUnit >( text );
    }
};

} // namespace codegen::cpp
