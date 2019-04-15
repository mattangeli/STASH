#ifndef RESOURCES_H
#define RESOURCES_H

#include <vector>

using namespace std;

class Resources
{
private:
	vector<int> available;

public:
	Resources(vector<int> const & invec) 
		:
		available{invec} {
		cout << "Resources succesfully initialized" << endl;
		cout << "The resources available are:" << endl;
		cout << available[0] << "	" << available[1] <<  "	" << available[2] << endl;
	}

	vector<int> avail(){
		return available;
	}

	//This function allocates resources. The input arguments are the needed resources (total need)
	//and a vector containing the resources that are already allocated to the process asking for the resources.
	//This function then gives, if available, the resources to the process by writing it in the occup vector
	//and removing them from the available vector of the resource class (Horrible exlanation, code is easy)
	void res_allocate(vector<int> const& needed, vector<int>& occup) {
		//Dimension checks
		if (needed.size() != occup.size() ||
			needed.size() != available.size() ) {

			cout << "Input vectors to function 'allocate' in Resource class have wrong length" << endl;
		}

		cout << "Allocated the following resources:" << endl;

		//Go through all the types of resources
		for (int ii=0; ii < available.size(); ii++){
			if (available[ii] >= (needed[ii] - occup[ii] )) {
				available[ii] -= (needed[ii] - occup[ii] );
				cout << ii << ": " << (needed[ii] - occup[ii] )  << endl;
				occup[ii] = needed[ii];
			} 
			else {
				occup[ii] +=available[ii];
				cout << ii << ": "<< available[ii] << endl;
				available[ii] = 0;
			}

		} //end for loop 

	}


	//This function releases the resources in the input vector
	void res_release(vector<int>& occup) {
		//Dimension check
		if (available.size() != occup.size()) {
			cout << "Input vectors to function 'release' in Resource class have wrong length" << endl;
		}

		for (int ii=0; ii < available.size(); ii++){
			available[ii] += occup[ii];
			occup[ii] = 0;
		} 

	}


};


#endif // RESOURCES_H