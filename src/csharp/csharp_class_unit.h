#pragma once

/// @file csharp_class_unit.h
/// @brief Узел класса для языка C#.

#include "class_unit.h"

namespace codegen::csharp {

/// @brief Узел класса C# (abstract; sealed из CM_FINAL).
class CSharpClassUnit : public ClassUnit {
public:
    using ClassUnit::ClassUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

} // namespace codegen::csharp
