#pragma once

/// @file field_unit.h
/// @brief Абстрактный узел «поле».

#include <string>

#include "unit.h"

namespace codegen {

/// @brief Абстрактный узел поля. Конкретные языки реализуют compile().
class FieldUnit : public Unit {
public:
    /// @brief Конструктор.
    /// @param name  Имя поля.
    /// @param type  Тип поля.
    /// @param flags Модификаторы поля (см. FieldModifier).
    FieldUnit( const std::string& name, const std::string& type, Flags flags );

protected:
    std::string m_name; ///< Имя поля.
    std::string m_type; ///< Тип поля.
    Flags m_flags;      ///< Модификаторы поля.
};

} // namespace codegen
