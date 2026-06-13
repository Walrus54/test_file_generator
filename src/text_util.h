#pragma once

/// @file text_util.h
/// @brief Экранирование строковых литералов и валидация имён.

#include <stdexcept>
#include <string>

namespace codegen {

/// @brief Экранировать произвольный текст для строкового литерала C++/C#/Java.
///
/// Спецсимволы (`\`, `"`, перевод строки и т. п.) заменяются на escape-
/// последовательности, чтобы текст нельзя было «вырваться» из литерала и
/// внедрить произвольный код в генерируемую программу.
/// @param text Исходный текст.
/// @return Экранированное содержимое литерала (без обрамляющих кавычек).
inline std::string escapeStringLiteral( const std::string& text ) {
    std::string result;
    result.reserve( text.size() );
    for( char c : text ) {
        switch( c ) {
            case '\\': result += "\\\\"; break;
            case '\"': result += "\\\""; break;
            case '\n': result += "\\n"; break;
            case '\r': result += "\\r"; break;
            case '\t': result += "\\t"; break;
            default:   result += c; break;
        }
    }
    return result;
}

/// @brief Проверить, что строка не пуста.
/// @param value Проверяемое значение.
/// @param what  Название поля для сообщения об ошибке.
/// @return Ссылка на исходную строку.
/// @throw std::invalid_argument Если строка пуста.
inline const std::string& requireNonEmpty( const std::string& value, const char* what ) {
    if( value.empty() ) {
        throw std::invalid_argument( std::string( what ) + " must not be empty" );
    }
    return value;
}

/// @brief Проверить, что строка — корректный идентификатор ([A-Za-z_][A-Za-z0-9_]*).
///
/// Защищает генерируемый код от инъекции через имена классов/методов/полей.
/// @param name Проверяемое имя.
/// @param what Название поля для сообщения об ошибке.
/// @return Ссылка на исходную строку.
/// @throw std::invalid_argument Если имя пусто или содержит недопустимые символы.
inline const std::string& requireIdentifier( const std::string& name, const char* what ) {
    requireNonEmpty( name, what );
    auto isIdentChar = []( char c, bool first ) {
        return c == '_' || ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) ||
               ( !first && c >= '0' && c <= '9' );
    };
    for( std::size_t i = 0; i < name.size(); ++i ) {
        if( !isIdentChar( name[ i ], i == 0 ) ) {
            throw std::invalid_argument( std::string( what ) + " is not a valid identifier: " + name );
        }
    }
    return name;
}

} // namespace codegen
