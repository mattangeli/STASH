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


//    vector<int> idsOut(3);
//    vector<float> probsOut(3);
////    Block helloworldBlock(0, idsOut, probsOut);

//	idsOut[0]= 656;
//	idsOut[1]= 2;
//	idsOut[2]= 7;

//	vector<int> res_tot(3);
//	vector<int> res_need1(3);
//	vector<int> res_need2(3);

//	res_tot[0] = 2;
//	res_tot[1] = 3;
//	res_tot[2] = 4;

//	res_need1[0] = 1;
//	res_need1[1] = 2;
//	res_need1[2] = 3;

//	res_need2[0] = 1;
//	res_need2[1] = 3;
//	res_need2[2] = 4;

//	Resources res_type(res_tot);

//	Wlk_Resources wlkrestest(3);
//	wlkrestest.set(0,1);
//	wlkrestest.set(1,2);
//	wlkrestest.set(2,3);


    
    vector<int> tot_res(1);
    tot_res[0]=4;
    Resources global_res(tot_res);
    Wlk_Resources wlkrestest(1);
    wlkrestest.set(0,2);
    vector<unique_ptr<Block>> blocksVector;
    //blocksVector.reserve(9); I think we do not need that
	

    /* Initialize Blocks */
    int idTest;
    for (idTest = 0; idTest < 10; ++idTest) {
		blocksVector.emplace_back(new taskBlock(idTest, vector<int>(1,idTest+1), vector<float>(1,1), wlkrestest));
		
    }
    blocksVector.emplace_back(new taskBlock(idTest, vector<int>(1,-1), vector<float>(1,1), wlkrestest));

	//Here we change the signs of the destinations, depending on the resources needed
	//%%%%%%%%% To be activated when Claudio finishes his changes %%%%%%%%%%%
	//adjust_idsOut_signs( blocksVector);



    int next{2}, new_pos{0}, aux{0};
    float next_time;
    Group test;
	//next identifies the next action (0 stop, 1 terminate process, 2 create walker in position
	// new_pos


    while (next!=0){

      //cout << "Total simulation step " << aux << " Walker at the step " << test.get_nwalker()<< endl;
      if (next==1) {
	test.check_stop_evolve(global_res); //here we free resources
      }
      if (next==2) test.create_walker(new_pos, test.get_nwalker(), 
				      test.get_nwalker(), global_res.get_ntype());
      test.check_queue(global_res, blocksVector);
      //remove for a huge performance improvement
      //cout<< "Status"<< endl;
      //test.print_status();
      next=test.next_operation(new_pos, next_time);
      if (aux<5) {
	next=2;
	new_pos=0;
	next_time=0;
      }
      test.add_time_queue(next_time);
      aux++;
      if (test.get_nwalker()==0) next=0;
      //cout << "Next operation is " << next << " Total execution time " <<test.get_exec_time() << endl;
    }
    cout << "Simulation completed"<< endl;



    #ifdef DEBUG
        // Xor Block Test
        int outcomes[16]={};
        int nextId; // from 0 to 15
        const int nstars = 100;
        const int nrolls = 100000;
        xorBlock myXorBlock = xorBlock(20, vector<int>{9,5,13,15}, vector<float>{0.25,0.25,0.5,0}, 0);
        for (int i=0; i < nrolls; i++) {
            nextId = myXorBlock.idNext();
            //cout << "    DEBUG::TEST: Next id " << nextId << endl;
            ++outcomes[nextId];
        }
        cout << "    DEBUG::TEST: ID     P (%)" << endl;
        for (int i=0; i < 16; i++) {
            cout << setfill('0')  << "    DEBUG::TEST: " << setw(2) << i << ":    " << setw(3) << outcomes[i]*nstars/nrolls << "    " << string(outcomes[i]*nstars/nrolls,'*') << endl;
        }
    #endif



 	

    return 0;
}



