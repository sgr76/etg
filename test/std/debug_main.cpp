#include "debug_etg.hpp"

#include <iostream>

using namespace std;


int main (int argc, char **argv)
{
    cout << debug_1 << " => " << etg::Debug::getDebugSymbol(debug_1)<<endl;
    
    return 0;
}
