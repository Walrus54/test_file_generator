#pragma once

/**
 * @file method_unit.hpp
 * @brief Абстрактное представление функции-члена (метода).
 */

#include <string>
#include <vector>

#include "codegen/unit.hpp"

namespace codegen {

/**
 * @brief Абстрактный узел «метод».
 *
 * Хранит сигнатуру (имя, тип возвращаемого значения, флаги модификаторов) и
 * операторы тела. Конкретные языковые подклассы реализуют compile() и решают,
 * какие флаги модификаторов выводить.
 */
class MethodUnit : public Unit {
public:
    /**
     * @brief Создать узел метода.
     * @param name       Имя метода.
     * @param returnType Тип возвращаемого значения.
     * @param flags      Битовая маска модификаторов метода (см. MethodModifier).
     */
    MethodUnit( const std::string& name, const std::string& returnType, Flags flags )
        : m_name( name ), m_returnType( returnType ), m_flags( flags ) {}

    /**
     * @brief Добавить оператор в тело метода.
     * @param unit Узел-оператор.
     */
    void add( const std::shared_ptr< Unit >& unit, Flags /* flags */ = 0 ) override {
        m_body.push_back( unit );
    }

protected:
    std::string m_name;                            ///< Имя метода.
    std::string m_returnType;                      ///< Тип возвращаемого значения.
    Flags m_flags;                                 ///< Модификаторы метода.
    std::vector< std::shared_ptr< Unit > > m_body; ///< Операторы тела метода.
};

} // namespace codegen
