#pragma once

/// @file types.h
/// @brief Общие типы и перечисления модификаторов генератора кода.
///
/// Набор модификаторов взят из источников, заданных в ТЗ:
///   - C#   — https://metanit.com/sharp/tutorial/3.2.php (модификаторы доступа);
///   - Java — http://proglang.su/java/modifiers (до п. 3.4; synchronized,
///            transient, volatile не включаются).
/// Поля поля используют те же флаги, что и методы (static/const/final).

namespace codegen {

/// @brief Тип битовых флагов и индексов.
using Flags = unsigned int;

/// @brief Модификаторы доступа (битовые флаги; источник — metanit 3.2 + Java).
enum AccessModifier {
    ACCESS_UNKNOWN     = 0,                    ///< Не задан / package-private (Java, без слова).
    PUBLIC             = 1 << 0,               ///< public — все языки.
    PROTECTED          = 1 << 1,               ///< protected — все языки.
    PRIVATE            = 1 << 2,               ///< private — все языки.
    PRIVATE_PROTECTED  = PRIVATE | PROTECTED,  ///< private protected — C#.
    INTERNAL           = 1 << 4,               ///< internal — C#.
    PROTECTED_INTERNAL = PROTECTED | INTERNAL, ///< protected internal — C#.
    FILE_ACCESS        = 1 << 6                ///< file — C# 11 (доступ в пределах файла).
};

/// @brief Модификаторы метода и поля (битовая маска; static/const/virtual/final/abstract).
enum MethodModifier {
    MM_UNKNOWN  = 0,         ///< Не задан.
    MM_STATIC   = 1 << 0,    ///< static — C++, C#, Java.
    MM_CONST    = 1 << 1,    ///< const — C++.
    MM_VIRTUAL  = 1 << 2,    ///< virtual — C++, C#.
    MM_FINAL    = 1 << 3,    ///< final — Java/C# (для поля C# — readonly).
    MM_ABSTRACT = 1 << 4,    ///< abstract — C#, Java.

    MM_STATIC_CONST          = MM_STATIC | MM_CONST,                ///< static + const.
    MM_STATIC_VIRTUAL        = MM_STATIC | MM_VIRTUAL,              ///< static + virtual.
    MM_FINAL_CONST           = MM_FINAL | MM_CONST,                 ///< final + const.
    MM_STATIC_FINAL          = MM_STATIC | MM_FINAL,                ///< static + final.
    MM_STATIC_ABSTRACT       = MM_STATIC | MM_ABSTRACT,             ///< static + abstract.
    MM_FINAL_ABSTRACT        = MM_FINAL | MM_ABSTRACT,              ///< final + abstract.
    MM_STATIC_FINAL_ABSTRACT = MM_STATIC | MM_FINAL | MM_ABSTRACT   ///< static + final + abstract.
};

/// @brief Модификаторы класса (битовая маска; final/abstract).
enum ClassModifier {
    CM_UNKNOWN        = 0,                    ///< Не задан.
    CM_FINAL          = 1 << 7,               ///< final — Java (для C# трактуется как sealed).
    CM_ABSTRACT       = 1 << 8,               ///< abstract — C#, Java.
    CM_ABSTRACT_FINAL = CM_ABSTRACT | CM_FINAL ///< abstract + final.
};

} // namespace codegen
