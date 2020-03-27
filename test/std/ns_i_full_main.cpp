#include "ns_i_full_etg.hpp"

#include <iostream>

using namespace std;


int main (int     argc,
          char ** argv)
{
    // debug
    cout << TestNamespace::TestClass::Value_2 << " => " << TestNamespace::etg::TestClass::TestEnum::getDebugSymbol(TestNamespace::TestClass::Value_2) << endl;

    // token
    cout << "token '" << TestNamespace::etg::TestClass::TestEnum::getToken(TestNamespace::TestClass::TestEnum::Value_2) << "' of " << TestNamespace::etg::TestClass::TestEnum::getEnum("special value") << endl;

    // cast
    try
    {
        cout << "cast (1): " << TestNamespace::etg::TestClass::TestEnum::cast(1) << endl;
    }
    catch (const std::exception & e)
    {
        return 1;
    }

    try
    {
        cout << "cast (5): " << TestNamespace::etg::TestClass::TestEnum::cast(5) << endl;

        return 1;
    }
    catch (const std::exception & e)
    {
        cout << "exception" << endl;
    }

    // translation
    // cout << TestNamespace::TestClass::TestEnum::Value_2 << " => " << TestNamespace::etg::TestClass::TestEnum::getTranslation(TestNamespace::TestClass::TestEnum::Value_2) << endl;

    // iterator
    cout << "iterator:";

    for (auto & I:TestNamespace::etg::TestClass::TestEnum())
    {
        cout << " " << I;
    }

    cout << endl;

    return 0;
}
