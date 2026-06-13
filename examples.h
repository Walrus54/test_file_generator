#pragma once

/// @file examples.h
/// @brief Переиспользуемые сборщики демонстрационных программ.

#include <string>

#include "factory.h"

namespace codegen {

/// @brief Переносимая демо-программа: класс MyClass через AbstractFactory.
/// @param factory Фабрика целевого языка.
/// @return Сгенерированный текст программы.
std::string generateProgram( const AbstractFactory& factory );

/// @brief Демонстрация модификаторов, специфичных для C#.
/// @param factory Фабрика C#.
/// @return Сгенерированный текст класса-демонстрации.
std::string generateCSharpShowcase( const AbstractFactory& factory );

/// @brief Демонстрация модификаторов, специфичных для Java.
/// @param factory Фабрика Java.
/// @return Сгенерированный текст класса-демонстрации.
std::string generateJavaShowcase( const AbstractFactory& factory );

} // namespace codegen
