#pragma once

/// @file cpp_method_unit.h
/// @brief Узел метода для языка C++.

#include "method_unit.h"

namespace codegen::cpp {

/// @brief Узел метода C++ (static/virtual/const/final, чистая виртуальность).
class CppMethodUnit : public MethodUnit {
public:
    using MethodUnit::MethodUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

} // namespace codegen::cpp
