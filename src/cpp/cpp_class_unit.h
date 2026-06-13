#pragma once

/// @file cpp_class_unit.h
/// @brief Узел класса для языка C++.

#include "class_unit.h"

namespace codegen::cpp {

/// @brief Узел класса C++ (члены под метками public:/protected:/private:).
class CppClassUnit : public ClassUnit {
public:
    using ClassUnit::ClassUnit;
    std::string compile( unsigned int level = 0 ) const override;
};

} // namespace codegen::cpp
