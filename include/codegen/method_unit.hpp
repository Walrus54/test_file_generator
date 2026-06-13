#pragma once

#include <string>
#include <vector>

#include "codegen/unit.hpp"

namespace codegen {

// Abstract representation of a member function. Holds the signature and the
// body statements; concrete language subclasses implement compile() and decide
// which modifier flags they emit.
class MethodUnit : public Unit {
public:
    MethodUnit( const std::string& name, const std::string& returnType, Flags flags )
        : m_name( name ), m_returnType( returnType ), m_flags( flags ) {}

    void add( const std::shared_ptr< Unit >& unit, Flags /* flags */ = 0 ) override {
        m_body.push_back( unit );
    }

protected:
    std::string m_name;
    std::string m_returnType;
    Flags m_flags;
    std::vector< std::shared_ptr< Unit > > m_body;
};

} // namespace codegen
