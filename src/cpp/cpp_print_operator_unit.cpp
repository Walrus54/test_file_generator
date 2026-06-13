/// @file cpp_print_operator_unit.cpp
/// @brief Реализация узла оператора печати C++.
#include "cpp/cpp_print_operator_unit.h"

namespace codegen::cpp {

std::string CppPrintOperatorUnit::compile( unsigned int level ) const {
    return generateShift( level ) + "printf( \"" + m_text + "\" );\n";
}

} // namespace codegen::cpp
