#include "debug_etg.hpp"

#include <QtCore/QTextStream>


int main (int argc, char **argv)
{
    QTextStream out(stdout);
    
    out << debug_1 << " => " << etg::Debug::getDebugSymbol(debug_1)<<endl;
    
    return 0;
}
