#include <iostream>
#include "block.h"

using namespace std;

Block::Block()
{
    #ifdef DEBUG
        cout << "    DEBUG: new block created." << endl;
    #endif
}
