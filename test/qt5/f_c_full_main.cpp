#include "c_full_etg.hpp"


int main (int     argc,
          char ** argv)
{
    // debug
    fmt::print("{0} => {0:d}\n",
               TestEnum::Value_2);

    // token
    fmt::print("token '{0:t}' of {0}\n",
               etg<TestEnum>::cast("special value"));

    // cast
    try
    {
        fmt::print("cast (1): {}\n",
                   etg<TestEnum>::cast(1));
    }
    catch (const std::exception & e)
    {
        return 1;
    }

    try
    {
        fmt::print("cast (5): {}\n",
                   etg<TestEnum>::cast(5));

        return 1;
    }
    catch (const std::exception & e)
    {
        fmt::print("exception\n");
    }

    // translation
    fmt::print("{0} => {0:l}\n",
               TestEnum::Value_2);

    // iterator
    fmt::print("iterator:");

    for (auto & I:etg<TestEnum>())
    {
        fmt::print(" {}",
                   int(I));
    }

    fmt::print("\n");

    return 0;
}
