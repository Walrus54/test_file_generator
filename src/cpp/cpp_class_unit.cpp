/// @file cpp_class_unit.cpp
/// @brief Реализация узла класса C++.
#include "cpp/cpp_class_unit.h"

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

} // namespace codegen::cpp
