#include "i_c_full_etg.hpp"

#include <QtCore/QTextStream>


int main (int     argc,
          char ** argv)
{
    QTextStream out(stdout);

    // debug
    out << int(TestClass::TestEnum::Value_2) << " => " << etg::TestClass::TestEnum::getDebugSymbol(TestClass::TestEnum::Value_2) << endl;

    // token
    out << "token '" << etg::TestClass::TestEnum::getToken(TestClass::TestEnum::Value_2) << "' of " << int(etg::TestClass::TestEnum::getEnum("special value")) << endl;

    // cast
    try
    {
        out << "cast (1): " << int(etg::TestClass::TestEnum::cast(1)) << endl;
    }
    catch (const std::exception & e)
    {
        return 1;
    }

    try
    {
        out << "cast (5): " << int(etg::TestClass::TestEnum::cast(5)) << endl;

        return 1;
    }
    catch (const std::exception & e)
    {
        out << "exception" << endl;
    }

    // translation
    out << int(TestClass::TestEnum::Value_2) << " => " << etg::TestClass::TestEnum::getTranslation(TestClass::TestEnum::Value_2) << endl;

    // iterator
    out << "iterator:";

    for (auto & I:etg::TestClass::TestEnum())
    {
        out << " " << int(I);
    }

    out << endl;

    return 0;
}
