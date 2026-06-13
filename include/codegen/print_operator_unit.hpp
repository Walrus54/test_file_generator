#pragma once

/**
 * @file print_operator_unit.hpp
 * @brief Абстрактное представление оператора печати строки.
 */

#include <string>

#include "codegen/unit.hpp"

namespace codegen {

/**
 * @brief Абстрактный узел «оператор печати».
 *
 * Конкретные языковые подклассы реализуют compile() с вызовом вывода,
 * специфичным для своего языка.
 */
class PrintOperatorUnit : public Unit {
public:
    /**
     * @brief Создать узел печати.
     * @param text Текст для вывода.
     */
    explicit PrintOperatorUnit( const std::string& text ) : m_text( text ) {}

protected:
    std::string m_text; ///< Выводимый текст.
};

} // namespace codegen
