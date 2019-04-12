#include <iostream>
#include "block.h"

using namespace std;

int main()
{
    #ifdef DEBUG
        cout << "    DEBUG: entering main routine." << endl;
    #endif

    Block helloworldBlock;

    return 0;
}
