#pragma once

/**
 * @file class_unit.hpp
 * @brief Абстрактное представление класса.
 */

#include <string>
#include <vector>

#include "codegen/unit.hpp"

namespace codegen {

/**
 * @brief Абстрактный узел «класс».
 *
 * Хранит имя класса, битовую маску модификаторов уровня класса и упорядоченный
 * список членов (каждый член несёт собственный модификатор доступа).
 * Конкретные языковые подклассы реализуют compile().
 */
class ClassUnit : public Unit {
public:
    /**
     * @brief Создать узел класса.
     * @param name  Имя класса.
     * @param flags Битовая маска модификаторов класса (см. ClassModifier).
     */
    ClassUnit( const std::string& name, Flags flags )
        : m_name( name ), m_flags( flags ) {}

    /**
     * @brief Добавить член класса.
     * @param unit  Добавляемый член (метод, поле, вложенный класс).
     * @param flags Модификатор доступа члена (значение AccessModifier).
     */
    void add( const std::shared_ptr< Unit >& unit, Flags flags ) override {
        unit->setAccessModifier( static_cast< AccessModifier >( flags ) );
        m_members.push_back( unit );
    }

protected:
    std::string m_name;                              ///< Имя класса.
    Flags m_flags;                                   ///< Модификаторы класса.
    std::vector< std::shared_ptr< Unit > > m_members; ///< Члены класса.
};

} // namespace codegen
