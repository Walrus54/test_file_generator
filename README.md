# Code Generator — Лабораторная №2 (Абстрактная фабрика)

Расширение учебного генератора кода: исходная версия умела порождать только
C++, текущая — порождает **C++, C# и Java** через паттерн **Abstract Factory**,
не меняя клиентский код генерации.

## Идея

Узлы синтаксиса (`Unit`) и фабрика разделены на абстрактный интерфейс и
конкретные реализации под каждый язык:

```
AbstractFactory ──► createClass / createMethod / createField / createPrintOperator
      ▲
      ├── CppFactory      → CppClassUnit,    CppMethodUnit,    ...
      ├── CSharpFactory   → CSharpClassUnit, CSharpMethodUnit, ...
      └── JavaFactory     → JavaClassUnit,   JavaMethodUnit,   ...
```

Клиент (`generateProgram` в `examples.hpp`) работает только с
`AbstractFactory`, поэтому один и тот же код собирает программу на любом из
трёх языков — достаточно передать другую конкретную фабрику.

## Структура

```
main.cpp                     демонстрация: одна программа на 3 языках + showcase модификаторов
examples.hpp                 переиспользуемые сборщики демо-программ
tools/emit.cpp               пишет сгенерированный код в файлы для проверки компиляции
tests/verify.sh              компилирует весь сгенерированный код реальными тулчейнами
include/codegen/
  types.hpp                  Flags + перечисления модификаторов (Access/Method/Class/Field)
  unit.hpp                   базовый Unit
  class_unit.hpp ...         абстрактные ClassUnit / MethodUnit / FieldUnit / PrintOperatorUnit
  factory.hpp                AbstractFactory
  cpp/    csharp/    java/   конкретные фабрики и узлы по языкам
```

## Модификаторы, которых нет в C++

Добавлены модификаторы классов и методов из C# и Java (узлы эмитят только те
флаги, что осмысленны для их языка; чужие игнорируются):

| Категория | C#                                                                    | Java                                                |
| --------- | --------------------------------------------------------------------- | --------------------------------------------------- |
| Доступ    | `internal`, `protected internal`, `private protected`                 | package-private (без ключевого слова)               |
| Класс     | `abstract`, `sealed`, `static`, `partial`                             | `abstract`, `final`, `static`, `strictfp`           |
| Метод     | `abstract`, `virtual`, `override`, `sealed`, `async`, `new`, `static` | `abstract`, `final`, `native`, `static`, `strictfp` |
| Поле      | `static`, `readonly`                                                  | `static`, `final`                                   |

## Сборка и запуск

```bash
# CMake
cmake -S . -B build && cmake --build build
./build/code_generator        # печатает сгенерированный код на 3 языках

# или напрямую
g++ -std=c++17 -Iinclude -o code_generator main.cpp && ./code_generator
```

## Проверка, что сгенерированный код компилируется

```bash
bash tests/verify.sh
```

Скрипт генерирует программы, затем компилирует их:
`g++ -std=c++17` (C++), `javac` (Java), `dotnet build` (C#). Требуются
соответствующие тулчейны; отсутствующий — пропускается.

## Git-флоу

`main` (исходный предложенный код) → `develop` → feature-ветки
(`abstract-factory`, `csharp-generator`, `java-generator`,
`verification-and-docs`). Первый коммит — размещение исходного кода из
`lab_2.pdf`, проверенного на сборку и запуск.
