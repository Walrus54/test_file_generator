#pragma once

/// @file java_access.h
/// @brief Сопоставление модификатора доступа ключевому слову Java.
/// Источник набора — proglang.su/java/modifiers.

#include <string>

#include "types.h"

namespace codegen::java {

/// @brief Ключевое слово доступа Java. Package-private — пустая строка.
inline std::string accessKeyword( AccessModifier access ) {
    switch( access ) {
        case PUBLIC:    return "public";
        case PROTECTED: return "protected";
        case PRIVATE:   return "private";
        default:        return ""; // package-private / значения только для C#
    }
}

} // namespace codegen::java
