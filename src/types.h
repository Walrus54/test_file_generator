#pragma once

/// @file types.h
/// @brief Общие типы и перечисления модификаторов генератора кода.

namespace codegen {

/// @brief Тип битовых флагов и индексов.
using Flags = unsigned int;

/// @brief Модификаторы доступа (объединение вариантов трёх языков).
enum AccessModifier {
    PUBLIC = 0,           ///< public — все языки.
    PROTECTED,            ///< protected — все языки.
    PRIVATE,              ///< private — все языки.
    INTERNAL,             ///< internal — C#.
    PROTECTED_INTERNAL,   ///< protected internal — C#.
    PRIVATE_PROTECTED,    ///< private protected — C#.
    PACKAGE_PRIVATE,      ///< package-private (по умолчанию) — Java.
    ACCESS_MODIFIER_COUNT ///< Служебное значение.
};

/// @brief Модификаторы метода (битовая маска).
enum MethodModifier {
    MM_STATIC   = 1 << 0,  ///< static — C++, C#, Java.
    MM_CONST    = 1 << 1,  ///< const — C++.
    MM_VIRTUAL  = 1 << 2,  ///< virtual — C++, C#.
    MM_ABSTRACT = 1 << 3,  ///< abstract — C#, Java.
    MM_OVERRIDE = 1 << 4,  ///< override — C#.
    MM_SEALED   = 1 << 5,  ///< sealed — C#.
    MM_ASYNC    = 1 << 6,  ///< async — C#.
    MM_NEW      = 1 << 7,  ///< new — C#.
    MM_FINAL    = 1 << 8,  ///< final — Java.
    MM_NATIVE   = 1 << 9,  ///< native — Java.
    MM_STRICTFP = 1 << 10  ///< strictfp — Java.
};

/// @brief Модификаторы класса (битовая маска).
enum ClassModifier {
    CM_STATIC   = 1 << 0,  ///< static (вложенный класс) — C#, Java.
    CM_ABSTRACT = 1 << 1,  ///< abstract — C#, Java.
    CM_SEALED   = 1 << 2,  ///< sealed — C#.
    CM_PARTIAL  = 1 << 3,  ///< partial — C#.
    CM_FINAL    = 1 << 4,  ///< final — Java.
    CM_STRICTFP = 1 << 5   ///< strictfp — Java.
};

/// @brief Модификаторы поля (битовая маска).
enum FieldModifier {
    FM_STATIC   = 1 << 0,  ///< static — C++, C#, Java.
    FM_CONST    = 1 << 1,  ///< const — C++, C#.
    FM_READONLY = 1 << 2,  ///< readonly — C#.
    FM_FINAL    = 1 << 3   ///< final — Java.
};

} // namespace codegen
