#pragma once

/// @file factory.h
/// @brief Интерфейс абстрактной фабрики узлов.

#include <memory>
#include <string>

#include "class_unit.h"
#include "field_unit.h"
#include "method_unit.h"
#include "print_operator_unit.h"
#include "types.h"

namespace codegen {

/// @brief Абстрактная фабрика (паттерн Abstract Factory).
///
/// Объявляет по одному фабричному методу на тип продукта. Конкретная фабрика
/// порождает семейство узлов своего языка. Клиентский код зависит только от
/// этого интерфейса.
class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;

    /// @brief Создать узел класса.
    virtual std::shared_ptr< ClassUnit > createClass(
        const std::string& name, Flags flags = 0 ) const = 0;

    /// @brief Создать узел метода.
    virtual std::shared_ptr< MethodUnit > createMethod(
        const std::string& name, const std::string& returnType, Flags flags = 0 ) const = 0;

    /// @brief Создать узел поля.
    virtual std::shared_ptr< FieldUnit > createField(
        const std::string& name, const std::string& type, Flags flags = 0 ) const = 0;

    /// @brief Создать узел оператора печати.
    virtual std::shared_ptr< PrintOperatorUnit > createPrintOperator(
        const std::string& text ) const = 0;

    /// @brief Название целевого языка ("C++", "C#", "Java").
    virtual std::string languageName() const = 0;
};

} // namespace codegen
