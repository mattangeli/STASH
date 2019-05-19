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
    #ifdef DEBUG
        cout << "    DEBUG: block is of type taskBlock." << endl;
    #endif
    //Dimension check: We want the vectors to have exactly length one for taskblock
    //The check that the vectors have the same length is done when calling block
    assert( (int)probsOut.size() == 1);
}

xorBlock::xorBlock(int id, vector<int> idsOut, vector<float> probsOut, int gatewayDirection_) :
    Block(id, idsOut, probsOut),
    gatewayDirection{gatewayDirection_} {
    #ifdef DEBUG
        cout << "    DEBUG: block is of type xorBlock." << endl;
    #endif
    // Some consistency checks
    // Redundant info here, but it's only at creation time so it doesn't hurt.
    switch (gatewayDirection) {
        case 0:
            #ifdef DEBUG
                cout << "    DEBUG: gatewayDirection -> Unspecified." << endl;
            #endif
            break;
        case 1:
            #ifdef DEBUG
                cout << "    DEBUG: gatewayDirection -> Converging." << endl;
            #endif
            assert( nLegsOut <= 1 );
            break;
        case 2:
            #ifdef DEBUG
                cout << "    DEBUG: gatewayDirection -> Diverging." << endl;
            #endif
            break;
        case 3:
            #ifdef DEBUG
                cout << "    DEBUG: gatewayDirection -> Mixed." << endl;
            #endif
            break;
    }
    probsOutDist = discrete_distribution<int>(probsOut.begin(),probsOut.end());
}


mergandBlock::mergandBlock(int id, vector<int> idsOut, vector<float> probsOut, vector<int> resource_types_) :
    Block(id, idsOut, probsOut),
	resource_types{resource_types_} {
    #ifdef DEBUG
        cout << "    DEBUG: block is of type mergandBlock." << endl;
    #endif
}







