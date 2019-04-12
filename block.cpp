#include <iostream>
#include "block.h"

using namespace std;

Block::Block()
{
    #ifdef DEBUGBUILD
        cout << "    DEBUG: new block created." << endl;
    #endif
}
