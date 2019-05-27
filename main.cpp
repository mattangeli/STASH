#include <iostream>
#include <vector>
#include <memory>
#include "block.h"
#include "walker.h"
#include "resources.h"
#include "adjustidsOut.h"
#include <limits>
#include <string>
#include <libconfig.h++>

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

    float huge = numeric_limits<float>::max();
    cout << "huge= " << huge << endl;

    /* ---------------------------
     * CONFIGURATION FILE :: BEGIN
     * ---------------------------
     */

    /* Configuration file filename */
    string inputconfigFileName = "input.cfg";
    string inputconfigexampleFileName = "input.example.cfg";
    /* Configuration file object */
    libconfig::Config inputConf;

    try {
        inputConf.readFile(inputconfigFileName.c_str());
        cout << "The configuration was read from '" << inputconfigFileName << "'." << endl;
    } catch (const libconfig::FileIOException &fioex) {
        //throw new libconfig::FileIOException;
        //exit(EXIT_FAILURE);
        cerr << "Cannot read the configuration file '" << inputconfigFileName << "': using a standard configuration '" << inputconfigexampleFileName << "' instead." << endl;
        // Populate the config file.
        libconfig::Setting &inputConfigRoot = inputConf.getRoot();
        // Global Settings
        libconfig::Setting &globalSettings = inputConfigRoot.add("globalSettings", libconfig::Setting::TypeGroup);
        globalSettings.add("maxTime", libconfig::Setting::TypeFloat) = 1440.0;
        // Block 00
        {
            libconfig::Setting &currentBlock = inputConfigRoot.add("taskBlock_00", libconfig::Setting::TypeGroup);
            currentBlock.add("timeType", libconfig::Setting::TypeInt) = 1;
            currentBlock.add("timeMean", libconfig::Setting::TypeFloat) = 4.0;
            currentBlock.add("timeStd", libconfig::Setting::TypeFloat) = 0.5;
            currentBlock.add("timeMin", libconfig::Setting::TypeFloat) = 0.0;
            currentBlock.add("timeMax", libconfig::Setting::TypeFloat) = huge;
        }
        // Block 01
        {
            libconfig::Setting &currentBlock = inputConfigRoot.add("xorBlock_01", libconfig::Setting::TypeGroup);
            currentBlock.add("probOut_02", libconfig::Setting::TypeFloat) = 0.6;
            currentBlock.add("probOut_04", libconfig::Setting::TypeFloat) = 0.4;
        }
        // Block 02
        {
            libconfig::Setting &currentBlock = inputConfigRoot.add("taskBlock_02", libconfig::Setting::TypeGroup);
            currentBlock.add("timeType", libconfig::Setting::TypeInt) = 1;
            currentBlock.add("timeMean", libconfig::Setting::TypeFloat) = 10.0;
            currentBlock.add("timeStd", libconfig::Setting::TypeFloat) = 2.5;
            currentBlock.add("timeMin", libconfig::Setting::TypeFloat) = 0.0;
            currentBlock.add("timeMax", libconfig::Setting::TypeFloat) = huge;
        }
        // Block 03
        {
            libconfig::Setting &currentBlock = inputConfigRoot.add("xorBlock_03", libconfig::Setting::TypeGroup);
            currentBlock.add("probOut_NB", libconfig::Setting::TypeFloat) = 0.85;
            currentBlock.add("probOut_00", libconfig::Setting::TypeFloat) = 0.15;
        }
        // Block 04
        {
            libconfig::Setting &currentBlock = inputConfigRoot.add("taskBlock_04", libconfig::Setting::TypeGroup);
            currentBlock.add("timeType", libconfig::Setting::TypeInt) = 0;
            currentBlock.add("timeMean", libconfig::Setting::TypeFloat) = 0.0;
            currentBlock.add("timeStd", libconfig::Setting::TypeFloat) = 0.0;
            currentBlock.add("timeMin", libconfig::Setting::TypeFloat) = 0.0;
            currentBlock.add("timeMax", libconfig::Setting::TypeFloat) = 0.0;
        }
        // Block 05
        {
            libconfig::Setting &currentBlock = inputConfigRoot.add("taskBlock_05", libconfig::Setting::TypeGroup);
            currentBlock.add("timeType", libconfig::Setting::TypeInt) = 0;
            currentBlock.add("timeMean", libconfig::Setting::TypeFloat) = 0.5;
            currentBlock.add("timeStd", libconfig::Setting::TypeFloat) = 0.0;
            currentBlock.add("timeMin", libconfig::Setting::TypeFloat) = 0.0;
            currentBlock.add("timeMax", libconfig::Setting::TypeFloat) = 0.0;
        }
        // Block 06
        {
            libconfig::Setting &currentBlock = inputConfigRoot.add("taskBlock_06", libconfig::Setting::TypeGroup);
            currentBlock.add("timeType", libconfig::Setting::TypeInt) = 1;
            currentBlock.add("timeMean", libconfig::Setting::TypeFloat) = 4.0;
            currentBlock.add("timeStd", libconfig::Setting::TypeFloat) = 0.5;
            currentBlock.add("timeMin", libconfig::Setting::TypeFloat) = 0.0;
            currentBlock.add("timeMax", libconfig::Setting::TypeFloat) = huge;
        }
        // Block 07
        {
            libconfig::Setting &currentBlock = inputConfigRoot.add("xorBlock_07", libconfig::Setting::TypeGroup);
            currentBlock.add("probOut_08", libconfig::Setting::TypeFloat) = 0.7;
            currentBlock.add("probOut_09", libconfig::Setting::TypeFloat) = 0.3;
        }
        // Block 08
        {
            libconfig::Setting &currentBlock = inputConfigRoot.add("taskBlock_08", libconfig::Setting::TypeGroup);
            currentBlock.add("timeType", libconfig::Setting::TypeInt) = 1;
            currentBlock.add("timeMean", libconfig::Setting::TypeFloat) = 1.0;
            currentBlock.add("timeStd", libconfig::Setting::TypeFloat) = 0.5;
            currentBlock.add("timeMin", libconfig::Setting::TypeFloat) = 0.0;
            currentBlock.add("timeMax", libconfig::Setting::TypeFloat) = huge;
        }
        // Block 09
        {
            libconfig::Setting &currentBlock = inputConfigRoot.add("taskBlock_09", libconfig::Setting::TypeGroup);
            currentBlock.add("timeType", libconfig::Setting::TypeInt) = 0;
            currentBlock.add("timeMean", libconfig::Setting::TypeFloat) = 0.5;
            currentBlock.add("timeStd", libconfig::Setting::TypeFloat) = 0.0;
            currentBlock.add("timeMin", libconfig::Setting::TypeFloat) = 0.0;
            currentBlock.add("timeMax", libconfig::Setting::TypeFloat) = 0.0;
        }
        // Block 10
        {
            libconfig::Setting &currentBlock = inputConfigRoot.add("taskBlock_10", libconfig::Setting::TypeGroup);
            currentBlock.add("timeType", libconfig::Setting::TypeInt) = 1;
            currentBlock.add("timeMean", libconfig::Setting::TypeFloat) = 7.0;
            currentBlock.add("timeStd", libconfig::Setting::TypeFloat) = 1.0;
            currentBlock.add("timeMin", libconfig::Setting::TypeFloat) = 0.0;
            currentBlock.add("timeMax", libconfig::Setting::TypeFloat) = huge;
        }
        // Block 11
        {
            libconfig::Setting &currentBlock = inputConfigRoot.add("xorBlock_11", libconfig::Setting::TypeGroup);
            currentBlock.add("probOut_12", libconfig::Setting::TypeFloat) = 0.8;
            currentBlock.add("probOut_13", libconfig::Setting::TypeFloat) = 0.2;
        }
        // Block 12
        {
            libconfig::Setting &currentBlock = inputConfigRoot.add("taskBlock_12", libconfig::Setting::TypeGroup);
            currentBlock.add("timeType", libconfig::Setting::TypeInt) = 1;
            currentBlock.add("timeMean", libconfig::Setting::TypeFloat) = 1.0;
            currentBlock.add("timeStd", libconfig::Setting::TypeFloat) = 0.5;
            currentBlock.add("timeMin", libconfig::Setting::TypeFloat) = 0.0;
            currentBlock.add("timeMax", libconfig::Setting::TypeFloat) = huge;
        }
        // Block 13
        {
            libconfig::Setting &currentBlock = inputConfigRoot.add("taskBlock_13", libconfig::Setting::TypeGroup);
            currentBlock.add("timeType", libconfig::Setting::TypeInt) = 1;
            currentBlock.add("timeMean", libconfig::Setting::TypeFloat) = 3.0;
            currentBlock.add("timeStd", libconfig::Setting::TypeFloat) = 1.0;
            currentBlock.add("timeMin", libconfig::Setting::TypeFloat) = 0.0;
            currentBlock.add("timeMax", libconfig::Setting::TypeFloat) = huge;
        }
        // Block 14
        {
            libconfig::Setting &currentBlock = inputConfigRoot.add("taskBlock_14", libconfig::Setting::TypeGroup);
            currentBlock.add("timeType", libconfig::Setting::TypeInt) = 1;
            currentBlock.add("timeMean", libconfig::Setting::TypeFloat) = 300.0;
            currentBlock.add("timeStd", libconfig::Setting::TypeFloat) = 30.0;
            currentBlock.add("timeMin", libconfig::Setting::TypeFloat) = 0.0;
            currentBlock.add("timeMax", libconfig::Setting::TypeFloat) = huge;
        }
        // Block 15
        {
            libconfig::Setting &currentBlock = inputConfigRoot.add("taskBlock_15", libconfig::Setting::TypeGroup);
            currentBlock.add("timeType", libconfig::Setting::TypeInt) = 1;
            currentBlock.add("timeMean", libconfig::Setting::TypeFloat) = 2.0;
            currentBlock.add("timeStd", libconfig::Setting::TypeFloat) = 0.5;
            currentBlock.add("timeMin", libconfig::Setting::TypeFloat) = 0.0;
            currentBlock.add("timeMax", libconfig::Setting::TypeFloat) = huge;
        }
        // Write the config file
        inputConf.writeFile(inputconfigexampleFileName.c_str());
    } catch (const libconfig::ParseException &pex) {
        cerr << "The configuration file '" << inputconfigFileName << "' is badly written! " << endl
             << "Parsing error at " << pex.getFile() << ":" << pex.getLine()
             << " - " << pex.getError() << endl
             << "Please use a legit configuration file." << endl;
        exit(EXIT_FAILURE);
    }

    /* ---------------------------
     * CONFIGURATION FILE :: END
     * ---------------------------
     */

    
    vector<int> tot_res(1);
    tot_res[0]=20;
    Resources global_res(tot_res);
    Wlk_Resources wlkrestest(1);
	Wlk_Resources wlkres_zero(1);
    wlkrestest.set(0,1);
    vector<unique_ptr<Block>> blocksVector;
    //blocksVector.reserve(9); I think we do not need that
   
    
    /* Initialize Blocks */
/*
	//First test
	int nblocks{5};
    int idTest;
    for (idTest = 0; idTest < nblocks; ++idTest) {
		if (idTest == 3) {
			blocksVector.emplace_back(new taskBlock(idTest, vector<int>(1,idTest+1), vector<float>(1,1), wlkrestest));
		}
		else
			blocksVector.emplace_back(new taskBlock(idTest, vector<int>(1,idTest+1), vector<float>(1,1), wlkres_zero));
		
    }

	//Second test

	int nblocks{6};
	blocksVector.emplace_back(new taskBlock(0, vector<int>(1,1), vector<float>(1,1), wlkres_zero, 0, {1,0,0,0}));
	blocksVector.emplace_back(new taskBlock(1, vector<int>(1,2), vector<float>(1,1), wlkrestest, 0, {1,0,0,0}));
	blocksVector.emplace_back(new xorBlock(2, {3,4}, {0.1,0.2}));
	blocksVector.emplace_back(new taskBlock(3, vector<int>(1,5), vector<float>(1,1), wlkrestest, 0, {1,0,0,0}));
	blocksVector.emplace_back(new taskBlock(4, vector<int>(1,5), vector<float>(1,1), wlkres_zero, 0, {1,0,0,0}));
	blocksVector.emplace_back(new taskBlock(5, vector<int>(1,6), vector<float>(1,1), wlkres_zero, 0, {1,0,0,0}));


*/

    int nblocks{16};


    //Get issue description from customer
    {   // <-- DON'T REMOVE THESE, it's a nasty hack for the fucking libconf library (currentBlock has local scope)
        libconfig::Setting &currentBlock = inputConf.lookup("taskBlock_00");
        blocksVector.emplace_back(new taskBlock(0, vector<int>(1,1), vector<float>(1,1), wlkres_zero, (int)currentBlock.lookup("timeType"), {(float)currentBlock.lookup("timeMean"),(float)currentBlock.lookup("timeStd"),(float)currentBlock.lookup("timeMin"),(float)currentBlock.lookup("timeMax")}));
    }
    //Able to provide solution (front office)?
    {
        libconfig::Setting  &currentBlock = inputConf.lookup("xorBlock_01");
        blocksVector.emplace_back(new xorBlock(1, {2,4}, {(float)currentBlock.lookup("probOut_02"),(float)currentBlock.lookup("probOut_04")}));
    }
	//Provide solution to  customer
    {
        libconfig::Setting &currentBlock = inputConf.lookup("taskBlock_02");
        blocksVector.emplace_back(new taskBlock(2, vector<int>(1,3), vector<float>(1,1), wlkres_zero, (int)currentBlock.lookup("timeType"), {(float)currentBlock.lookup("timeMean"),(float)currentBlock.lookup("timeStd"),(float)currentBlock.lookup("timeMin"),(float)currentBlock.lookup("timeMax")}));
    }
    //Solution if effective?
    {
        libconfig::Setting  &currentBlock = inputConf.lookup("xorBlock_03");
        blocksVector.emplace_back(new xorBlock(3, {nblocks,0}, {(float)currentBlock.lookup("probOut_NB"),(float)currentBlock.lookup("probOut_00")}));
    }
	//Inform customer the issue is going to be escalated
    {
        libconfig::Setting &currentBlock = inputConf.lookup("taskBlock_04");
        blocksVector.emplace_back(new taskBlock(4, vector<int>(1,5), vector<float>(1,1), wlkres_zero, (int)currentBlock.lookup("timeType"), {(float)currentBlock.lookup("timeMean"),(float)currentBlock.lookup("timeStd"),(float)currentBlock.lookup("timeMin"),(float)currentBlock.lookup("timeMax")}));
    }
	//Request 1st level support
    {
        libconfig::Setting &currentBlock = inputConf.lookup("taskBlock_05");
        blocksVector.emplace_back(new taskBlock(5, vector<int>(1,6), vector<float>(1,1), wlkres_zero, (int)currentBlock.lookup("timeType"), {(float)currentBlock.lookup("timeMean"),(float)currentBlock.lookup("timeStd"),(float)currentBlock.lookup("timeMin"),(float)currentBlock.lookup("timeMax")}));
    }


	//Find solution 1st level issue
    {
        libconfig::Setting &currentBlock = inputConf.lookup("taskBlock_06");
        blocksVector.emplace_back(new taskBlock(6, vector<int>(1,7), vector<float>(1,1), wlkres_zero, (int)currentBlock.lookup("timeType"), {(float)currentBlock.lookup("timeMean"),(float)currentBlock.lookup("timeStd"),(float)currentBlock.lookup("timeMin"),(float)currentBlock.lookup("timeMax")}));
    }
    // Able to provide 1st level solution?
    {
        libconfig::Setting &currentBlock = inputConf.lookup("xorBlock_07");
        blocksVector.emplace_back(new xorBlock(7, {8,9}, {(float)currentBlock.lookup("probOut_08"),(float)currentBlock.lookup("probOut_09")}));
    }
	// Provide solution to front office
    {
        libconfig::Setting &currentBlock = inputConf.lookup("taskBlock_08");
        blocksVector.emplace_back(new taskBlock(8, vector<int>(1,2), vector<float>(1,1), wlkres_zero, (int)currentBlock.lookup("timeType"), {(float)currentBlock.lookup("timeMean"),(float)currentBlock.lookup("timeStd"),(float)currentBlock.lookup("timeMin"),(float)currentBlock.lookup("timeMax")}));
    }
	// Request 2nd level support
    {
        libconfig::Setting &currentBlock = inputConf.lookup("taskBlock_09");
        blocksVector.emplace_back(new taskBlock(9, vector<int>(1,10), vector<float>(1,1), wlkres_zero, (int)currentBlock.lookup("timeType"), {(float)currentBlock.lookup("timeMean"),(float)currentBlock.lookup("timeStd"),(float)currentBlock.lookup("timeMin"),(float)currentBlock.lookup("timeMax")}));
    }


    //Find solution 2nd level issue
    {
        libconfig::Setting &currentBlock = inputConf.lookup("taskBlock_10");
        blocksVector.emplace_back(new taskBlock(10, vector<int>(1,11), vector<float>(1,1), wlkres_zero, (int)currentBlock.lookup("timeType"), {(float)currentBlock.lookup("timeMean"),(float)currentBlock.lookup("timeStd"),(float)currentBlock.lookup("timeMin"),(float)currentBlock.lookup("timeMax")}));
    }
    // Able to provide 2nd level solution?
    {
        libconfig::Setting &currentBlock = inputConf.lookup("xorBlock_11");
        blocksVector.emplace_back(new xorBlock(11, {12,13}, {(float)currentBlock.lookup("probOut_12"),(float)currentBlock.lookup("probOut_13")}));
    }
    // Provide solution to first level support
    {
        libconfig::Setting &currentBlock = inputConf.lookup("taskBlock_12");
        blocksVector.emplace_back(new taskBlock(12, vector<int>(1,8), vector<float>(1,1), wlkres_zero, (int)currentBlock.lookup("timeType"), {(float)currentBlock.lookup("timeMean"),(float)currentBlock.lookup("timeStd"),(float)currentBlock.lookup("timeMin"),(float)currentBlock.lookup("timeMax")}));
    }
    // Request supplier support
    {
        libconfig::Setting &currentBlock = inputConf.lookup("taskBlock_13");
        blocksVector.emplace_back(new taskBlock(13, vector<int>(1,14), vector<float>(1,1), wlkres_zero, (int)currentBlock.lookup("timeType"), {(float)currentBlock.lookup("timeMean"),(float)currentBlock.lookup("timeStd"),(float)currentBlock.lookup("timeMin"),(float)currentBlock.lookup("timeMax")}));
    }



	//Find solution supplier issue
    {
        libconfig::Setting &currentBlock = inputConf.lookup("taskBlock_14");
        blocksVector.emplace_back(new taskBlock(14, vector<int>(1,15), vector<float>(1,1), wlkres_zero, (int)currentBlock.lookup("timeType"), {(float)currentBlock.lookup("timeMean"),(float)currentBlock.lookup("timeStd"),(float)currentBlock.lookup("timeMin"),(float)currentBlock.lookup("timeMax")}));
    }
	// Provide solution to second level support
    {
        libconfig::Setting &currentBlock = inputConf.lookup("taskBlock_15");
        blocksVector.emplace_back(new taskBlock(15, vector<int>(1,12), vector<float>(1,1), wlkres_zero, (int)currentBlock.lookup("timeType"), {(float)currentBlock.lookup("timeMean"),(float)currentBlock.lookup("timeStd"),(float)currentBlock.lookup("timeMin"),(float)currentBlock.lookup("timeMax")}));
    }




	//Here we change the signs of the destinations, depending on the resources needed
	//Negative sign means that no resources are needed for the next block 
	//and therefore the process has to be put to the top of the queue.
	adjust_idsOut_signs( blocksVector);



    int next{99}, new_pos{0}, aux{0};
    float next_time, maxtime{(float)inputConf.lookup("globalSettings.maxTime")};
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



