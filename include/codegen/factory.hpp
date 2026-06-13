#pragma once

/**
 * @file factory.hpp
 * @brief Интерфейс абстрактной фабрики узлов.
 */

#include <memory>
#include <string>

#include "codegen/class_unit.hpp"
#include "codegen/field_unit.hpp"
#include "codegen/method_unit.hpp"
#include "codegen/print_operator_unit.hpp"
#include "codegen/types.hpp"

namespace codegen {

/**
 * @brief Абстрактная фабрика (паттерн Abstract Factory).
 *
 * Объявляет по одному фабричному методу на каждый тип продукта. Конкретная
 * фабрика (CppFactory, CSharpFactory, JavaFactory) создаёт семейство узлов,
 * порождающих одну и ту же логическую программу на своём языке. Клиентский код
 * (например, generateProgram()) зависит только от этого интерфейса и никогда —
 * от конкретного узла.
 */
class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;

    /**
     * @brief Создать узел класса.
     * @param name  Имя класса.
     * @param flags Модификаторы класса (см. ClassModifier).
     * @return Узел класса целевого языка.
     */
    virtual std::shared_ptr< ClassUnit > createClass(
        const std::string& name, Flags flags = 0 ) const = 0;

    /**
     * @brief Создать узел метода.
     * @param name       Имя метода.
     * @param returnType Тип возвращаемого значения.
     * @param flags      Модификаторы метода (см. MethodModifier).
     * @return Узел метода целевого языка.
     */
    virtual std::shared_ptr< MethodUnit > createMethod(
        const std::string& name, const std::string& returnType, Flags flags = 0 ) const = 0;

    /**
     * @brief Создать узел поля.
     * @param name  Имя поля.
     * @param type  Тип поля.
     * @param flags Модификаторы поля (см. FieldModifier).
     * @return Узел поля целевого языка.
     */
    virtual std::shared_ptr< FieldUnit > createField(
        const std::string& name, const std::string& type, Flags flags = 0 ) const = 0;

    /**
     * @brief Создать узел оператора печати.
     * @param text Текст для вывода.
     * @return Узел печати целевого языка.
     */
    virtual std::shared_ptr< PrintOperatorUnit > createPrintOperator(
        const std::string& text ) const = 0;
};

} // namespace codegen
