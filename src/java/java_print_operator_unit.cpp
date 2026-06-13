/// @file java_print_operator_unit.cpp
/// @brief Реализация узла оператора печати Java.
#include "java/java_print_operator_unit.h"

namespace codegen::java {

std::string JavaPrintOperatorUnit::compile( unsigned int level ) const {
    return generateShift( level ) + "System.out.println( \"" + m_text + "\" );\n";
}

} // namespace codegen::java
