#include "i_full_etg.hpp"

#include <iostream>

using namespace std;


int main (int     argc,
          char ** argv)
{
    // debug
    cout << TestClass::Value_2 << " => " << etg::TestClass::TestEnum::getDebugSymbol(TestClass::Value_2) << endl;

    // token
    cout << "token '" << etg::TestClass::TestEnum::getToken(TestClass::TestEnum::Value_2) << "' of " << etg::TestClass::TestEnum::getEnum("special value") << endl;

    // cast
    try
    {
        cout << "cast (1): " << etg::TestClass::TestEnum::cast(1) << endl;
    }
    catch (const std::exception & e)
    {
        return 1;
    }

    try
    {
        cout << "cast (5): " << etg::TestClass::TestEnum::cast(5) << endl;

        return 1;
    }
    catch (const std::exception & e)
    {
        cout << "exception" << endl;
    }

    // translation
    // cout << TestClass::TestEnum::Value_2 << " => " << etg::TestClass::TestEnum::getTranslation(TestClass::TestEnum::Value_2) << endl;

    // iterator
    cout << "iterator:";

    for (auto & I:etg::TestClass::TestEnum())
    {
        cout << " " << I;
    }

    cout << endl;

    return 0;
}
