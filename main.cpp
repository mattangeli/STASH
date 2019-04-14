#include <iostream>
#include <vector>
#include <memory>
#include "block.h"
#include "walker.h"
using namespace std;

int main()
{
    #ifdef DEBUG
        cout << "    DEBUG: entering main routine." << endl;
    #endif

    vector<int> idsOut(3);
    vector<float> probsOut(3);
//    Block helloworldBlock(0, idsOut, probsOut);

    taskBlock Block1(1, idsOut, probsOut);
    xorBlock Block2(2, idsOut, probsOut);

//    Block1.ABBA();
//    Block2.ABBA();

    cout << endl << "Trying to make a vector of blocks" << endl << endl;

//    vector<unique_ptr<Block>> blocksVector;
//    blocksVector.reserve(2);
//    blocksVector.emplace_back(new taskBlock(0, idsOut, probsOut));
//    blocksVector.emplace_back(new xorBlock(1, idsOut, probsOut));

    vector<Block*> blocksVector(2);
    blocksVector[0] = new taskBlock(0, idsOut, probsOut);
    blocksVector[1] = new xorBlock(1, idsOut, probsOut);

    cout << endl << "Calling ABBA functions" << endl << endl;
    blocksVector[0]->ABBA();
    blocksVector[1]->ABBA();
    
    cout << "CCC START HERE "<<endl;
    Group test(1,1);
    test.create_walker(0,1,0,1,1);
    test.create_walker(0,2,0,1,1);
    test.print_status();
    cout << "CCC ENDS HERE "<<endl;
    return 0;
}
