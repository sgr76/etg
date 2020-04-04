#include "ns_full_etg.hpp"

#include <QtCore/QTextStream>


int main (int     argc,
          char ** argv)
{
    QTextStream out(stdout);

    // debug
    out << TestNamespace::Value_2 << " => " << etg<TestNamespace::TestEnum>::debugSymbol(TestNamespace::Value_2) << endl;

    // token
    out << "token '" << etg<TestNamespace::TestEnum>::token(TestNamespace::TestEnum::Value_2) << "' of " << etg<TestNamespace::TestEnum>::cast("special value") << endl;

    // cast
    try
    {
        out << "cast (1): " << etg<TestNamespace::TestEnum>::cast(1) << endl;
    }
    catch (const std::exception & e)
    {
        return 1;
    }

    try
    {
        out << "cast (5): " << etg<TestNamespace::TestEnum>::cast(5) << endl;

        return 1;
    }
    catch (const std::exception & e)
    {
        out << "exception" << endl;
    }

    // translation
    out << TestNamespace::TestEnum::Value_2 << " => " << etg<TestNamespace::TestEnum>::translation(TestNamespace::TestEnum::Value_2) << endl;

    // iterator
    out << "iterator:";

    for (auto & I:etg<TestNamespace::TestEnum>())
    {
        out << " " << I;
    }

    out << endl;

    return 0;
}
