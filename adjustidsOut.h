
#include "block.h"
#include <memory>
#include <vector>
#include "resources.h"
#include "Wlk_Resources.h"

using namespace std;

//Here is the function that is changing the signs in the idsOut vector depending on the
//resources that are needed by the blocks we go to 

void adjust_idsOut_signs(vector<unique_ptr<Block>> & blocksvec) {

	//Define variables we need here
	vector<int> idsOut;
	bool do_need_res;
	//Loop over all blocks
	for (int ii=0; ii<(int)blocksvec.size(); ii++) {

		//First we need to ask block ii for the possible destinations
		idsOut = blocksvec[ii]->get_idsOut();

		for (int jj=0; jj<(int)idsOut.size(); jj++) {

			assert(idsOut[jj]<=(int)blocksvec.size());
			if (idsOut[jj] != (int)blocksvec.size()) {
				//Ask this block if it needs resources
				do_need_res=blocksvec[idsOut[jj]]->do_need_resources();
				//cout << "do_need_res is " << do_need_res << endl;
				if (!do_need_res) {
					blocksvec[ii]->make_idOut_negative(jj);
					//cout << "Changing idOut in Block " << ii << endl;
				}
			}
		}
	}

}
