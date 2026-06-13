#pragma once

/// @file cpp_print_operator_unit.h
/// @brief Узел оператора печати для языка C++.

#include "print_operator_unit.h"

namespace codegen::cpp {

/// @brief Узел оператора печати C++ (через printf).
class CppPrintOperatorUnit : public PrintOperatorUnit {
public:
    using PrintOperatorUnit::PrintOperatorUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

} // namespace codegen::cpp
