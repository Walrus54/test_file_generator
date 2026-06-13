#pragma once

/// @file cpp_field_unit.h
/// @brief Узел поля для языка C++.

#include "field_unit.h"

namespace codegen::cpp {

/// @brief Узел поля C++ (static/const).
class CppFieldUnit : public FieldUnit {
public:
    using FieldUnit::FieldUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

} // namespace codegen::cpp
