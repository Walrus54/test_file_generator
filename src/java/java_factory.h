#pragma once

/// @file java_factory.h
/// @brief Фабрика узлов для языка Java.

#include "factory.h"

namespace codegen::java {

/// @brief Конкретная фабрика, порождающая семейство узлов Java.
class JavaFactory : public AbstractFactory {
public:
    std::shared_ptr< ClassUnit > createClass(
        const std::string& name, Flags flags = 0 ) const override;
    std::shared_ptr< MethodUnit > createMethod(
        const std::string& name, const std::string& returnType, Flags flags = 0 ) const override;
    std::shared_ptr< FieldUnit > createField(
        const std::string& name, const std::string& type, Flags flags = 0 ) const override;
    std::shared_ptr< PrintOperatorUnit > createPrintOperator(
        const std::string& text ) const override;
    std::string languageName() const override;
};

} // namespace codegen::java
