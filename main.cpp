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
	/*
    vector<int> idsOut(3);
    vector<float> probsOut(3);
//    Block helloworldBlock(0, idsOut, probsOut);

	idsOut[0]= 656;

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

	//Test for returning needed resources
	auto testreturn = blocksVector[1]->get_needed_res(3);
	cout << "We need " << testreturn[0] << "  " << testreturn[1] << "  " << testreturn[2] << endl;

	//Test returning next id
	cout << "Next we go to Block " << blocksVector[2]->get_next_id() << endl;

*/
 	
	cout << "CCC START HERE "<<endl;

	Group bla;
	Wlk_Resources pippo(2,1), paperino;

	bla.create_walker(0,-1,0);
	bla.create_walker(0,1,1);
	bla.add_time_queue(1.5);
	bla.activate_process(1, 2.2, 1, 1, pippo);
	bla.add_time_queue(1.2);
	bla.end_process(0, &pippo);
	bla.print_status();
	//Peche' non riesco ad iniziare un nuovo processo???
	//	bla.activate_process(1, 0.2, -1, 1, pippo);
	//	bla.end_process(0, &pippo);
	//	cout << "Pippo "<< pippo << endl;
	//cout << "Paperino " << paperino <<endl;


	//    std::vector<int> invec(3,0);
	//for(unsigned int i=0 ; i<invec.size() ; i++ ){
	//invec[i]=3*i+1;
	//}
	//Resources *pgres = new Resources(invec) ;
	//test.create_walker(5,0,0,1,1,pgres);
	//test.create_walker(2,1,0,1,1,pgres);
	//test.add_time_queue(0.45);
	//test.move_walker(1,33);
	//test.add_time_queue(0.35);
	//test.move_walker(1,35);
	//test.move_walker(0,12);
	//test.add_time_queue(0.35);
	//test.print_status();
	cout << "CCC ENDS HERE "<<endl;
	

/*
   //TEST WALKER

  cout << "TEST FOR Wlk_Resources "<<endl;
  //  std::vector<int> invec(3,0);
  //  for(unsigned int i=0 ; i<invec.size() ; i++ ){
  //     invec[i]=3*i+1;
  //   }
  //  Resources *pgres = new Resources(invec) ;
    //Wlk_Resources wlk_res(pgres,9);
    Wlk_Resources wlk_res(pgres);
    std::cout<<"initial  "<<wlk_res<<std::endl;
    std::vector<int> needed{0,1,3};
    wlk_res.add_res(needed,pgres);

    std::cout<<"final "<<wlk_res<<std::endl;

    wlk_res.release_res(pgres);


    std::cout<<"after rel  "<<wlk_res<<std::endl;
    int tres{2},nres{5} ;
    //int tres{39},nres{5} ;
    wlk_res.add_res(tres,nres,pgres);

    std::cout<<"final "<<wlk_res<<std::endl;
	*/
    return 0;
}
