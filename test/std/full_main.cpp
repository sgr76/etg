#include "full_etg.hpp"

#include <iostream>

using namespace std;


int main (int     argc,
          char ** argv)
{
    // debug
    cout << Value_2 << " => " << etg::TestEnum::getDebugSymbol(Value_2) << endl;

    // token
    cout << "token '" << etg::TestEnum::getToken(TestEnum::Value_2) << "' of " << etg::TestEnum::getEnum("special value") << endl;

    // cast
    try
    {
        cout << "cast (1): " << etg::TestEnum::cast(1) << endl;
    }
    catch (const std::exception & e)
    {
        return 1;
    }

    try
    {
        cout << "cast (5): " << etg::TestEnum::cast(5) << endl;

        return 1;
    }
    catch (const std::exception & e)
    {
        cout << "exception" << endl;
    }

    // translation
    // cout << TestEnum::Value_2 << " => " << etg::TestEnum::getTranslation(TestEnum::Value_2) << endl;

    // iterator
    cout << "iterator:";

    for (auto & I:etg::TestEnum())
    {
        cout << " " << I;
    }

    cout << endl;

    return 0;
}
