#include "ns_i_c_full_etg.hpp"

#include <QtCore/QTextStream>


int main (int     argc,
          char ** argv)
{
    QTextStream out(stdout);

    // debug
    out << int(TestNamespace::TestClass::TestEnum::Value_2) << " => " << etg<TestNamespace::TestClass::TestEnum>::debugSymbol(TestNamespace::TestClass::TestEnum::Value_2) << endl;

    // token
    out << "token '" << etg<TestNamespace::TestClass::TestEnum>::token(TestNamespace::TestClass::TestEnum::Value_2) << "' of " << int(etg<TestNamespace::TestClass::TestEnum>::cast("special value")) << endl;

    // cast
    try
    {
        out << "cast (1): " << int(etg<TestNamespace::TestClass::TestEnum>::cast(1)) << endl;
    }
    catch (const std::exception & e)
    {
        return 1;
    }

    try
    {
        out << "cast (5): " << int(etg<TestNamespace::TestClass::TestEnum>::cast(5)) << endl;

        return 1;
    }
    catch (const std::exception & e)
    {
        out << "exception" << endl;
    }

    // translation
    out << int(TestNamespace::TestClass::TestEnum::Value_2) << " => " << etg<TestNamespace::TestClass::TestEnum>::translation(TestNamespace::TestClass::TestEnum::Value_2) << endl;

    // iterator
    out << "iterator:";

    for (auto & I:etg<TestNamespace::TestClass::TestEnum>())
    {
        out << " " << int(I);
    }

    out << endl;

    return 0;
}
