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
    tot_res[0] = 2;
    Resources global_res(tot_res);
    Wlk_Resources wlkrestest_no(1);
    Wlk_Resources wlkrestest_one(1);
    wlkrestest_no.set(0,0);
    wlkrestest_one.set(0,1);
    //vector<unique_ptr<Block>> blocksVector;
    //blocksVector.reserve(9);
    vector<Block*> blocksVector(10);

    taskBlock testtask(8, vector<int>(1,6), vector<float>(1,1), wlkrestest_one);
    auto yoloneeds1 = testtask.get_res_needed( 1 );
    cout << "Yolo block needs " << yoloneeds1.get_resources(0) << endl;

    /* Initialize Blocks */
    int idTest;
    for (idTest = 0; idTest < 10; ++idTest) {
	if ( idTest % 2 == 0) {
        	//blocksVector.emplace_back(new taskBlock(idTest, vector<int>(1,idTest+1), vector<float>(1,1), wlkrestest_no));
		blocksVector[idTest] = (new taskBlock(idTest, vector<int>(1,idTest+1), vector<float>(1,1), wlkrestest_no));
	}
	else {
		//blocksVector.emplace_back(new taskBlock(idTest, vector<int>(1,idTest+1), vector<float>(1,1), wlkrestest_one));
		blocksVector[idTest] = (new taskBlock(idTest, vector<int>(1,idTest+1), vector<float>(1,1), wlkrestest_one));
	}
	
    }
    //blocksVector.emplace_back(new taskBlock(idTest, vector<int>(1,-1), vector<float>(1,1), wlkrestest_no));
	blocksVector[9] = (new taskBlock(idTest, vector<int>(1,-1), vector<float>(1,1), wlkrestest_no));

	auto yolo = *blocksVector[2];
	auto outvec = yolo.get_idsOut();
	cout << "Yolo The outvector is " << outvec[0] << endl;
	auto yoloneeds = yolo.get_res_needed( 1 );
	cout << "Yolo block needs " << yoloneeds.get_resources(0) << endl;

    int next{2}, new_pos{0}, aux{0};
    float next_time;
    Group test;
	//next identifies the next action (0 stop, 1 terminate process, 2 create walker in position
	// new_pos


    while (next!=0){

      cout << "Total simulation step " << aux << " Walker at the step " << test.get_nwalker()<< endl;
      if (next==1) {
	test.check_stop_evolve(global_res); //here we free resources
      }
      if (next==2) test.create_walker(new_pos, test.get_nwalker(), 
				      test.get_nwalker(), global_res.get_ntype());
      test.check_queue(global_res, blocksVector);
      //remove for a huge performance improvement
      cout<< "Status"<< endl;
      test.print_status();
      next=test.next_operation(new_pos, next_time);
      if (aux<50) {
	next=2;
	new_pos=0;
	next_time=0;
      }
      test.add_time_queue(next_time);
      aux++;
      if (test.get_nwalker()==0) next=0;
      cout << "Next operation is " << next << " Total execution time " <<test.get_exec_time() << endl;
    }
    cout << "Simulation completed"<< endl;

 	

    return 0;
}
