#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <cassert>
#include <random>
#include "resources.h"
#include "Wlk_Resources.h"


using namespace std;

/*--------------------
      Block Class
--------------------*/

/*---------------------------------------------------------------------------
  Class defines the building element (block) of every BMPN diagram.
  It contains the indices of the next blocks to which the current one is
  connected and the transition probabilities between blocks. It also provides
  methods for allocating and releasing resources.
  Specializations of a generic block are contained here for the time being.
---------------------------------------------------------------------------*/


/* Generic block */
class Block {
protected:
    int id;
    int nLegsOut;
    vector<int> idsOut;
    vector<float> probsOut;
public:
    Block(int, vector<int>, vector<float>);
    //destructor
    virtual ~Block ();
    virtual Wlk_Resources get_res_needed(int len) {
        return Wlk_Resources(len);
    }
	vector<int> get_idsOut() {
		return idsOut;
	}
	virtual bool do_need_resources() const {
		return false;
	}
    // Virtual function that returns the next id(s) where
    // we have to go. Each block type must specify it.
    // The default is to return EVERY outgoing leg, so
    // it works for the taskBlock.
    virtual vector<int> idNext() {
        return idsOut;
    }
	//Nonvirtual function to make sign 
	//of elements in the idsOut vector negative:
	//Does not change sign, but always makes it negative
	void make_idOut_negative(int const index) {
		assert(index<nLegsOut);
		idsOut[index] = -abs(idsOut[index]); 
	}
	//Return time needed for this Block
	//Standard is 0 (time needed for gates)
	virtual float processing_time() {
		return 0.0;
	}
};


/* Generic task block */
class taskBlock : public Block {
private:
    Wlk_Resources res_needed;
    unsigned int timeType = 0;
    vector<float> timeParameters = {0,0,0,0};
    float procTime = 0.0;
    default_random_engine randomEngine = default_random_engine(time(NULL));
    normal_distribution<float> procTimeDist;
public:
    taskBlock(int, vector<int>, vector<float>, Wlk_Resources &, unsigned int = 0, vector<float> = {0,0,0,0});
    Wlk_Resources get_res_needed(int len) {
        return res_needed;
    }
	//Return if taskblock needs resources. 
	//Pay attention to the NOT when returning
	bool do_need_resources() const {
		return (!res_needed.are_res_zero());
	}
	//Return the time needed to complete this task
    float processing_time();
};


/* Exclusive gateway */
class xorBlock : public Block {
private:
    /* Same property as the BPMN standard.
       0    Unspecified
       1    Converging -> no more than 1 outLeg
       2    Diverging  -> no more than 1 inLeg
       3    Mixed
    */
    unsigned int gatewayDirection = 0;
    /* Probability distribution object.
       randomEngine is a sort of seed, while probsOutDist
       is a distribution that returns numbers from 0 to nLegsOut-1
       distributed according to probsOut. Note that probsOut do not
       necessarily have to be probabilities; if e.g. all the elements
       are 1 or 2 or X, then the outcomes are equally distributed.
       The case in which the elements of probsOut are normalized to 1
       is just a particular case.
     */
    default_random_engine randomEngine = default_random_engine(time(NULL));
    discrete_distribution<int> probsOutDist;
public:
    xorBlock(int, vector<int>, vector<float>, unsigned int = 0);
    // Don't need to specify do_need_resources()
    // and processing_time(), since the defaults
    // are already meant for the gates.

    // Function that tells you where you go that Davide has to implement.
    // It basically picks up one of the idsOut at random or based on
    // the probsOut.
    vector<int> idNext() {
        return vector<int>{(int)idsOut.at(probsOutDist(randomEngine))};
    }
};


/* Merging AND gateway */
class mergandBlock : public Block {
private:    
	vector<int> resource_types;
public:
    mergandBlock(int, vector<int>, vector<float>, vector<int>);
};


#endif // BLOCK_H



