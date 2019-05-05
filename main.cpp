#include <iostream>
#include <vector>
#include <memory>
#include "block.h"
#include "walker.h"
#include "resources.h"


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
    Resources global_res(tot_res);
    Wlk_Resources wlkrestest(1);
    wlkrestest.set(0,0);
    vector<unique_ptr<Block>> blocksVector;
    blocksVector.reserve(3);

    /* Initialize Blocks */
    int idTest;
    for (idTest = 0; idTest < 4; ++idTest) {
        blocksVector.emplace_back(new taskBlock(idTest, vector<int>(1,idTest+1), vector<float>(1,1), wlkrestest));
    }
    blocksVector.emplace_back(new taskBlock(idTest, vector<int>(1,-1), vector<float>(1,1), wlkrestest));

    int next{2}, new_pos{0};
    float next_time;
    Group test;
	//next identifies the next action (0 stop, 1 terminate process, 2 create walker in position
	// new_pos
    while (next!=0){
      cout << next << endl;
      if (next==1) {
	test.check_stop_evolve(global_res); //here we free resources
      }
      if (next==2) test.create_walker(new_pos, test.get_nwalker(), 
				      test.get_nwalker(), global_res.get_ntype());
      test.print_status();
      test.check_queue(global_res, blocksVector);
      next=test.next_operation(new_pos, next_time);
      test.add_time_queue(next_time);
      cout << "Next" << next<< " " <<test.get_exec_time() << endl;
    }

 	

    return 0;
}
