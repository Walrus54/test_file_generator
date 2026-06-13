#pragma once

#include <string>

#include "codegen/unit.hpp"

namespace codegen {

// Abstract representation of a "print a string" statement. Concrete language
// subclasses implement compile() with the language-specific output call.
class PrintOperatorUnit : public Unit {
public:
    explicit PrintOperatorUnit( const std::string& text ) : m_text( text ) {}

protected:
    std::string m_text;
};

} // namespace codegen
