#include "ns_c_full_etg.hpp"

#include <iostream>

using namespace std;


int main (int     argc,
          char ** argv)
{
    // debug
    cout << int(TestNamespace::TestEnum::Value_2) << " => " << TestNamespace::etg::TestEnum::getDebugSymbol(TestNamespace::TestEnum::Value_2) << endl;

    // token
    cout << "token '" << TestNamespace::etg::TestEnum::getToken(TestNamespace::TestEnum::Value_2) << "' of " << int(TestNamespace::etg::TestEnum::getEnum("special value")) << endl;

    // cast
    try
    {
        cout << "cast (1): " << int(TestNamespace::etg::TestEnum::cast(1)) << endl;
    }
    catch (const std::exception & e)
    {
        return 1;
    }

    try
    {
        cout << "cast (5): " << int(TestNamespace::etg::TestEnum::cast(5)) << endl;

        return 1;
    }
    catch (const std::exception & e)
    {
        cout << "exception" << endl;
    }

    // translation
    // cout << int(TestNamespace::TestEnum::Value_2) << " => " << TestNamespace::etg::TestEnum::getTranslation(TestNamespace::TestEnum::Value_2) << endl;

    // iterator
    cout << "iterator:";

    for (auto & I:TestNamespace::etg::TestEnum())
    {
        cout << " " << int(I);
    }

    cout << endl;

    return 0;
}
