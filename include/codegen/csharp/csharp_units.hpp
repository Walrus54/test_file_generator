#pragma once

#include <string>

#include "codegen/class_unit.hpp"
#include "codegen/field_unit.hpp"
#include "codegen/method_unit.hpp"
#include "codegen/print_operator_unit.hpp"

namespace codegen::csharp {

// Maps the shared AccessModifier enum onto C# keywords. C# has no
// package-private, so it falls back to "private".
inline std::string accessKeyword( AccessModifier access ) {
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

class CSharpClassUnit : public ClassUnit {
public:
    using ClassUnit::ClassUnit;

    std::string compile( unsigned int level = 0 ) const override {
        std::string mods;
        // A top-level class is left at the default (internal) access; only the
        // C#-specific class modifiers are emitted here.
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
};

class CSharpMethodUnit : public MethodUnit {
public:
    using MethodUnit::MethodUnit;

    std::string compile( unsigned int level = 0 ) const override {
        std::string result = generateShift( level ) + accessKeyword( m_access ) + " ";

        if( m_flags & MM_NEW )      result += "new ";
        if( m_flags & MM_STATIC )   result += "static ";
        if( m_flags & MM_VIRTUAL )  result += "virtual ";
        if( m_flags & MM_ABSTRACT ) result += "abstract ";
        if( m_flags & MM_SEALED )   result += "sealed ";
        if( m_flags & MM_OVERRIDE ) result += "override ";
        if( m_flags & MM_ASYNC )    result += "async ";
        // MM_CONST has no method-level meaning in C# and is ignored.

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
};

class CSharpFieldUnit : public FieldUnit {
public:
    using FieldUnit::FieldUnit;

    std::string compile( unsigned int level = 0 ) const override {
        std::string result = generateShift( level ) + accessKeyword( m_access ) + " ";
        if( m_flags & FM_STATIC )   result += "static ";
        if( m_flags & FM_READONLY ) result += "readonly ";
        // FM_CONST in C# requires a compile-time initializer, so it is not
        // emitted for value-less fields; static/readonly cover the demos.
        result += m_type + " " + m_name + ";\n";
        return result;
    }
};

class CSharpPrintOperatorUnit : public PrintOperatorUnit {
public:
    using PrintOperatorUnit::PrintOperatorUnit;

    std::string compile( unsigned int level = 0 ) const override {
        return generateShift( level ) + "System.Console.WriteLine( \"" + m_text + "\" );\n";
    }
};

} // namespace codegen::csharp
