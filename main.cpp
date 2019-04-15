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

    vector<int> idsOut(3);
    vector<float> probsOut(3);
//    Block helloworldBlock(0, idsOut, probsOut);

	vector<int> res_tot(3);
	vector<int> res_need1(3);
	vector<int> res_need2(3);

	res_tot[0] = 2;
	res_tot[1] = 3;
	res_tot[2] = 4;

	res_need1[0] = 1;
	res_need1[1] = 2;
	res_need1[2] = 3;

	res_need2[0] = 1;
	res_need2[1] = 3;
	res_need2[2] = 4;

	Resources res_type(res_tot);

    taskBlock Block1(1, idsOut, probsOut,res_need1);
    xorBlock Block2(2, idsOut, probsOut);

//    Block1.ABBA();
//    Block2.ABBA();

    cout << endl << "Trying to make a vector of blocks" << endl << endl;

//    vector<unique_ptr<Block>> blocksVector;
//    blocksVector.reserve(2);
//    blocksVector.emplace_back(new taskBlock(0, idsOut, probsOut));
//    blocksVector.emplace_back(new xorBlock(1, idsOut, probsOut));




    vector<Block*> blocksVector(3);
    blocksVector[0] = new taskBlock(0, idsOut, probsOut,res_need1);
    blocksVector[1] = new xorBlock(1, idsOut, probsOut);
	blocksVector[2] = new taskBlock(2, idsOut, probsOut,res_need2);

    cout << endl << "Calling ABBA functions" << endl << endl;
    blocksVector[0]->ABBA();
    blocksVector[1]->ABBA();
    

	cout << "Testing some resource stuff" << endl;

	//First allocate resources to Block 0
	blocksVector[0]->resources_allocate(res_type);
	auto hihi = res_type.avail();
	//Print the remaining resources
	cout << "Now we have available " << hihi[0] << "  " << hihi[1] << "  " << hihi[2] << endl;
	//Allocate the available resources to Block 2 (Block 1 is still xOR, not used here)
	blocksVector[2]->resources_allocate(res_type);
	hihi = res_type.avail();
	//Print resources that remain now
	cout << "Now we have available " << hihi[0] << "  " << hihi[1] << "  " << hihi[2] << endl;

	//Allocate again resources for Block 2
	//Obviously this should not do anything. Allocation has projection property P^2=P
	blocksVector[2]->resources_allocate(res_type);
	hihi = res_type.avail();
	//print again
	cout << "Now we have available " << hihi[0] << "  " << hihi[1] << "  " << hihi[2] << endl;

	//Now release resources from Block 0
	blocksVector[0]->resources_release(res_type);
	hihi = res_type.avail();
	cout << "Now we have available " << hihi[0] << "  " << hihi[1] << "  " << hihi[2] << endl;

	//Now allocate again resources of Block 2 (now it can get the rest that it needed)
	blocksVector[2]->resources_allocate(res_type);
	hihi = res_type.avail();
	cout << "Now we have available " << hihi[0] << "  " << hihi[1] << "  " << hihi[2] << endl;

	//Release again resources of Block 0 (shouldn't do anything, since we already released)
	blocksVector[0]->resources_release(res_type);
	hihi = res_type.avail();
	cout << "Now we have available " << hihi[0] << "  " << hihi[1] << "  " << hihi[2] << endl;

	//Release also Block 2, now we should have all the resources available again
	blocksVector[2]->resources_release(res_type);
	hihi = res_type.avail();
	cout << "Now we have available " << hihi[0] << "  " << hihi[1] << "  " << hihi[2] << endl;

	cout << "CCC START HERE "<<endl;
	Group test(1,1);
	test.create_walker(5,0,0,1,1);
	test.create_walker(2,1,0,1,1);
	test.add_time_queue(0.45);
	test.move_walker(1,33);
	test.add_time_queue(0.35);
	test.move_walker(1,35);
	test.move_walker(0,12);
	test.add_time_queue(0.35);
	test.print_status();
	cout << "CCC ENDS HERE "<<endl;
	

    return 0;
}
