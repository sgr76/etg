#include "c_full_etg.hpp"

#include <QtCore/QTextStream>


int main (int     argc,
          char ** argv)
{
    QTextStream out(stdout);

    // debug
    out << int(TestEnum::Value_2) << " => " << etg<TestEnum>::debugSymbol(TestEnum::Value_2) << endl;

    // token
    out << "token '" << etg<TestEnum>::token(TestEnum::Value_2) << "' of " << int(etg<TestEnum>::cast("special value")) << endl;

    // cast
    try
    {
        out << "cast (1): " << int(etg<TestEnum>::cast(1)) << endl;
    }
    catch (const std::exception & e)
    {
        return 1;
    }

    try
    {
        out << "cast (5): " << int(etg<TestEnum>::cast(5)) << endl;

        return 1;
    }
    catch (const std::exception & e)
    {
        out << "exception" << endl;
    }

    // translation
    out << int(TestEnum::Value_2) << " => " << etg<TestEnum>::translation(TestEnum::Value_2) << endl;

    // iterator
    out << "iterator:";

    for (auto & I:etg<TestEnum>())
    {
        out << " " << int(I);
    }

    out << endl;

    return 0;
}
