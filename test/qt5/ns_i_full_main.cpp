#include "ns_i_full_etg.hpp"

#include <QtCore/QTextStream>


int main (int     argc,
          char ** argv)
{
    QTextStream out(stdout);

    // debug
    out << TestNamespace::TestClass::Value_2 << " => " << TestNamespace::etg::TestClass::TestEnum::getDebugSymbol(TestNamespace::TestClass::Value_2) << endl;

    // token
    out << "token '" << TestNamespace::etg::TestClass::TestEnum::getToken(TestNamespace::TestClass::TestEnum::Value_2) << "' of " << TestNamespace::etg::TestClass::TestEnum::getEnum("special value") << endl;

    // cast
    try
    {
        out << "cast (1): " << TestNamespace::etg::TestClass::TestEnum::cast(1) << endl;
    }
    catch (const std::exception & e)
    {
        return 1;
    }

    try
    {
        out << "cast (5): " << TestNamespace::etg::TestClass::TestEnum::cast(5) << endl;

        return 1;
    }
    catch (const std::exception & e)
    {
        out << "exception" << endl;
    }

    // translation
    out << TestNamespace::TestClass::TestEnum::Value_2 << " => " << TestNamespace::etg::TestClass::TestEnum::getTranslation(TestNamespace::TestClass::TestEnum::Value_2) << endl;

    // iterator
    out << "iterator:";

    for (auto & I:TestNamespace::etg::TestClass::TestEnum())
    {
        out << " " << I;
    }

    out << endl;

    return 0;
}
