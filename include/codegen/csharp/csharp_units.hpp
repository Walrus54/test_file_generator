#pragma once

/**
 * @file csharp_units.hpp
 * @brief Конкретные узлы генерации для языка C#.
 */

#include <string>

#include "codegen/class_unit.hpp"
#include "codegen/field_unit.hpp"
#include "codegen/method_unit.hpp"
#include "codegen/print_operator_unit.hpp"

namespace codegen::csharp {

/**
 * @brief Сопоставить общий AccessModifier ключевому слову C#.
 *
 * В C# нет package-private, поэтому такое значение отображается в "private".
 * @param access Модификатор доступа.
 * @return Ключевое слово доступа C#.
 */
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

/**
 * @brief Узел класса C#. Выводит модификаторы abstract/sealed/static/partial.
 */
class CSharpClassUnit : public ClassUnit {
public:
    using ClassUnit::ClassUnit;

    /**
     * @brief Сгенерировать объявление класса C#.
     * @param level Уровень вложенности.
     * @return Текст класса.
     */
    std::string compile( unsigned int level = 0 ) const override {
        std::string mods;
        // У класса верхнего уровня доступ оставляем по умолчанию (internal);
        // здесь выводятся только специфичные для C# модификаторы класса.
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

/**
 * @brief Узел метода C#.
 *
 * Выводит модификаторы new/static/virtual/abstract/sealed/override/async.
 * Абстрактный метод формируется без тела (только сигнатура с «;»).
 */
class CSharpMethodUnit : public MethodUnit {
public:
    using MethodUnit::MethodUnit;

    /**
     * @brief Сгенерировать определение метода C#.
     * @param level Уровень вложенности.
     * @return Текст метода.
     */
    std::string compile( unsigned int level = 0 ) const override {
        std::string result = generateShift( level ) + accessKeyword( m_access ) + " ";

        if( m_flags & MM_NEW )      result += "new ";
        if( m_flags & MM_STATIC )   result += "static ";
        if( m_flags & MM_VIRTUAL )  result += "virtual ";
        if( m_flags & MM_ABSTRACT ) result += "abstract ";
        if( m_flags & MM_SEALED )   result += "sealed ";
        if( m_flags & MM_OVERRIDE ) result += "override ";
        if( m_flags & MM_ASYNC )    result += "async ";
        // MM_CONST не имеет смысла на уровне метода в C# и игнорируется.

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

/**
 * @brief Узел поля C#. Выводит модификаторы static/readonly.
 */
class CSharpFieldUnit : public FieldUnit {
public:
    using FieldUnit::FieldUnit;

    /**
     * @brief Сгенерировать объявление поля C#.
     * @param level Уровень вложенности.
     * @return Текст поля.
     */
    std::string compile( unsigned int level = 0 ) const override {
        std::string result = generateShift( level ) + accessKeyword( m_access ) + " ";
        if( m_flags & FM_STATIC )   result += "static ";
        if( m_flags & FM_READONLY ) result += "readonly ";
        // FM_CONST в C# требует инициализатора времени компиляции, поэтому для
        // поля без значения не выводится; static/readonly покрывают примеры.
        result += m_type + " " + m_name + ";\n";
        return result;
    }
};

/**
 * @brief Узел оператора печати C# (через System.Console.WriteLine).
 */
class CSharpPrintOperatorUnit : public PrintOperatorUnit {
public:
    using PrintOperatorUnit::PrintOperatorUnit;

    /**
     * @brief Сгенерировать вызов System.Console.WriteLine.
     * @param level Уровень вложенности.
     * @return Текст оператора печати.
     */
    std::string compile( unsigned int level = 0 ) const override {
        return generateShift( level ) + "System.Console.WriteLine( \"" + m_text + "\" );\n";
    }
};

} // namespace codegen::csharp
