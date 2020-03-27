#include "ns_full_etg.hpp"

#include <QtCore/QTextStream>


int main (int     argc,
          char ** argv)
{
    QTextStream out(stdout);

    // debug
    out << TestNamespace::Value_2 << " => " << TestNamespace::etg::TestEnum::getDebugSymbol(TestNamespace::Value_2) << endl;

    // token
    out << "token '" << TestNamespace::etg::TestEnum::getToken(TestNamespace::TestEnum::Value_2) << "' of " << TestNamespace::etg::TestEnum::getEnum("special value") << endl;

    // cast
    try
    {
        out << "cast (1): " << TestNamespace::etg::TestEnum::cast(1) << endl;
    }
    catch (const std::exception & e)
    {
        return 1;
    }

    try
    {
        out << "cast (5): " << TestNamespace::etg::TestEnum::cast(5) << endl;

        return 1;
    }
    catch (const std::exception & e)
    {
        out << "exception" << endl;
    }

    // translation
    out << TestNamespace::TestEnum::Value_2 << " => " << TestNamespace::etg::TestEnum::getTranslation(TestNamespace::TestEnum::Value_2) << endl;

    // iterator
    out << "iterator:";

    for (auto & I:TestNamespace::etg::TestEnum())
    {
        out << " " << I;
    }

    out << endl;

    return 0;
}
