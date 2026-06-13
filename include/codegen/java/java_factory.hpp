#pragma once

/**
 * @file java_factory.hpp
 * @brief Конкретная фабрика узлов для языка Java.
 */

#include "codegen/factory.hpp"
#include "codegen/java/java_units.hpp"

namespace codegen::java {

/**
 * @brief Конкретная фабрика, порождающая семейство узлов Java.
 */
class JavaFactory : public AbstractFactory {
public:
    /// @copydoc AbstractFactory::createClass
    std::shared_ptr< ClassUnit > createClass(
        const std::string& name, Flags flags = 0 ) const override {
        return std::make_shared< JavaClassUnit >( name, flags );
    }

    /// @copydoc AbstractFactory::createMethod
    std::shared_ptr< MethodUnit > createMethod(
        const std::string& name, const std::string& returnType, Flags flags = 0 ) const override {
        return std::make_shared< JavaMethodUnit >( name, returnType, flags );
    }

    /// @copydoc AbstractFactory::createField
    std::shared_ptr< FieldUnit > createField(
        const std::string& name, const std::string& type, Flags flags = 0 ) const override {
        return std::make_shared< JavaFieldUnit >( name, type, flags );
    }

    /// @copydoc AbstractFactory::createPrintOperator
    std::shared_ptr< PrintOperatorUnit > createPrintOperator(
        const std::string& text ) const override {
        return std::make_shared< JavaPrintOperatorUnit >( text );
    }
};

} // namespace codegen::java
