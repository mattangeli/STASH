#include <iostream>
#include <vector>
#include <memory>
#include "block.h"
#include "walker.h"
#include "resources.h"
#include "adjustidsOut.h"

#ifdef DEBUG
    #include <iomanip>
#endif


using namespace std;



int main()
{
    #ifdef DEBUG
        cout << "    DEBUG: entering main routine." << endl;
    #endif



    
    vector<int> tot_res(1);
    tot_res[0]=1;
    Resources global_res(tot_res);
    Wlk_Resources wlkrestest(1);
	Wlk_Resources wlkres_zero(1);
    wlkrestest.set(0,1);
    vector<unique_ptr<Block>> blocksVector;
    //blocksVector.reserve(9); I think we do not need that
   
    int nblocks{5};
    /* Initialize Blocks */
    int idTest;
    for (idTest = 0; idTest < nblocks; ++idTest) {

		if (idTest == 3) {
			blocksVector.emplace_back(new taskBlock(idTest, vector<int>(1,idTest+1), vector<float>(1,1), wlkrestest));
		}
		else
			blocksVector.emplace_back(new taskBlock(idTest, vector<int>(1,idTest+1), vector<float>(1,1), wlkres_zero));
		
    }
    blocksVector.emplace_back(new taskBlock(idTest, vector<int>(1,nblocks), vector<float>(1,1), wlkres_zero));

	//Here we change the signs of the destinations, depending on the resources needed
	//Negative sign means that no resources are needed for the next block 
	//and therefore the process has to be put to the top of the queue.
	adjust_idsOut_signs( blocksVector);



    int next{99}, new_pos{0}, aux{0};
    float next_time, maxtime{50};
    Group test( blocksVector );
    //Temporany function, it will be removed when the blocks will be inside the group/
    test.readnblocks(nblocks);
	//next identifies the next action:
	// 0: stop 
	// 1: terminate process
	// 2: create new walker


	while (next!=0){

		//cout << "Total simulation step " << aux << " Walker at the step " << test.get_nwalker()<< endl;
		if (next==1) {
			//Stop one or more processes. Walkers reaching the end are killed
			//The walker is put into the queue for the next block, 
			//either on top if no resources are needed or to the end otherwise
			test.check_stop_evolve(global_res); 
		}
		if (next==2) {
			test.create_walker(new_pos, test.get_nwalker(), 
				      test.get_nwalker(), global_res.get_ntype());
		}

		//Go through the queue and start the walkers being able to start
		test.check_queue(global_res);

		//Find the next operation: Possible (int) returns:
		//1: Stop one or more processes
		//2: Create a new walker
		//next_time returns the time from now until we do this action
		next=test.next_operation(new_pos, next_time);

		//Move globaly to this time 
		test.add_time_queue(next_time);
		aux++;
		if (test.get_exec_time()> maxtime) next=0;
		//      if (test.get_nwalker()==0) next=0;
		//cout << "Next operation is " << next << " Total execution time " <<test.get_exec_time() << endl;
    }
    cout << "Simulation completed"<< endl;



    #ifdef DEBUG
        // Xor Block Test
        int outcomes[16]={};
        int nextId; // from 0 to 15
        const int nstars = 100;
        const int nrolls = 100000;
        xorBlock myXorBlock = xorBlock(20, vector<int>{9,5,13,15}, vector<float>{0.25,0.25,0.5,0});
        for (int i=0; i < nrolls; i++) {
            nextId = myXorBlock.idNext()[0];
            //cout << "    DEBUG::TEST:  Next id " << nextId << endl;
            ++outcomes[nextId];
        }
        cout << "    DEBUG::TEST:  ID    P (%)" << endl;
        for (int i=0; i < 16; i++) {
            cout << setfill(' ')  << "    DEBUG::TEST:  " << setw(2) << i << "    " << setw(3) << outcomes[i]*nstars/nrolls << "    " << string(outcomes[i]*nstars/nrolls,'*') << endl;
        }
    #endif



 	

    return 0;
}



