#pragma once

/// @file csharp_access.h
/// @brief Сопоставление модификатора доступа ключевому слову C#.
/// Источник набора — metanit.com/sharp/tutorial/3.2.php.

#include <string>

#include "types.h"

namespace codegen::csharp {

/// @brief Ключевое слово доступа C#. Package-private отображается в private.
inline std::string accessKeyword( AccessModifier access ) {
    switch( access ) {
        case PUBLIC:             return "public";
        case PROTECTED:          return "protected";
        case INTERNAL:           return "internal";
        case PROTECTED_INTERNAL: return "protected internal";
        case PRIVATE_PROTECTED:  return "private protected";
        case FILE_ACCESS:        return "file";
        case PRIVATE:
        default:                 return "private";
    }
}

} // namespace codegen::csharp
