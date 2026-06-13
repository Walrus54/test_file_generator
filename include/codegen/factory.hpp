#pragma once

#include <memory>
#include <string>

#include "codegen/class_unit.hpp"
#include "codegen/field_unit.hpp"
#include "codegen/method_unit.hpp"
#include "codegen/print_operator_unit.hpp"
#include "codegen/types.hpp"

namespace codegen {

// Abstract Factory: declares one factory method per product type. Each concrete
// factory (CppFactory, CSharpFactory, JavaFactory) produces a family of Units
// that render the same logical program in its own language. Client code such as
// generateProgram() depends only on this interface, never on a concrete unit.
class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;

    virtual std::shared_ptr< ClassUnit > createClass(
        const std::string& name, Flags flags = 0 ) const = 0;

    virtual std::shared_ptr< MethodUnit > createMethod(
        const std::string& name, const std::string& returnType, Flags flags = 0 ) const = 0;

    virtual std::shared_ptr< FieldUnit > createField(
        const std::string& name, const std::string& type, Flags flags = 0 ) const = 0;

    virtual std::shared_ptr< PrintOperatorUnit > createPrintOperator(
        const std::string& text ) const = 0;
};

} // namespace codegen
