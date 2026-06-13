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

Сборщик `buildClass(factory, spec)` (`examples.cpp`) принимает фабрику и
спецификацию `ClassSpec` — имя, флаги класса и список методов с их флагами и
модификаторами доступа. Флаги задаются вызывающей стороной (как данные), а не
зашиты в сборщик; одна и та же `ClassSpec` собирается на любом из трёх языков —
достаточно передать другую конкретную фабрику.

## Структура

Объявления вынесены в заголовки `.h`, реализация — в `.cpp` (отдельная
статическая библиотека `codegen`):

```
main.cpp                     демонстрация: одна программа на 3 языках + showcase модификаторов
examples.h / examples.cpp    переиспользуемые сборщики демо-программ
tools/emit.cpp               пишет сгенерированный код в файлы для проверки компиляции
tests/verify.sh              компилирует весь сгенерированный код реальными тулчейнами
src/
  types.h                    Flags + перечисления модификаторов (Access/Method/Class/Field)
  unit.h / unit.cpp          базовый Unit
  class_unit.{h,cpp} ...     абстрактные ClassUnit / MethodUnit / FieldUnit / PrintOperatorUnit
  factory.h                  AbstractFactory
  cpp/  csharp/  java/        по языкам: каждый юнит в своей паре .h+.cpp
                             (*_class_unit, *_method_unit, *_field_unit,
                              *_print_operator_unit) + *_factory + *_access.h
```

## Модификаторы, которых нет в C++

Набор модификаторов взят из источников, указанных в ТЗ, а не «по памяти»:

- C# — [metanit.com/sharp/tutorial/3.2.php](https://metanit.com/sharp/tutorial/3.2.php) (модификаторы доступа);
- Java — [proglang.su/java/modifiers](http://proglang.su/java/modifiers) (до п. 3.4; `synchronized`, `transient`, `volatile` не включаются).

Перечисления (`src/types.h`) повторяют выверенный по сайтам набор: один и тот же
флаг рендерится по-разному в зависимости от языка, лишние флаги язык игнорирует.

| Категория | C#                                                                    | Java                                  |
| --------- | --------------------------------------------------------------------- | ------------------------------------- |
| Доступ    | `internal`, `protected internal`, `private protected`, `file` (C# 11) | package-private (без ключевого слова) |
| Класс     | `abstract`, `sealed` (из `CM_FINAL`)                                  | `abstract`, `final`                   |
| Метод     | `static`, `virtual`, `abstract`                                       | `static`, `final`, `abstract`         |
| Поле      | `static`, `readonly` (из `MM_FINAL`)                                  | `static`, `final`                     |

## Сборка и запуск

```bash
# CMake
cmake -S . -B build && cmake --build build
./build/code_generator        # печатает сгенерированный код на 3 языках

# или напрямую
g++ -std=c++17 -Isrc -I. -o code_generator main.cpp examples.cpp src/*.cpp src/*/*.cpp && ./code_generator
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
