#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <cassert>
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
    virtual void ABBA() {
        cout << "I'm a Block and you are a Block." << endl;
    }


    virtual Wlk_Resources get_res_needed(int len) {
        return Wlk_Resources(len);
    }

	vector<int> get_idsOut() {
		return idsOut;
	}

	virtual bool do_need_resources() const {
		return false;
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
public:
    taskBlock(int, vector<int>, vector<float>, Wlk_Resources &);
    void ABBA() {
        cout << "I'm a taskBlock and I suck!" << endl;
    }


    Wlk_Resources get_res_needed(int len) {
        return res_needed;
    }

	//Return if taskblock needs resources. 
	//Pay attention to the NOT when returning
	bool do_need_resources() const {
		return (!res_needed.are_res_zero());
	}

	//Return the time needed to complete this task
	float processing_time() {
		//Here we should get a random number according to some distribution
		return id*3.14159265359;
	}


};


/* Exclusive gateway */
class xorBlock : public Block {
private:    
public:
    xorBlock(int, vector<int>, vector<float>);
    void ABBA() {
        cout << "I'm a xorBlock and I suck even more!" << endl;
    }
};


/* Merging AND gateway */
class mergandBlock : public Block {
private:    
	vector<int> resource_types;
public:
    mergandBlock(int, vector<int>, vector<float>, vector<int>);
    void ABBA() {
        cout << "I'm a mergand Block and I suck the most!" << endl;
    }
};





#endif // BLOCK_H



