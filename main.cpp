#include <iostream>

#include "codegen/cpp/cpp_factory.hpp"
#include "codegen/csharp/csharp_factory.hpp"
#include "codegen/java/java_factory.hpp"
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
    java::JavaFactory javaFactory;

    // The same generateProgram() call produces all three languages.
    printSection( "C++  : MyClass", generateProgram( cppFactory ) );
    printSection( "C#   : MyClass", generateProgram( csharpFactory ) );
    printSection( "Java : MyClass", generateProgram( javaFactory ) );

    // Language-specific modifier showcases.
    printSection( "C#   : modifier showcase", generateCSharpShowcase( csharpFactory ) );
    printSection( "Java : modifier showcase", generateJavaShowcase( javaFactory ) );

    return 0;
}
