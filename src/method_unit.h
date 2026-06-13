#pragma once

/// @file method_unit.h
/// @brief Абстрактный узел «метод».

#include <string>
#include <vector>

#include "unit.h"

namespace codegen {

/// @brief Абстрактный узел метода.
///
/// Хранит сигнатуру и операторы тела. Конкретные языки реализуют compile() и
/// решают, какие флаги модификаторов выводить.
class MethodUnit : public Unit {
public:
    /// @brief Конструктор.
    /// @param name       Имя метода.
    /// @param returnType Тип возвращаемого значения.
    /// @param flags      Модификаторы метода (см. MethodModifier).
    MethodUnit( const std::string& name, const std::string& returnType, Flags flags );

    /// @brief Добавить оператор в тело метода.
    /// @param unit Узел-оператор.
    void add( const std::shared_ptr< Unit >& unit, Flags flags = 0 ) override;

protected:
    std::string m_name;                            ///< Имя метода.
    std::string m_returnType;                      ///< Тип возвращаемого значения.
    Flags m_flags;                                 ///< Модификаторы метода.
    std::vector< std::shared_ptr< Unit > > m_body; ///< Операторы тела.
};

} // namespace codegen
