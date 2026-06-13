#pragma once

/// @file csharp_print_operator_unit.h
/// @brief Узел оператора печати для языка C#.

#include "print_operator_unit.h"

namespace codegen::csharp {

/// @brief Узел оператора печати C# (через System.Console.WriteLine).
class CSharpPrintOperatorUnit : public PrintOperatorUnit {
public:
    using PrintOperatorUnit::PrintOperatorUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

} // namespace codegen::csharp
