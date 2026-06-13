#pragma once

#include <string>

#include "codegen/class_unit.hpp"
#include "codegen/field_unit.hpp"
#include "codegen/method_unit.hpp"
#include "codegen/print_operator_unit.hpp"

namespace codegen::java {

// Maps the shared AccessModifier enum onto Java keywords. The package-private
// default (and any C#-only value) renders as no keyword at all.
inline std::string accessKeyword( AccessModifier access ) {
    switch( access ) {
        case PUBLIC:    return "public";
        case PROTECTED: return "protected";
        case PRIVATE:   return "private";
        default:        return ""; // package-private / C#-only values
    }
}

class JavaClassUnit : public ClassUnit {
public:
    using ClassUnit::ClassUnit;

    std::string compile( unsigned int level = 0 ) const override {
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
};

class JavaMethodUnit : public MethodUnit {
public:
    using MethodUnit::MethodUnit;

    std::string compile( unsigned int level = 0 ) const override {
        std::string result = generateShift( level );
        std::string access = accessKeyword( m_access );
        if( !access.empty() ) result += access + " ";

        if( m_flags & MM_STATIC )   result += "static ";
        if( m_flags & MM_FINAL )    result += "final ";
        if( m_flags & MM_ABSTRACT ) result += "abstract ";
        if( m_flags & MM_NATIVE )   result += "native ";
        if( m_flags & MM_STRICTFP ) result += "strictfp ";
        // MM_CONST / MM_VIRTUAL / C#-only flags have no Java meaning.

        result += m_returnType + " " + m_name + "()";

        // Abstract and native methods have no body in Java.
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
};

class JavaFieldUnit : public FieldUnit {
public:
    using FieldUnit::FieldUnit;

    std::string compile( unsigned int level = 0 ) const override {
        std::string result = generateShift( level );
        std::string access = accessKeyword( m_access );
        if( !access.empty() ) result += access + " ";
        if( m_flags & FM_STATIC ) result += "static ";
        if( m_flags & FM_FINAL )  result += "final ";
        result += m_type + " " + m_name + ";\n";
        return result;
    }
};

class JavaPrintOperatorUnit : public PrintOperatorUnit {
public:
    using PrintOperatorUnit::PrintOperatorUnit;

    std::string compile( unsigned int level = 0 ) const override {
        return generateShift( level ) + "System.out.println( \"" + m_text + "\" );\n";
    }
};

} // namespace codegen::java
