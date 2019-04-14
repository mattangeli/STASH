#include <iostream>
#include "block.h"

using namespace std;

//Block::Block()
//{
//    #ifdef DEBUG
//        cout << "    DEBUG: new block created with empty initializer." << endl;
//    #endif
//}

Block::Block(int id, vector<int> idsOut, vector<float> probsOut)
{
    if ( idsOut.size() == probsOut.size() ) {
        this->nLegsOut = idsOut.size();

        this->id = id;
        this->idsOut = idsOut;
        this->probsOut = probsOut;

        #ifdef DEBUG
            cout << "    DEBUG: new block created with id " << this->id << "." << endl;
            cout << "    DEBUG: the number of outer legs in the Block is " << this->nLegsOut << "." << endl;
        #endif


    } else {
        cout << "You are an idiot, the length of the input vectors in the Block class idsOut is not the same as probsOut!" << endl;
    }
}

taskBlock::taskBlock(int id, vector<int> idsOut, vector<float> probsOut, vector<int> res_needed_) :
    Block(id, idsOut, probsOut),
	res_needed{res_needed_},
	res_occup(res_needed_.size(),0) {
        #ifdef DEBUG
            cout << "    DEBUG: block is of type taskBlock." << endl;
         #endif
}

xorBlock::xorBlock(int id, vector<int> idsOut, vector<float> probsOut) :
    Block(id, idsOut, probsOut) {
        #ifdef DEBUG
            cout << "    DEBUG: block is of type xorBlock." << endl;
         #endif
}


