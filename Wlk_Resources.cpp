#include <iostream>
#include "Wlk_Resources.h"



     // default constructor
     Wlk_Resources::Wlk_Resources():
      ntype_res{0},
      num_tot_res{0},
      num_res_alloc{0},
      resources{std::vector<int>(ntype_res,0)}
      {}
     // constuctor with len and res
     Wlk_Resources::Wlk_Resources(int _ntype_res, int _num_tot_res ):
      ntype_res{_ntype_res},
      num_tot_res{_num_tot_res},
      num_res_alloc{0},
      resources{std::vector<int>(_ntype_res,0)}
      {}
/*
     // function to add resources the typeof res is an int?
     Wlk_Resources::Wlk_Resources(Resources * global_res, int _num_tot_res):
      ntype_res{(int)global_res->get_ntype()},
      num_tot_res{_num_tot_res},
      num_res_alloc{0},
      resources{std::vector<int>(ntype_res,0)}
      {
#ifdef DEBUG
          std::cout<<"constr con il Resources *"<<std::endl;
#endif
          }

*/ 

/*
    void Wlk_Resources::add_res(int tres, int nres, Resources * global_res ){ // tres type resources to alloc nres how much of it
       assert( tres < ntype_res);
       vector<int> needed(ntype_res,0);
       needed[tres]=nres;
       global_res->res_allocate(needed,resources);
    }
*/

//release resources not really needed just call the function in the REs Container
//    void Wlk_Resources::release_res(Resources * global_res){
//        global_res-> res_release(resources);
//    }

/*
    void Wlk_Resources::add_res(vector<int> const& needed , Resources * global_res){
       assert( needed.size() == global_res->get_ntype() );
       assert( needed.size() == resources.size() );

       global_res->res_allocate(needed,resources);

    }
*/

    std::vector<int>  Wlk_Resources::get_resources() const {
       return resources;
    }

	int Wlk_Resources::get_resources(int res_type) const {
		assert(res_type <= ntype_res);
		return resources[res_type];
	}

	int Wlk_Resources::ntypes() const {
		return ntype_res;
	}


	//This function returns if all resources are 0
	bool Wlk_Resources::are_res_zero() const {
		bool result = true;
		for (int ii = 0; ii < ntype_res; ii++) {
			if (resources[ii] != 0) {
				result = false;
				break;
			}
		}
		return result;
	
	}
	
	void Wlk_Resources::set(int res_type, int newvalue) {
		resources[res_type] = newvalue;
	}

    std::vector<int> Wlk_Resources::get_variables() const { // return all  the other protected variables in a vector [ntype_res, num_tot_res, num_res_alloc]
       std::vector<int> var{ntype_res, num_tot_res, num_res_alloc};
       return var;
    }

void Wlk_Resources::release() {for (auto i=resources.begin();i!=resources.end();i++) *i=0;}
/*
std::ostream& operator<<(std::ostream& os, const Wlk_Resources& res) {
  os << res.get_resources()<<endl;
  os << res.get_variables()<<endl;
  return os;
};
*/
