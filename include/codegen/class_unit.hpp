#pragma once

#include <string>
#include <vector>

#include "codegen/unit.hpp"

namespace codegen {

// Abstract representation of a class. Stores the name, class-level modifier
// flags and the ordered list of members (each member carries its own access
// modifier). Concrete language subclasses implement compile().
class ClassUnit : public Unit {
public:
    ClassUnit( const std::string& name, Flags flags )
        : m_name( name ), m_flags( flags ) {}

    // The second argument is the member's AccessModifier.
    void add( const std::shared_ptr< Unit >& unit, Flags flags ) override {
        unit->setAccessModifier( static_cast< AccessModifier >( flags ) );
        m_members.push_back( unit );
    }

protected:
    std::string m_name;
    Flags m_flags;
    std::vector< std::shared_ptr< Unit > > m_members;
};

} // namespace codegen
