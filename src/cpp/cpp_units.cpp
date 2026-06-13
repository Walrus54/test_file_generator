/// @file cpp_units.cpp
/// @brief Реализация узлов генерации для языка C++.
#include "cpp/cpp_units.h"

#include <array>

namespace codegen::cpp {
namespace {

/// @brief Ключевое слово секции доступа C++.
const char* sectionKeyword( AccessModifier access ) {
    switch( access ) {
        case PUBLIC:    return "public";
        case PROTECTED: return "protected";
        default:        return "private";
    }
}

} // namespace

std::string CppClassUnit::compile( unsigned int level ) const {
    std::string shift = generateShift( level );
    std::string result = shift + "class " + m_name;
    if( m_flags & CM_FINAL ) {
        result += " final";
    }
    result += " {\n";

    static constexpr std::array< AccessModifier, 3 > order = { PUBLIC, PROTECTED, PRIVATE };
    for( AccessModifier access : order ) {
        bool opened = false;
        for( const auto& member : m_members ) {
            if( member->accessModifier() != access ) {
                continue;
            }
            if( !opened ) {
                result += shift + sectionKeyword( access ) + ":\n";
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
    } else if( m_flags & ( MM_VIRTUAL | MM_ABSTRACT ) ) {
        result += "virtual ";
    }
    result += m_returnType + " " + m_name + "()";
    if( m_flags & MM_CONST ) {
        result += " const";
    }
    if( m_flags & MM_FINAL ) {
        result += " final";
    }
    // Чистая виртуальная функция — без тела.
    if( m_flags & MM_ABSTRACT ) {
        result += " = 0;\n";
        return result;
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
    if( m_flags & MM_STATIC ) {
        result += "static ";
    }
    if( m_flags & MM_CONST ) {
        result += "const ";
    }
    result += m_type + " " + m_name + ";\n";
    return result;
}

std::string CppPrintOperatorUnit::compile( unsigned int level ) const {
    return generateShift( level ) + "printf( \"" + m_text + "\" );\n";
}

} // namespace codegen::cpp
