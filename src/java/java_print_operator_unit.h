#pragma once

/// @file java_print_operator_unit.h
/// @brief Узел оператора печати для языка Java.

#include "print_operator_unit.h"

namespace codegen::java {

/// @brief Узел оператора печати Java (через System.out.println).
class JavaPrintOperatorUnit : public PrintOperatorUnit {
public:
    using PrintOperatorUnit::PrintOperatorUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

} // namespace codegen::java
