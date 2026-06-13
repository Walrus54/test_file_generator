#pragma once

/// @file unit.h
/// @brief Базовый класс узла синтаксического дерева.

#include <memory>
#include <string>

#include "types.h"

namespace codegen {

/// @brief Базовый класс любого элемента генерируемого кода.
class Unit {
public:
    virtual ~Unit() = default;

    /// @brief Добавить вложенный элемент.
    /// @param unit  Вложенный узел.
    /// @param flags Дополнительные флаги (например, модификатор доступа).
    /// @throw std::runtime_error Если узел не поддерживает вложение.
    virtual void add( const std::shared_ptr< Unit >& unit, Flags flags );

    /// @brief Сгенерировать текст узла.
    /// @param level Уровень вложенности (для отступов).
    /// @return Код на целевом языке.
    virtual std::string compile( unsigned int level = 0 ) const = 0;

    /// @brief Задать модификатор доступа узла.
    void setAccessModifier( AccessModifier access ) { m_access = access; }

    /// @brief Получить модификатор доступа узла.
    AccessModifier accessModifier() const { return m_access; }

protected:
    /// @brief Сформировать строку отступа для уровня вложенности.
    /// @param level Уровень вложенности.
    /// @return Строка из нужного числа пробелов.
    virtual std::string generateShift( unsigned int level ) const;

    AccessModifier m_access = PRIVATE; ///< Модификатор доступа узла.
};

} // namespace codegen
