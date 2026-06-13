#pragma once

/// @file cpp_units.h
/// @brief Узлы генерации для языка C++.

#include "class_unit.h"
#include "field_unit.h"
#include "method_unit.h"
#include "print_operator_unit.h"

namespace codegen::cpp {

/// @brief Узел класса C++ (члены под метками public:/protected:/private:).
class CppClassUnit : public ClassUnit {
public:
    using ClassUnit::ClassUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

/// @brief Узел метода C++ (static/virtual/const).
class CppMethodUnit : public MethodUnit {
public:
    using MethodUnit::MethodUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

/// @brief Узел поля C++ (static/const).
class CppFieldUnit : public FieldUnit {
public:
    using FieldUnit::FieldUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

/// @brief Узел оператора печати C++ (через printf).
class CppPrintOperatorUnit : public PrintOperatorUnit {
public:
    using PrintOperatorUnit::PrintOperatorUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

} // namespace codegen::cpp
