#pragma once

/**
 * @file field_unit.hpp
 * @brief Абстрактное представление поля (данных-члена).
 */

#include <string>

#include "codegen/unit.hpp"

namespace codegen {

/**
 * @brief Абстрактный узел «поле».
 *
 * Конкретные языковые подклассы реализуют compile() и решают, какие флаги
 * модификаторов поля выводить.
 */
class FieldUnit : public Unit {
public:
    /**
     * @brief Создать узел поля.
     * @param name  Имя поля.
     * @param type  Тип поля.
     * @param flags Битовая маска модификаторов поля (см. FieldModifier).
     */
    FieldUnit( const std::string& name, const std::string& type, Flags flags )
        : m_name( name ), m_type( type ), m_flags( flags ) {}

protected:
    std::string m_name; ///< Имя поля.
    std::string m_type; ///< Тип поля.
    Flags m_flags;      ///< Модификаторы поля.
};

} // namespace codegen
