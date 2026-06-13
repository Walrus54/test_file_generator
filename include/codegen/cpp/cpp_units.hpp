#pragma once

#include <array>
#include <string>

#include "codegen/class_unit.hpp"
#include "codegen/field_unit.hpp"
#include "codegen/method_unit.hpp"
#include "codegen/print_operator_unit.hpp"

namespace codegen::cpp {

class CppClassUnit : public ClassUnit {
public:
    using ClassUnit::ClassUnit;

    std::string compile( unsigned int level = 0 ) const override {
        // C++ has no abstract/sealed/partial/... class modifiers, so m_flags
        // is intentionally ignored here.
        std::string result = generateShift( level ) + "class " + m_name + " {\n";

        static constexpr std::array< AccessModifier, 3 > order = { PUBLIC, PROTECTED, PRIVATE };
        static const char* keyword[] = { "public", "protected", "private" };

        for( AccessModifier access : order ) {
            bool sectionOpened = false;
            for( const auto& member : m_members ) {
                if( member->accessModifier() != access ) {
                    continue;
                }
                if( !sectionOpened ) {
                    result += generateShift( level ) + keyword[ access ] + ":\n";
                    sectionOpened = true;
                }
                result += member->compile( level + 1 );
            }
            if( sectionOpened ) {
                result += "\n";
            }
        }

        result += generateShift( level ) + "};\n";
        return result;
    }
};

class CppMethodUnit : public MethodUnit {
public:
    using MethodUnit::MethodUnit;

    std::string compile( unsigned int level = 0 ) const override {
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
};

class CppFieldUnit : public FieldUnit {
public:
    using FieldUnit::FieldUnit;

    std::string compile( unsigned int level = 0 ) const override {
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
};

class CppPrintOperatorUnit : public PrintOperatorUnit {
public:
    using PrintOperatorUnit::PrintOperatorUnit;

    std::string compile( unsigned int level = 0 ) const override {
        return generateShift( level ) + "printf( \"" + m_text + "\" );\n";
    }
};

} // namespace codegen::cpp
