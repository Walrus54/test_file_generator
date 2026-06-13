#pragma once

/**
 * @file types.hpp
 * @brief Общие типы и перечисления модификаторов для генератора кода.
 *
 * Здесь собран «словарь» модификаторов, общий для всех целевых языков
 * (C++, C#, Java). Каждый язык использует только осмысленные для него значения,
 * а остальные игнорирует.
 */

namespace codegen {

/**
 * @brief Тип битовых флагов и индексов, используемый узлами и фабриками.
 */
using Flags = unsigned int;

/**
 * @brief Модификаторы доступа.
 *
 * Перечисление — объединение всех вариантов доступа, поддерживаемых тремя
 * языками. Каждый язык сопоставляет понятным ему значениям ключевые слова,
 * а прочие трактует по умолчанию.
 *   - C++  : PUBLIC, PROTECTED, PRIVATE
 *   - C#   : дополнительно INTERNAL, PROTECTED_INTERNAL, PRIVATE_PROTECTED
 *   - Java : дополнительно PACKAGE_PRIVATE (по умолчанию, без ключевого слова)
 */
enum AccessModifier {
    PUBLIC = 0,           ///< Публичный доступ (все языки).
    PROTECTED,            ///< Защищённый доступ (все языки).
    PRIVATE,              ///< Приватный доступ (все языки).
    INTERNAL,             ///< Доступ в пределах сборки — C#.
    PROTECTED_INTERNAL,   ///< protected internal — C#.
    PRIVATE_PROTECTED,    ///< private protected — C#.
    PACKAGE_PRIVATE,      ///< Доступ в пределах пакета (по умолчанию) — Java.
    ACCESS_MODIFIER_COUNT ///< Служебное значение — количество модификаторов.
};

/**
 * @brief Модификаторы метода в виде битовой маски.
 *
 * Один MethodUnit может комбинировать несколько флагов
 * (например, в C# «public static async»).
 */
enum MethodModifier {
    MM_STATIC   = 1 << 0,  ///< static — C++, C#, Java.
    MM_CONST    = 1 << 1,  ///< const — только C++.
    MM_VIRTUAL  = 1 << 2,  ///< virtual — C++, C#.
    MM_ABSTRACT = 1 << 3,  ///< abstract — C#, Java.
    MM_OVERRIDE = 1 << 4,  ///< override — C#.
    MM_SEALED   = 1 << 5,  ///< sealed — C#.
    MM_ASYNC    = 1 << 6,  ///< async — C#.
    MM_NEW      = 1 << 7,  ///< new (сокрытие) — C#.
    MM_FINAL    = 1 << 8,  ///< final — Java.
    MM_NATIVE   = 1 << 9,  ///< native — Java.
    MM_STRICTFP = 1 << 10  ///< strictfp — Java.
};

/**
 * @brief Модификаторы класса в виде битовой маски.
 */
enum ClassModifier {
    CM_STATIC   = 1 << 0,  ///< static (вложенный класс) — C#, Java.
    CM_ABSTRACT = 1 << 1,  ///< abstract — C#, Java.
    CM_SEALED   = 1 << 2,  ///< sealed — C#.
    CM_PARTIAL  = 1 << 3,  ///< partial — C#.
    CM_FINAL    = 1 << 4,  ///< final — Java.
    CM_STRICTFP = 1 << 5   ///< strictfp — Java.
};

/**
 * @brief Модификаторы поля в виде битовой маски.
 */
enum FieldModifier {
    FM_STATIC   = 1 << 0,  ///< static — C++, C#, Java.
    FM_CONST    = 1 << 1,  ///< const — C++, C#.
    FM_READONLY = 1 << 2,  ///< readonly — C#.
    FM_FINAL    = 1 << 3   ///< final — Java.
};

} // namespace codegen
