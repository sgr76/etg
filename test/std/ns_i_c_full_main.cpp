#include "ns_i_c_full_etg.hpp"

#include <iostream>

using namespace std;


int main (int     argc,
          char ** argv)
{
    // debug
    cout << int(TestNamespace::TestClass::TestEnum::Value_2) << " => " << etg<TestNamespace::TestClass::TestEnum>::debugSymbol(TestNamespace::TestClass::TestEnum::Value_2) << endl;

    // token
    cout << "token '" << etg<TestNamespace::TestClass::TestEnum>::token(TestNamespace::TestClass::TestEnum::Value_2) << "' of " << int(etg<TestNamespace::TestClass::TestEnum>::cast("special value")) << endl;

    // cast
    try
    {
        cout << "cast (1): " << int(etg<TestNamespace::TestClass::TestEnum>::cast(1)) << endl;
    }
    catch (const std::exception & e)
    {
        return 1;
    }

    try
    {
        cout << "cast (5): " << int(etg<TestNamespace::TestClass::TestEnum>::cast(5)) << endl;

        return 1;
    }
    catch (const std::exception & e)
    {
        cout << "exception" << endl;
    }

    // translation
    // cout << int(TestNamespace::TestClass::TestEnum::Value_2) << " => " << etg<TestNamespace::TestClass::TestEnum>::getTranslation(TestNamespace::TestClass::TestEnum::Value_2) << endl;

    // iterator
    cout << "iterator:";

    for (auto & I:etg<TestNamespace::TestClass::TestEnum>())
    {
        cout << " " << int(I);
    }

    cout << endl;

    return 0;
}
