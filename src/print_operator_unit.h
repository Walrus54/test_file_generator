#pragma once

/// @file print_operator_unit.h
/// @brief Абстрактный узел «оператор печати».

#include <string>

#include "unit.h"

namespace codegen {

/// @brief Абстрактный узел оператора печати. Конкретные языки реализуют compile().
class PrintOperatorUnit : public Unit {
public:
    /// @brief Конструктор.
    /// @param text Текст для вывода.
    explicit PrintOperatorUnit( const std::string& text );

protected:
    std::string m_text; ///< Выводимый текст.
};

} // namespace codegen
