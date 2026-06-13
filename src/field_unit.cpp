/// @file field_unit.cpp
/// @brief Реализация абстрактного узла поля.
#include "field_unit.h"

namespace codegen {

FieldUnit::FieldUnit( const std::string& name, const std::string& type, Flags flags )
    : m_name( name ), m_type( type ), m_flags( flags ) {}

} // namespace codegen
