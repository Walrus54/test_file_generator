#pragma once

namespace codegen {

// Bit-flag / index type used across every Unit and factory method.
using Flags = unsigned int;

// Access modifiers. The enum is the union of everything the three target
// languages support; each language maps the values it understands to keywords
// and ignores the rest.
//   C++  : PUBLIC, PROTECTED, PRIVATE
//   C#   : + INTERNAL, PROTECTED_INTERNAL, PRIVATE_PROTECTED
//   Java : + PACKAGE_PRIVATE (the default, empty keyword)
enum AccessModifier {
    PUBLIC = 0,
    PROTECTED,
    PRIVATE,
    INTERNAL,            // C#
    PROTECTED_INTERNAL,  // C#
    PRIVATE_PROTECTED,   // C#
    PACKAGE_PRIVATE,     // Java
    ACCESS_MODIFIER_COUNT
};

// Method modifiers as a bit mask. A single MethodUnit can combine several
// (e.g. C# "public static async").
enum MethodModifier {
    MM_STATIC   = 1 << 0,  // C++, C#, Java
    MM_CONST    = 1 << 1,  // C++
    MM_VIRTUAL  = 1 << 2,  // C++, C#
    MM_ABSTRACT = 1 << 3,  // C#, Java
    MM_OVERRIDE = 1 << 4,  // C#
    MM_SEALED   = 1 << 5,  // C#
    MM_ASYNC    = 1 << 6,  // C#
    MM_NEW      = 1 << 7,  // C#
    MM_FINAL    = 1 << 8,  // Java
    MM_NATIVE   = 1 << 9,  // Java
    MM_STRICTFP = 1 << 10  // Java
};

// Class-level modifiers as a bit mask.
enum ClassModifier {
    CM_STATIC   = 1 << 0,  // C#, Java (nested)
    CM_ABSTRACT = 1 << 1,  // C#, Java
    CM_SEALED   = 1 << 2,  // C#
    CM_PARTIAL  = 1 << 3,  // C#
    CM_FINAL    = 1 << 4,  // Java
    CM_STRICTFP = 1 << 5   // Java
};

// Field modifiers as a bit mask.
enum FieldModifier {
    FM_STATIC   = 1 << 0,  // C++, C#, Java
    FM_CONST    = 1 << 1,  // C++, C#
    FM_READONLY = 1 << 2,  // C#
    FM_FINAL    = 1 << 3   // Java
};

} // namespace codegen
