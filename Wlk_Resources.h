
#ifndef WLK_RESOURCES_H
#define WLK_RESOURCES_H

#include <iostream>
#include <vector>
#include <memory>         
#include <cassert>

class Wlk_Resources{
   int ntype_res, num_tot_res, num_res_alloc ;
   std::vector<int> resources; 

   public:
     // default constructor
     Wlk_Resources();
     // constuctor with len and res
     Wlk_Resources(int _ntype_res, int _num_tot_res = 0);
     // function to add resources the typeof res is an int?
//     Wlk_Resources(Resources * global_res, int _num_tot_res = 0);

//    void add_res(int tres, int nres, Resources * global_res );
//release resources not really needed just call the function in the REs Container
//    void release_res(Resources * global_res);

//    void add_res(vector<int> const& needed , Resources * global_res);
     
     std::vector<int>  get_resources() const;
     
     int get_resources(int res_type) const;

     void set(int res_type, int newvalue);
     
     int ntypes() const;
	
     void release();

     std::vector<int> get_variables() const;// { // return all  the other protected variables in a vector [ntype_res, num_tot_res, num_res_alloc]
     //  std::vector<int> var{ntype_res, num_tot_res, num_res_alloc};
     //  return var;
    //}

};


//std::ostream& operator<<(std::ostream& os, const Wlk_Resources& res);



#endif
