/// @file csharp_units.cpp
/// @brief Реализация узлов генерации для языка C#.
#include "csharp/csharp_units.h"

namespace codegen::csharp {
namespace {

/// @brief Ключевое слово доступа C#. Package-private отображается в private.
std::string accessKeyword( AccessModifier access ) {
    switch( access ) {
        case PUBLIC:             return "public";
        case PROTECTED:          return "protected";
        case INTERNAL:           return "internal";
        case PROTECTED_INTERNAL: return "protected internal";
        case PRIVATE_PROTECTED:  return "private protected";
        case PRIVATE:
        case PACKAGE_PRIVATE:
        default:                 return "private";
    }
}

} // namespace

std::string CSharpClassUnit::compile( unsigned int level ) const {
    std::string mods;
    if( m_flags & CM_ABSTRACT ) mods += "abstract ";
    if( m_flags & CM_SEALED )   mods += "sealed ";
    if( m_flags & CM_STATIC )   mods += "static ";
    if( m_flags & CM_PARTIAL )  mods += "partial ";

    std::string shift = generateShift( level );
    std::string result = shift + mods + "class " + m_name + "\n";
    result += shift + "{\n";
    for( const auto& member : m_members ) {
        result += member->compile( level + 1 );
    }
    result += shift + "}\n";
    return result;
}

std::string CSharpMethodUnit::compile( unsigned int level ) const {
    std::string result = generateShift( level ) + accessKeyword( m_access ) + " ";

    if( m_flags & MM_NEW )      result += "new ";
    if( m_flags & MM_STATIC )   result += "static ";
    if( m_flags & MM_VIRTUAL )  result += "virtual ";
    if( m_flags & MM_ABSTRACT ) result += "abstract ";
    if( m_flags & MM_SEALED )   result += "sealed ";
    if( m_flags & MM_OVERRIDE ) result += "override ";
    if( m_flags & MM_ASYNC )    result += "async ";

    result += m_returnType + " " + m_name + "()";

    if( m_flags & MM_ABSTRACT ) {
        result += ";\n";
        return result;
    }

    result += "\n" + generateShift( level ) + "{\n";
    for( const auto& statement : m_body ) {
        result += statement->compile( level + 1 );
    }
    result += generateShift( level ) + "}\n";
    return result;
}

std::string CSharpFieldUnit::compile( unsigned int level ) const {
    std::string result = generateShift( level ) + accessKeyword( m_access ) + " ";
    if( m_flags & FM_STATIC )   result += "static ";
    if( m_flags & FM_READONLY ) result += "readonly ";
    result += m_type + " " + m_name + ";\n";
    return result;
}

std::string CSharpPrintOperatorUnit::compile( unsigned int level ) const {
    return generateShift( level ) + "System.Console.WriteLine( \"" + m_text + "\" );\n";
}

} // namespace codegen::csharp
