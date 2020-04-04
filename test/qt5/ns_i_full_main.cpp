#include "ns_i_full_etg.hpp"

#include <QtCore/QTextStream>


int main (int     argc,
          char ** argv)
{
    QTextStream out(stdout);

    // debug
    out << TestNamespace::TestClass::Value_2 << " => " << etg<TestNamespace::TestClass::TestEnum>::debugSymbol(TestNamespace::TestClass::Value_2) << endl;

    // token
    out << "token '" << etg<TestNamespace::TestClass::TestEnum>::token(TestNamespace::TestClass::TestEnum::Value_2) << "' of " << etg<TestNamespace::TestClass::TestEnum>::cast("special value") << endl;

    // cast
    try
    {
        out << "cast (1): " << etg<TestNamespace::TestClass::TestEnum>::cast(1) << endl;
    }
    catch (const std::exception & e)
    {
        return 1;
    }

    try
    {
        out << "cast (5): " << etg<TestNamespace::TestClass::TestEnum>::cast(5) << endl;

        return 1;
    }
    catch (const std::exception & e)
    {
        out << "exception" << endl;
    }

    // translation
    out << TestNamespace::TestClass::TestEnum::Value_2 << " => " << etg<TestNamespace::TestClass::TestEnum>::translation(TestNamespace::TestClass::TestEnum::Value_2) << endl;

    // iterator
    out << "iterator:";

    for (auto & I:etg<TestNamespace::TestClass::TestEnum>())
    {
        out << " " << I;
    }

    out << endl;

    return 0;
}
