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

// Constructor. The last two parameters are optional:
// - timeType        Can be 0 if the time is a constant float, or
//                   1 if it's a distribution.
// - timeParameters  It's a vector of float. If timeType is 0, then
//                   its first element contains the execution time;
//                   if timeType is 1, then its elements are the parameters
//                   of a (truncated) normal distribution in this order:
//                   mean, std, min, max.
taskBlock::taskBlock(int id, vector<int> idsOut, vector<float> probsOut, Wlk_Resources & res_needed_, unsigned int timeType_, vector<float> timeParameters_) :
    Block(id, idsOut, probsOut),
    res_needed{res_needed_},
    timeType{timeType_},
    timeParameters{timeParameters_} {
    #ifdef DEBUG
        cout << "    DEBUG: block is of type taskBlock." << endl;
    #endif
    // Check that timeType is either 0 or 1, since we don't support
    // any other types yet.
    assert(timeType<2);
    switch (timeType) {
        case 0:
            //assert(timeParameters.size() == 1); // Don't do it since the default has length 4
            #ifdef DEBUG
                cout << "    DEBUG: block processing time is " << timeParameters.at(0) << "." << endl;
            #endif
            // Initialize the processing time as a constant
            procTime = timeParameters.at(0);
            break;
        case 1:
            assert(timeParameters.size() == 4);
            // Check if min < max
            assert(timeParameters.at(2)<timeParameters.at(3));
            #ifdef DEBUG
                cout << "    DEBUG: block processing time is a truncated normal with parameters:" << endl
                     << "             mean = " << timeParameters.at(0) << "    std = " << timeParameters.at(1) << endl
                     << "             min  = " << timeParameters.at(2) << "    max = " << timeParameters.at(3) << endl;
            #endif
            // Initialize the processing time as a NORMAL distribution.
            // WARNING: since C++ has no truncated normal distribution, we have to
            //          MANUALLY truncate it. Ideally, one has to implement a proper
            //          distribution type that holds these parameters, and then remove
            //          the need of timeParameters.
            procTimeDist = normal_distribution<float>(timeParameters.at(0),timeParameters.at(1));
            break;
    }
}

float taskBlock::processing_time() {
    switch (timeType) {
        case 0:
            return procTime;
        case 1:
            {
                // Generate a normal distributed random number
                float returnedProcTime = procTimeDist(randomEngine);
                // If it's out of bound, just regenerate until it's in range.
                // Quite INEFFICIENT, but cutting to the min or max generates
                // spikes in the PDF in those points.
                while ( (returnedProcTime>timeParameters.at(3)) || (returnedProcTime<timeParameters.at(2)) ) {
                    returnedProcTime = procTimeDist(randomEngine);
                }
                return returnedProcTime;
            }
        default:
            cout << "WARNING: unknown tymeType. Returning processing time equal to 0 for block #" << id << "." << endl;
            return 0.0;
    }
}

xorBlock::xorBlock(int id, vector<int> idsOut, vector<float> probsOut, unsigned int gatewayDirection_) :
    Block(id, idsOut, probsOut),
    gatewayDirection{gatewayDirection_} {
    #ifdef DEBUG
        cout << "    DEBUG: block is of type xorBlock." << endl;
    #endif
    assert(gatewayDirection<4);
    // Some consistency checks
    // Redundant info here, but it's only at creation time so it doesn't hurt.
    switch (gatewayDirection) {
        case 0:     // Default type
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







