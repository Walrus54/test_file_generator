#pragma once

#include <string>

#include "codegen/unit.hpp"

namespace codegen {

// Abstract representation of a data member. Concrete language subclasses
// implement compile() and decide which field modifier flags they emit.
class FieldUnit : public Unit {
public:
    FieldUnit( const std::string& name, const std::string& type, Flags flags )
        : m_name( name ), m_type( type ), m_flags( flags ) {}

protected:
    std::string m_name;
    std::string m_type;
    Flags m_flags;
};

} // namespace codegen
