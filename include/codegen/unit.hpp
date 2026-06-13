#pragma once

#include <memory>
#include <stdexcept>
#include <string>

#include "codegen/types.hpp"

namespace codegen {

// Base class of every syntax node. A Unit knows how to render itself into the
// target language via compile() and may carry an access modifier so its parent
// ClassUnit can place it correctly.
class Unit {
public:
    virtual ~Unit() = default;

    // Add a nested element (a method body statement, a class member, ...).
    // Not every Unit supports nesting, hence the default throwing implementation.
    virtual void add( const std::shared_ptr< Unit >&, Flags ) {
        throw std::runtime_error( "Not supported" );
    }

    // Render this node, indented by `level` shift steps.
    virtual std::string compile( unsigned int level = 0 ) const = 0;

    void setAccessModifier( AccessModifier access ) { m_access = access; }
    AccessModifier accessModifier() const { return m_access; }

protected:
    virtual std::string generateShift( unsigned int level ) const {
        static const auto DEFAULT_SHIFT = "    ";
        std::string result;
        for( unsigned int i = 0; i < level; ++i ) {
            result += DEFAULT_SHIFT;
        }
        return result;
    }

    AccessModifier m_access = PRIVATE;
};

} // namespace codegen
