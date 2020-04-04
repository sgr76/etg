#include "c_full_etg.hpp"

#include <iostream>

using namespace std;


int main (int     argc,
          char ** argv)
{
    // debug
    cout << int(TestEnum::Value_2) << " => " << etg<TestEnum>::debugSymbol(TestEnum::Value_2) << endl;

    // token
    cout << "token '" << etg<TestEnum>::token(TestEnum::Value_2) << "' of " << int(etg<TestEnum>::cast("special value")) << endl;

    // cast
    try
    {
        cout << "cast (1): " << int(etg<TestEnum>::cast(1)) << endl;
    }
    catch (const std::exception & e)
    {
        return 1;
    }

    try
    {
        cout << "cast (5): " << int(etg<TestEnum>::cast(5)) << endl;

        return 1;
    }
    catch (const std::exception & e)
    {
        cout << "exception" << endl;
    }

    // translation
    // cout << int(TestEnum::Value_2) << " => " << etg::TestEnum::getTranslation(TestEnum::Value_2) << endl;

    // iterator
    cout << "iterator:";

    for (auto & I:etg<TestEnum>())
    {
        cout << " " << int(I);
    }

    cout << endl;

    return 0;
}
