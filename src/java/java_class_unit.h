#pragma once

/// @file java_class_unit.h
/// @brief Узел класса для языка Java.

#include "class_unit.h"

namespace codegen::java {

/// @brief Узел класса Java (abstract/final).
class JavaClassUnit : public ClassUnit {
public:
    using ClassUnit::ClassUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

} // namespace codegen::java
