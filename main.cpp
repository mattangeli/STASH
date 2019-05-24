#include <iostream>
#include <vector>
#include <memory>
#include "block.h"
#include "walker.h"
#include "resources.h"
#include "adjustidsOut.h"

#ifdef DEBUG
    #include <iomanip>
    #include <algorithm>
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
   
    int nblocks{5};
    /* Initialize Blocks */
    int idTest;
    for (idTest = 0; idTest < nblocks; ++idTest) {
        blocksVector.emplace_back(new taskBlock(idTest, vector<int>(1,idTest+1), vector<float>(1,1), wlkrestest, 0, vector<float>(1,0)));
		
    }
    blocksVector.emplace_back(new taskBlock(idTest, vector<int>(1,nblocks), vector<float>(1,1), wlkrestest));

	//Here we change the signs of the destinations, depending on the resources needed
	//%%%%%%%%% To be activated when Claudio finishes his changes %%%%%%%%%%%
	//adjust_idsOut_signs( blocksVector);



    int next{2}, new_pos{0}, aux{0};
    float next_time, maxtime{100};
    Group test;
    //Temporany function, it will be removed when the blocks will be inside the group/
    test.readnblocks(nblocks);
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
      cout<< "Status"<< endl;
      test.print_status();
      

      next=test.next_operation(new_pos, next_time);
      /*      if (aux<5) {
	next=2;
	new_pos=0;
	next_time=0;
	}*/
      test.add_time_queue(next_time);
      aux++;
      if (test.get_exec_time()> maxtime) next=0;
      //      if (test.get_nwalker()==0) next=0;
      cout << "Next operation is " << next << " Total execution time " <<test.get_exec_time() << endl;
      cout << "Next time is " << next_time << endl;
    }
    cout << "Simulation completed"<< endl;



    #ifdef DEBUG
        // Xor Block Test
        cout << endl << "=============================================" << endl
             << "    DEBUG::TEST:  xorBlock test." << endl
             << "=============================================" << endl;
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

    #ifdef DEBUG
        // Task Block Time Test #1
        cout << endl << "=============================================" << endl
             << "    DEBUG::TEST:  taskBlock time test #1." << endl
             << "=============================================" << endl;
        int T1bins = 50;
        vector<int> T1outcomes(T1bins,0);
        const float T1mean = 4.0;
        const float T1std  = 0.5;
        const float T1min  = 0.0;
        const float T1max  = 10.0;
        float T1processingTime;
        const int T1nstars = 100;
        const int T1nrolls = 100000;
        taskBlock myTaskBlockDistr = taskBlock(25, vector<int>{9,5,13,15}, vector<float>(4,1.0), wlkrestest, 1, vector<float>{T1mean,T1std,T1min,T1max});
        for (int i=0; i < T1nrolls; i++) {
            T1processingTime = myTaskBlockDistr.processing_time();
            ++T1outcomes.at(round(T1processingTime*(float)T1bins/(T1max-T1min)));
        }
        cout << "    DEBUG::TEST:  TIME  P (exp)  P (exact)" << endl;
        for (int i=0; i < T1bins; i++) {
            cout << setfill(' ')  << "    DEBUG::TEST:  "
                 << setw(4) << ((T1max-T1min)/(float)T1bins)*((float)i) << "      "
                 << setw(3) << round((float)T1outcomes.at(i)*(float)nstars/(float)nrolls) << "        "
                 << setw(3) << round(exp(-0.5*pow((((T1max-T1min)/(float)T1bins)*((float)i)-T1mean)/T1std,2.0))*((float)*max_element(T1outcomes.begin(),T1outcomes.end()))*(float)nstars/(float)nrolls) << "      "
                 << string(T1outcomes.at(i)*T1nstars/T1nrolls,'*') << endl;
        }
    #endif

    #ifdef DEBUG
        // Task Block Time Test #2
        cout << endl << "=============================================" << endl
             << "    DEBUG::TEST:  taskBlock time test #2." << endl
             << "=============================================" << endl;
        int T2bins = 20;
        vector<int> T2outcomes(T2bins,0);
        const float T2mean = 4.0;
        const float T2std  = 1E-15;
        const float T2min  = 0.0;
        const float T2max  = 8.0;
        float T2processingTime;
        const int T2nstars = 10;
        const int T2nrolls = 100000;
        taskBlock myTaskBlockConst = taskBlock(26, vector<int>{9,5,13,15}, vector<float>(4,1.0), wlkrestest, 0, vector<float>{T2mean});
        for (int i=0; i < T2nrolls; i++) {
            T2processingTime = myTaskBlockConst.processing_time();
            ++T2outcomes.at(round(T2processingTime*(float)T2bins/(T2max-T2min)));
        }
        cout << "    DEBUG::TEST:  TIME  P (exp)  P (exact)" << endl;
        for (int i=0; i < T2bins; i++) {
            cout << setfill(' ')  << "    DEBUG::TEST:  "
                 << setw(4) << ((T2max-T2min)/(float)T2bins)*((float)i) << "      "
                 << setw(3) << round((float)T2outcomes.at(i)*(float)nstars/(float)nrolls) << "        "
                 << setw(3) << round(exp(-0.5*pow((((T2max-T2min)/(float)T2bins)*((float)i)-T2mean)/T2std,2.0))*((float)*max_element(T2outcomes.begin(),T2outcomes.end()))*(float)nstars/(float)nrolls) << "      "
                 << string(T2outcomes.at(i)*T2nstars/T2nrolls,'*') << endl;
        }
    #endif

    #ifdef DEBUG
        // Task Block Time Test #3
        cout << endl << "=============================================" << endl
             << "    DEBUG::TEST:  taskBlock time test #3." << endl
             << "=============================================" << endl;
        int T3bins = 20;
        vector<int> T3outcomes(T3bins,0);
        const float T3mean = 0.0;
        const float T3std  = 1E-15;
        const float T3min  = 0.0;
        const float T3max  = 8.0;
        float T3processingTime;
        const int T3nstars = 10;
        const int T3nrolls = 100000;
        taskBlock myTaskBlockConst0 = taskBlock(26, vector<int>{9,5,13,15}, vector<float>(4,1.0), wlkrestest);
        for (int i=0; i < T3nrolls; i++) {
            T3processingTime = myTaskBlockConst0.processing_time();
            ++T3outcomes.at(round(T3processingTime*(float)T3bins/(T3max-T3min)));
        }
        cout << "    DEBUG::TEST:  TIME  P (exp)  P (exact)" << endl;
        for (int i=0; i < T3bins; i++) {
            cout << setfill(' ')  << "    DEBUG::TEST:  "
                 << setw(4) << ((T3max-T3min)/(float)T3bins)*((float)i) << "      "
                 << setw(3) << round((float)T3outcomes.at(i)*(float)nstars/(float)nrolls) << "        "
                 << setw(3) << round(exp(-0.5*pow((((T3max-T3min)/(float)T3bins)*((float)i)-T3mean)/T3std,2.0))*((float)*max_element(T3outcomes.begin(),T3outcomes.end()))*(float)nstars/(float)nrolls) << "      "
                 << string(T3outcomes.at(i)*T3nstars/T3nrolls,'*') << endl;
        }
    #endif



 	

    return 0;
}



