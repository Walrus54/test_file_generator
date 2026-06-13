/// @file cpp_factory.cpp
/// @brief Реализация фабрики узлов для языка C++.
#include "cpp/cpp_factory.h"

#include "cpp/cpp_units.h"

namespace codegen::cpp {

std::shared_ptr< ClassUnit > CppFactory::createClass( const std::string& name, Flags flags ) const {
    return std::make_shared< CppClassUnit >( name, flags );
}

std::shared_ptr< MethodUnit > CppFactory::createMethod(
    const std::string& name, const std::string& returnType, Flags flags ) const {
    return std::make_shared< CppMethodUnit >( name, returnType, flags );
}

std::shared_ptr< FieldUnit > CppFactory::createField(
    const std::string& name, const std::string& type, Flags flags ) const {
    return std::make_shared< CppFieldUnit >( name, type, flags );
}

std::shared_ptr< PrintOperatorUnit > CppFactory::createPrintOperator( const std::string& text ) const {
    return std::make_shared< CppPrintOperatorUnit >( text );
}

std::string CppFactory::languageName() const {
    return "C++";
}

} // namespace codegen::cpp
