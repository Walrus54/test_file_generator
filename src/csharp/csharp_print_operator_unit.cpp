/// @file csharp_print_operator_unit.cpp
/// @brief Реализация узла оператора печати C#.
#include "csharp/csharp_print_operator_unit.h"

#include "text_util.h"

namespace codegen::csharp {

std::string CSharpPrintOperatorUnit::compile( unsigned int level ) const {
    return generateShift( level ) + "System.Console.WriteLine( \"" + escapeStringLiteral( m_text ) + "\" );\n";
}

} // namespace codegen::csharp
