#pragma once

/// @file csharp_method_unit.h
/// @brief Узел метода для языка C#.

#include "method_unit.h"

namespace codegen::csharp {

/// @brief Узел метода C# (static/virtual/abstract).
class CSharpMethodUnit : public MethodUnit {
public:
    using MethodUnit::MethodUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

} // namespace codegen::csharp
