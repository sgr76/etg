#include "ns_full_etg.hpp"

#include <iostream>

using namespace std;


int main (int     argc,
          char ** argv)
{
    // debug
    cout << TestNamespace::Value_2 << " => " << etg<TestNamespace::TestEnum>::debugSymbol(TestNamespace::Value_2) << endl;

    // token
    cout << "token '" << etg<TestNamespace::TestEnum>::token(TestNamespace::TestEnum::Value_2) << "' of " << etg<TestNamespace::TestEnum>::cast("special value") << endl;

    // cast
    try
    {
        cout << "cast (1): " << etg<TestNamespace::TestEnum>::cast(1) << endl;
    }
    catch (const std::exception & e)
    {
        return 1;
    }

    try
    {
        cout << "cast (5): " << etg<TestNamespace::TestEnum>::cast(5) << endl;

        return 1;
    }
    catch (const std::exception & e)
    {
        cout << "exception" << endl;
    }

    // translation
    // cout << TestNamespace::TestEnum::Value_2 << " => " << etg<TestNamespace::TestEnum>::getTranslation(TestNamespace::TestEnum::Value_2) << endl;

    // iterator
    cout << "iterator:";

    for (auto & I:etg<TestNamespace::TestEnum>())
    {
        cout << " " << I;
    }

    cout << endl;

    return 0;
}
