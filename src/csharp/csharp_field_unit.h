#pragma once

/// @file csharp_field_unit.h
/// @brief Узел поля для языка C#.

#include "field_unit.h"

namespace codegen::csharp {

/// @brief Узел поля C# (static; readonly из MM_FINAL).
class CSharpFieldUnit : public FieldUnit {
public:
    using FieldUnit::FieldUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

} // namespace codegen::csharp
