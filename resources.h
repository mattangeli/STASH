#ifndef RESOURCES_H
#define RESOURCES_H

#include <vector>
#include "Wlk_Resources.h"

using namespace std;

/*--------------------
   Resources Class
--------------------*/

/*---------------------------------------------------------------------------
  Class that hosts the avaiable resources and provides methods to allocate
  and release resources themselves.
---------------------------------------------------------------------------*/


class Resources {
private:
    vector<int> available;

public:
    Resources(vector<int> const & invec) :
        available{invec} {
#ifdef DEBUG
        cout << "Resources succesfully initialized" << endl;
        cout << "The resources available are:" << endl;
        cout << available[0] << "	" << available[1] <<  "	" << available[2] << endl;
#endif
    }

    vector<int> avail(){
        return available;
    }

    std::vector<int>::size_type get_ntype(){return available.size();}

    /* This function allocates resources. The input arguments are the needed
     * resources (total need) and a vector containing the resources that are
     * already allocated to the process asking for the resources.
     * This function then gives, if available, the resources to the process by
     * writing it in the occup vector and removing them from the available
     * vector of the resource class (Horrible exlanation, code is easy)
     */
    void res_allocate(Wlk_Resources const& needed, Wlk_Resources & occup) {
        /* Dimension checks */
      //      if (needed.ntypes() == occup.ntypes() && needed.ntypes() == (int)available.size()) 
            assert(needed.ntypes() == occup.ntypes() && needed.ntypes() == (int)available.size());
        //if (needed.size() != occup.size() ||
        //        needed.size() != available.size() ) {

        //    cout << "Input vectors to function 'allocate' in Resource class have wrong length" << endl;
        //}
      //      cout<< (int)available.size() << " " << needed.ntypes()  << " " <<  occup.ntypes()<< endl;
        cout << "Allocated the following resources:" << endl;

        /* Go through all the types of resources */
        for (int ii=0; ii < (int)available.size(); ii++){
            if (available[ii] >= (needed.get_resources(ii) - occup.get_resources(ii) )) {
                available[ii] -= (needed.get_resources(ii) - occup.get_resources(ii) );
                cout << ii << ": " << (needed.get_resources(ii) - occup.get_resources(ii) )  << endl;
                occup.set(ii,needed.get_resources(ii));
            }
            else {
				occup.set(ii,occup.get_resources(ii) + available[ii] );
                cout << ii << ": "<< available[ii] << endl;
                available[ii] = 0;
            }

        } //end for loop

    }


    /* This function releases the resources in the input vector */
    void res_release(vector<int>& occup) {
        /* Dimension check */
        assert(available.size() == occup.size());
        //if (available.size() != occup.size()) {
        //    cout << "Input vectors to function 'release' in Resource class have wrong length" << endl;
        //}

        for (int ii=0; ii < (int)available.size(); ii++){
            available[ii] += occup[ii];
            occup[ii] = 0;
        }

    }


};


#endif // RESOURCES_H
