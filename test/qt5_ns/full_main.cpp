#include "full_etg.hpp"

#include <QtCore/QTextStream>


int main (int     argc,
          char ** argv)
{
    QTextStream out(stdout);

    // debug
    out << Value_2 << " => " << etg::TestEnum::getDebugSymbol(Value_2) << endl;

    // token
    out << "token '" << etg::TestEnum::getToken(TestEnum::Value_2) << "' of " << etg::TestEnum::getEnum("special value") << endl;

    // cast
    try
    {
        out << "cast (1): " << etg::TestEnum::cast(1) << endl;
    }
    catch (const std::exception & e)
    {
        return 1;
    }

    try
    {
        out << "cast (5): " << etg::TestEnum::cast(5) << endl;

        return 1;
    }
    catch (const std::exception & e)
    {
        out << "exception" << endl;
    }

    // translation
    out << TestEnum::Value_2 << " => " << etg::TestEnum::getTranslation(TestEnum::Value_2) << endl;

    // iterator
    out << "iterator:";

    for (auto & I:etg::TestEnum())
    {
        out << " " << I;
    }

    out << endl;

    return 0;
}
