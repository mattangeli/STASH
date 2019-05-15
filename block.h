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

    virtual void resources_allocate(Resources&) {
        cout << "I don't think it works" << endl;
    }

    virtual void resources_release(Resources&) {
        cout << "Me neither" << endl;
    }

    virtual Wlk_Resources get_res_needed(int len) {
        return Wlk_Resources(len);
    }

	vector<int> get_idsOut() {
		return idsOut;
	}



	//Return time needed for this Block
	//Standard is 0 (time needed for gates)
	virtual float processing_time() {
		return 0.0;
	}



	virtual int get_block_info(Wlk_Resources&, vector<int>& destinations , float & time ) {
        cout << "get_block_info function not specialized. Define it for your block" << endl;
        return 1; //add to make a warnong silent
	}

	/*
	The next function returns whether or not we can continue
	to the next Block. This is important,
	since at the merging AND gate we might need
	to wait until we have processes in all (both)
	incoming legs. The standard is true, since taskgates
	have only one incoming leg and so we don't need to wait.
	NOTE: This is not related to resources in any way.
	HOWEVER: We can implement this using resources:
	Consider the following scenario:

			  ______
		A-->--|     |
			  | AND |--->--- C  
		B-->--|_____|

	Now we could make a resource type for both incoming legs A and B.
	One a process arrives at the gate, we increase the respective resource 
	type by one quantitiy. Moreover we can say that the AND gate is a process
	that requires one resource of type A and one of type B. 
	If they are available, we take them and we can continue to C. 
	Note that this process is destroying a walker. 
	To do it with the resources we need to tell the gate at initialization which are 
	the resource types that belong to the gate.	
	

	//DON'T USE THIS FUNCTION, NOT FINISHED YET
	virtual bool can_continue() {
		return true;
	}
	*/

};


/* Generic task block */
class taskBlock : public Block {
private:
    Wlk_Resources res_needed;
    Wlk_Resources res_occup;
public:
    taskBlock(int, vector<int>, vector<float>, Wlk_Resources &);
    void ABBA() {
        cout << "I'm a taskBlock and I suck!" << endl;
    }


    Wlk_Resources get_res_needed(int len) {
        return res_needed;
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
