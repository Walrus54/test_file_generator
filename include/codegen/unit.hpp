#pragma once

/**
 * @file unit.hpp
 * @brief Базовый класс любого узла синтаксического дерева.
 */

#include <memory>
#include <stdexcept>
#include <string>

#include "codegen/types.hpp"

namespace codegen {

/**
 * @brief Базовый класс любого элемента генерируемого кода.
 *
 * Узел умеет преобразовывать себя в текст на целевом языке через compile() и
 * может хранить модификатор доступа, чтобы родительский ClassUnit разместил его
 * правильно.
 */
class Unit {
public:
    virtual ~Unit() = default;

    /**
     * @brief Добавить вложенный элемент (оператор тела метода, член класса и т. п.).
     *
     * Не каждый узел поддерживает вложение, поэтому реализация по умолчанию
     * бросает исключение.
     * @param unit  Добавляемый вложенный узел.
     * @param flags Дополнительные флаги (например, модификатор доступа члена).
     * @throws std::runtime_error Если узел не поддерживает вложение.
     */
    virtual void add( const std::shared_ptr< Unit >&, Flags ) {
        throw std::runtime_error( "Not supported" );
    }

    /**
     * @brief Сгенерировать текст узла.
     * @param level Уровень вложенности для расчёта отступов.
     * @return Строка с кодом на целевом языке.
     */
    virtual std::string compile( unsigned int level = 0 ) const = 0;

    /**
     * @brief Задать модификатор доступа узла.
     * @param access Модификатор доступа.
     */
    void setAccessModifier( AccessModifier access ) { m_access = access; }

    /**
     * @brief Получить модификатор доступа узла.
     * @return Текущий модификатор доступа.
     */
    AccessModifier accessModifier() const { return m_access; }

protected:
    /**
     * @brief Сформировать строку отступа для заданного уровня вложенности.
     * @param level Уровень вложенности.
     * @return Строка из нужного числа пробелов.
     */
    virtual std::string generateShift( unsigned int level ) const {
        static const auto DEFAULT_SHIFT = "    ";
        std::string result;
        for( unsigned int i = 0; i < level; ++i ) {
            result += DEFAULT_SHIFT;
        }
        return result;
    }

    AccessModifier m_access = PRIVATE; ///< Модификатор доступа узла.
};

} // namespace codegen
