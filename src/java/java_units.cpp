/// @file java_units.cpp
/// @brief Реализация узлов генерации для языка Java.
#include "java/java_units.h"

namespace codegen::java {
namespace {

/// @brief Ключевое слово доступа Java. Package-private — пустая строка.
std::string accessKeyword( AccessModifier access ) {
    switch( access ) {
        case PUBLIC:    return "public";
        case PROTECTED: return "protected";
        case PRIVATE:   return "private";
        default:        return ""; // package-private / значения только для C#
    }
}

} // namespace

std::string JavaClassUnit::compile( unsigned int level ) const {
    std::string mods;
    if( m_flags & CM_ABSTRACT ) mods += "abstract ";
    if( m_flags & CM_FINAL )    mods += "final ";
    if( m_flags & CM_STATIC )   mods += "static ";
    if( m_flags & CM_STRICTFP ) mods += "strictfp ";

    std::string shift = generateShift( level );
    std::string result = shift + mods + "class " + m_name + " {\n";
    for( const auto& member : m_members ) {
        result += member->compile( level + 1 );
    }
    result += shift + "}\n";
    return result;
}

std::string JavaMethodUnit::compile( unsigned int level ) const {
    std::string result = generateShift( level );
    std::string access = accessKeyword( m_access );
    if( !access.empty() ) result += access + " ";

    if( m_flags & MM_STATIC )   result += "static ";
    if( m_flags & MM_FINAL )    result += "final ";
    if( m_flags & MM_ABSTRACT ) result += "abstract ";
    if( m_flags & MM_NATIVE )   result += "native ";
    if( m_flags & MM_STRICTFP ) result += "strictfp ";

    result += m_returnType + " " + m_name + "()";

    // У абстрактных и native-методов в Java нет тела.
    if( m_flags & ( MM_ABSTRACT | MM_NATIVE ) ) {
        result += ";\n";
        return result;
    }

    result += " {\n";
    for( const auto& statement : m_body ) {
        result += statement->compile( level + 1 );
    }
    result += generateShift( level ) + "}\n";
    return result;
}

std::string JavaFieldUnit::compile( unsigned int level ) const {
    std::string result = generateShift( level );
    std::string access = accessKeyword( m_access );
    if( !access.empty() ) result += access + " ";
    if( m_flags & FM_STATIC ) result += "static ";
    if( m_flags & FM_FINAL )  result += "final ";
    result += m_type + " " + m_name + ";\n";
    return result;
}

std::string JavaPrintOperatorUnit::compile( unsigned int level ) const {
    return generateShift( level ) + "System.out.println( \"" + m_text + "\" );\n";
}

} // namespace codegen::java
