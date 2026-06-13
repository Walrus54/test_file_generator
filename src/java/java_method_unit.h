#pragma once

/// @file java_method_unit.h
/// @brief Узел метода для языка Java.

#include "method_unit.h"

namespace codegen::java {

/// @brief Узел метода Java (static/final/abstract).
class JavaMethodUnit : public MethodUnit {
public:
    using MethodUnit::MethodUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

} // namespace codegen::java
