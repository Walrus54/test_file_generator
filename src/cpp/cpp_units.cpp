/// @file cpp_units.cpp
/// @brief Реализация узлов генерации для языка C++.
#include "cpp/cpp_units.h"

#include <array>

namespace codegen::cpp {

std::string CppClassUnit::compile( unsigned int level ) const {
    // В C++ нет модификаторов класса abstract/sealed/partial — m_flags игнорируется.
    std::string shift = generateShift( level );
    std::string result = shift + "class " + m_name + " {\n";

    static constexpr std::array< AccessModifier, 3 > order = { PUBLIC, PROTECTED, PRIVATE };
    static const char* keyword[] = { "public", "protected", "private" };

    for( AccessModifier access : order ) {
        bool opened = false;
        for( const auto& member : m_members ) {
            if( member->accessModifier() != access ) {
                continue;
            }
            if( !opened ) {
                result += shift + keyword[ access ] + ":\n";
                opened = true;
            }
            result += member->compile( level + 1 );
        }
        if( opened ) {
            result += "\n";
        }
    }

    result += shift + "};\n";
    return result;
}

std::string CppMethodUnit::compile( unsigned int level ) const {
    std::string result = generateShift( level );
    if( m_flags & MM_STATIC ) {
        result += "static ";
    } else if( m_flags & MM_VIRTUAL ) {
        result += "virtual ";
    }
    result += m_returnType + " " + m_name + "()";
    if( m_flags & MM_CONST ) {
        result += " const";
    }
    result += " {\n";
    for( const auto& statement : m_body ) {
        result += statement->compile( level + 1 );
    }
    result += generateShift( level ) + "}\n";
    return result;
}

std::string CppFieldUnit::compile( unsigned int level ) const {
    std::string result = generateShift( level );
    if( m_flags & FM_STATIC ) {
        result += "static ";
    }
    if( m_flags & FM_CONST ) {
        result += "const ";
    }
    result += m_type + " " + m_name + ";\n";
    return result;
}

std::string CppPrintOperatorUnit::compile( unsigned int level ) const {
    return generateShift( level ) + "printf( \"" + m_text + "\" );\n";
}

} // namespace codegen::cpp
