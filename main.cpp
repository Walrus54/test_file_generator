#include <iostream>

#include "codegen/cpp/cpp_factory.hpp"
#include "codegen/csharp/csharp_factory.hpp"
#include "examples.hpp"

using namespace codegen;

namespace {

void printSection( const std::string& title, const std::string& code ) {
    std::cout << "// ===== " << title << " =====\n" << code << "\n";
}

} // namespace

int main() {
    cpp::CppFactory cppFactory;
    csharp::CSharpFactory csharpFactory;

    printSection( "C++ : MyClass", generateProgram( cppFactory ) );
    printSection( "C#  : MyClass", generateProgram( csharpFactory ) );
    printSection( "C#  : modifier showcase", generateCSharpShowcase( csharpFactory ) );

    return 0;
}
