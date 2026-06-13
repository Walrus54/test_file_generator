#pragma once

/// @file examples.h
/// @brief Обобщённый сборщик класса по флагам и набор демо-спецификаций.

#include <string>
#include <vector>

#include "factory.h"

namespace codegen {

/// @brief Спецификация метода: имя, тип, флаги модификаторов, доступ, тела-печати.
struct MethodSpec {
    std::string name;                 ///< Имя метода.
    std::string returnType;           ///< Тип возвращаемого значения.
    Flags flags = 0;                  ///< Модификаторы метода (см. MethodModifier).
    AccessModifier access = PUBLIC;   ///< Модификатор доступа.
    std::vector< std::string > prints; ///< Тексты операторов печати в теле.
};

/// @brief Спецификация класса: имя, флаги класса и его методы.
struct ClassSpec {
    std::string name;                 ///< Имя класса.
    Flags classFlags = CM_UNKNOWN;    ///< Модификаторы класса (см. ClassModifier).
    std::vector< MethodSpec > methods; ///< Методы класса.
};

/// @brief Собрать класс через фабрику по переданной спецификации (флаги — в spec).
/// @param factory Фабрика целевого языка (живёт у вызывающей стороны).
/// @param spec    Что и с какими флагами создавать.
/// @return Сгенерированный текст класса.
std::string buildClass( const AbstractFactory& factory, const ClassSpec& spec );

/// @brief Переносимая демо-программа (класс MyClass из лабораторной).
ClassSpec programSpec();

/// @brief Демонстрация модификаторов, специфичных для C#.
ClassSpec csharpShowcaseSpec();

/// @brief Демонстрация модификаторов, специфичных для Java.
ClassSpec javaShowcaseSpec();

} // namespace codegen
