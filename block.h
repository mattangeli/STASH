#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <cassert>
#include "resources.h"
#include "Wlk_Resources.h"
#include "walker.h"

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
    virtual void ABBA() {
        cout << "I'm a Block and you are a Block." << endl;
    }

    virtual void resources_allocate(Resources&) {
        cout << "I don't think it works" << endl;
    }

    virtual void resources_release(Resources&) {
        cout << "Me neither" << endl;
    }

    virtual vector<int> get_needed_res(int length) {
        vector<int> outvec(length,0);
        return outvec;
    }

    int get_next_id() {
        return idsOut[0];
    }

	//Return time needed for this Block
	//Standard is 0 (time needed for gates)
	virtual float processing_time() {
		return 0.0;
	}



	virtual int get_block_info(Wlk_Resources&, vector<int>& destinations , float & time ) {
		cout << "get_block_info function not specialized. Define it for your block" << endl;	
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

    /*
    OLD IDEA, WE DONT NEED THAT
    //We need a function that checks if we have
    //the resources to do this specific task.
    //This means that every block also needs a member where
    //we store what the block needs. This could be a vector, where
    //at each index there is a different type of resource and the
    //number at this index tells us how much of it we need.
    //We might make this function private and use it in another function
    //which is executing all functions (resource check+allocation),
    //walker processing...
    //Maybe make a public function for process start and one
    //for process end.
    bool resoureces_avail(Resources resource_) { //The input needs to be a resource type
    if true { //this has to be replaced }
    //Actually it could be something like (pseudocode)
    //if all(vec_resouce_needed(:) <= resource_.avail(:)) {
    //Alternatively we don't check and we just allocate all the
    //available resources that we need. If not all are available
    //we wait until the rest is available (but we already have reserved
    //the ones that are available.
        return true;
        cout << "The resources requested are available" << endl;
    }
    else {
        return false;
        cout << "Resources NOT available" << endl;
    }
    }

*/

/*

    // Allocate resources 
    void resources_allocate(Resources& resource_) {
        cout << "Allocating resources for Block " << id << endl;
        resource_.res_allocate(res_needed, res_occup);
    }

    // After finishing the process we want to release the resources.
    void resources_release(Resources& resource_) {
        cout << "Releasing the resources of Block " << id << endl;
        resource_.res_release(res_occup);
    }

    vector<int> get_needed_res(int length) {
        if (length != (int)res_needed.size()) {
            cout << "Integer provided to get_needed_res does not agree with resource vector length" << endl;
        }
        return res_needed;
    }

*/

	//Return the time needed to complete this task
	float processing_time() {
		//Here we should get a random number according to some distribution
		return id*3.14159265359;
	}


	int get_block_info(Group & the_group, const int id, vector<int>& destinations , float & time, Resources & global_res ) {

		the_group.add_res(id,res_needed,&global_res);
		destinations = idsOut;
		time = id*3.14159265359; //Here we need to adjust

		return 0; // Return 


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
