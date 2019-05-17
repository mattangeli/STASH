#include <iostream>
#include "block.h"

using namespace std;

//Block::Block()
//{
//    #ifdef DEBUG
//        cout << "    DEBUG: new block created with empty initializer." << endl;
//    #endif
//}

Block::Block(int id, vector<int> idsOut, vector<float> probsOut) {
    if ( idsOut.size() == probsOut.size() ) {
        this->nLegsOut = (int)idsOut.size();

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
//destructor
Block::~Block () {};

taskBlock::taskBlock(int id, vector<int> idsOut, vector<float> probsOut, Wlk_Resources & res_needed_) :
    Block(id, idsOut, probsOut),
    res_needed{res_needed_} {
    //Dimension check: We want the vectors to have exactly length one for taskblock
    //The check that the vectors have the same length is done when calling block
    assert( (int)probsOut.size() == 1);
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


mergandBlock::mergandBlock(int id, vector<int> idsOut, vector<float> probsOut, vector<int> resource_types_) :
    Block(id, idsOut, probsOut),
	resource_types{resource_types_} {
    #ifdef DEBUG
        cout << "    DEBUG: block is of type mergandBlock." << endl;
    #endif
}







