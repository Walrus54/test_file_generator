#pragma once

/// @file csharp_units.h
/// @brief Узлы генерации для языка C#.

#include "class_unit.h"
#include "field_unit.h"
#include "method_unit.h"
#include "print_operator_unit.h"

namespace codegen::csharp {

/// @brief Узел класса C# (abstract/sealed/static/partial).
class CSharpClassUnit : public ClassUnit {
public:
    using ClassUnit::ClassUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

/// @brief Узел метода C# (new/static/virtual/abstract/sealed/override/async).
class CSharpMethodUnit : public MethodUnit {
public:
    using MethodUnit::MethodUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

/// @brief Узел поля C# (static/readonly).
class CSharpFieldUnit : public FieldUnit {
public:
    using FieldUnit::FieldUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

/// @brief Узел оператора печати C# (через System.Console.WriteLine).
class CSharpPrintOperatorUnit : public PrintOperatorUnit {
public:
    using PrintOperatorUnit::PrintOperatorUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

} // namespace codegen::csharp
