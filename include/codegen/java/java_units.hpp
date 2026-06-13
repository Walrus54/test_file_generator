#pragma once

/**
 * @file java_units.hpp
 * @brief Конкретные узлы генерации для языка Java.
 */

#include <string>

#include "codegen/class_unit.hpp"
#include "codegen/field_unit.hpp"
#include "codegen/method_unit.hpp"
#include "codegen/print_operator_unit.hpp"

namespace codegen::java {

/**
 * @brief Сопоставить общий AccessModifier ключевому слову Java.
 *
 * Доступ по умолчанию (package-private) и любые значения, специфичные для C#,
 * отображаются в пустую строку (без ключевого слова).
 * @param access Модификатор доступа.
 * @return Ключевое слово доступа Java либо пустая строка.
 */
inline std::string accessKeyword( AccessModifier access ) {
    switch( access ) {
        case PUBLIC:    return "public";
        case PROTECTED: return "protected";
        case PRIVATE:   return "private";
        default:        return ""; // package-private / значения только для C#
    }
}

/**
 * @brief Узел класса Java. Выводит модификаторы abstract/final/static/strictfp.
 */
class JavaClassUnit : public ClassUnit {
public:
    using ClassUnit::ClassUnit;

    /**
     * @brief Сгенерировать объявление класса Java.
     * @param level Уровень вложенности.
     * @return Текст класса.
     */
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

/**
 * @brief Узел метода Java.
 *
 * Выводит модификаторы static/final/abstract/native/strictfp.
 * Абстрактные и native-методы формируются без тела (только сигнатура с «;»).
 */
class JavaMethodUnit : public MethodUnit {
public:
    using MethodUnit::MethodUnit;

    /**
     * @brief Сгенерировать определение метода Java.
     * @param level Уровень вложенности.
     * @return Текст метода.
     */
    std::string compile( unsigned int level = 0 ) const override {
        std::string result = generateShift( level );
        std::string access = accessKeyword( m_access );
        if( !access.empty() ) result += access + " ";

        if( m_flags & MM_STATIC )   result += "static ";
        if( m_flags & MM_FINAL )    result += "final ";
        if( m_flags & MM_ABSTRACT ) result += "abstract ";
        if( m_flags & MM_NATIVE )   result += "native ";
        if( m_flags & MM_STRICTFP ) result += "strictfp ";
        // MM_CONST / MM_VIRTUAL и флаги, специфичные для C#, в Java смысла не имеют.

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
};

/**
 * @brief Узел поля Java. Выводит модификаторы static/final.
 */
class JavaFieldUnit : public FieldUnit {
public:
    using FieldUnit::FieldUnit;

    /**
     * @brief Сгенерировать объявление поля Java.
     * @param level Уровень вложенности.
     * @return Текст поля.
     */
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

/**
 * @brief Узел оператора печати Java (через System.out.println).
 */
class JavaPrintOperatorUnit : public PrintOperatorUnit {
public:
    using PrintOperatorUnit::PrintOperatorUnit;

    /**
     * @brief Сгенерировать вызов System.out.println.
     * @param level Уровень вложенности.
     * @return Текст оператора печати.
     */
    std::string compile( unsigned int level = 0 ) const override {
        return generateShift( level ) + "System.out.println( \"" + m_text + "\" );\n";
    }
};

} // namespace codegen::java
