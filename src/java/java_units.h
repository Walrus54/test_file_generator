#pragma once

/// @file java_units.h
/// @brief Узлы генерации для языка Java.

#include "class_unit.h"
#include "field_unit.h"
#include "method_unit.h"
#include "print_operator_unit.h"

namespace codegen::java {

/// @brief Узел класса Java (abstract/final/static/strictfp).
class JavaClassUnit : public ClassUnit {
public:
    using ClassUnit::ClassUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

/// @brief Узел метода Java (static/final/abstract/native/strictfp).
class JavaMethodUnit : public MethodUnit {
public:
    using MethodUnit::MethodUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

/// @brief Узел поля Java (static/final).
class JavaFieldUnit : public FieldUnit {
public:
    using FieldUnit::FieldUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

/// @brief Узел оператора печати Java (через System.out.println).
class JavaPrintOperatorUnit : public PrintOperatorUnit {
public:
    using PrintOperatorUnit::PrintOperatorUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

} // namespace codegen::java
