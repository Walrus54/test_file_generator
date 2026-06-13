#pragma once

/// @file java_field_unit.h
/// @brief Узел поля для языка Java.

#include "field_unit.h"

namespace codegen::java {

/// @brief Узел поля Java (static/final).
class JavaFieldUnit : public FieldUnit {
public:
    using FieldUnit::FieldUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

} // namespace codegen::java
