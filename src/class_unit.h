#pragma once

/// @file class_unit.h
/// @brief Абстрактный узел «класс».

#include <string>
#include <vector>

#include "unit.h"

namespace codegen {

/// @brief Абстрактный узел класса.
///
/// Хранит имя, модификаторы класса и упорядоченный список членов (каждый член
/// несёт собственный модификатор доступа). Конкретные языки реализуют compile().
class ClassUnit : public Unit {
public:
    /// @brief Конструктор.
    /// @param name  Имя класса.
    /// @param flags Модификаторы класса (см. ClassModifier).
    ClassUnit( const std::string& name, Flags flags );

    /// @brief Добавить член класса.
    /// @param unit  Член класса (метод, поле, вложенный класс).
    /// @param flags Модификатор доступа члена (значение AccessModifier).
    void add( const std::shared_ptr< Unit >& unit, Flags flags ) override;

protected:
    std::string m_name;                               ///< Имя класса.
    Flags m_flags;                                    ///< Модификаторы класса.
    std::vector< std::shared_ptr< Unit > > m_members; ///< Члены класса.
};

} // namespace codegen
