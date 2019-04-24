#ifndef WALKER_H
#define WALKER_H

#include <iostream>
#include <vector>
#include <memory>         
#include "history.h"
#include <cassert>
#include "resources.h"

/*--------------------
     Walker Class
--------------------*/

/*---------------------------------------------------------------------------
  Class for the walkers of the system. It manages the position, id, history,
  and resources allocated.
---------------------------------------------------------------------------*/

template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec);


class walker {
    /* Maybe we could say that destination -1 is the end? */
    int parent_id, child_id, position, destination, max_resources, type_resources;
    history hist;
    int * resources;
public:
    /* Default constructor for a walker, it must be initialized before the
     * walker is simulated.
     */
    walker();

    /* Basilar constructor for the walker, it creates an unitialized but
     * working walker.
     */
    walker(const int r_types,  const int max_r);

    /* This constructor creates and initialize a walker */
    walker(const int pos, const int par_id,
           const int ch_id, const int r_types,  const int max_r);

    int get_parent_id() const noexcept; //{return parent_id;}
    int get_child_id() const noexcept; //{return child_id;}
    int get_pos() const noexcept ;//{return position;}
    const history  get_history() const noexcept ;//{return hist;}


    void addtq (const float time);//{hist.addtimeque(time);}
    /* Moves the walker in the next position */
    void moveto(const int pos);

    void start(const float time, const int dest, const std::vector<int> res);
    /* add here resources as output */
    void stop ();
};


/* Overload the << operator for the walker */
std::ostream& operator<<(std::ostream& os, const walker& w);


class Wlk_Resources{
   int ntype_res, num_tot_res, num_res_alloc ;
   std::vector<int> resources; 

   public:
     // default constructor
     Wlk_Resources();
     // constuctor with len and res
     Wlk_Resources(int _ntype_res, int _num_tot_res = 0);
     // function to add resources the typeof res is an int?
     Wlk_Resources(Resources * global_res, int _num_tot_res = 0);

    void add_res(int tres, int nres, Resources * global_res );
//release resources not really needed just call the function in the REs Container
    void release_res(Resources * global_res);

    void add_res(vector<int> const& needed , Resources * global_res);

    std::vector<int>  get_resources() const;// {
      // return resources;
    //}

    std::vector<int> get_variables() const;// { // return all  the other protected variables in a vector [ntype_res, num_tot_res, num_res_alloc]
     //  std::vector<int> var{ntype_res, num_tot_res, num_res_alloc};
     //  return var;
    //}

};

std::ostream& operator<<(std::ostream& os, const Wlk_Resources& res);

class Group {
    int nwalker;
    std::vector<walker> walker_list;
    std::vector<Wlk_Resources> res_list;
    std::vector<int> queue, status,running;
    std::vector<float> exec_time;
public:
    Group(const int resource_types,  const int max_resources);

    void create_walker(const int pos, const int par_id,
                       const int ch_id, const int r_types,  const int max_r, Resources * global_Res);

    void add_time_queue(const float time);

    void move_walker(const int id, const int pos);

    void activate_process(const int id, const float t, const int dest,
                          const int queue_pos, const std::vector<int> res);

    /* Maybe at the end of this we shoud free the resources
     * running_pos is the position in the vector of running
     * processes.
     */
    void end_process(const int id, const int running_pos);


    void print_status();


};

/*
int main(){
  Group test(5,1,1,1) ;
    std::cout<<std::endl;
    history hi;
    std::cout<<hi ;
    std::cout<<"nuova Histo"<<std::endl;
    history hi1(4,5);
    std::cout<<hi1 ;
    std::cout<<"nuova Histo2"<<std::endl;
    history hi2(4,5);
    hi2.nextstep(66);
    std::cout<<hi1 ;
     std::cout<<hi2 ;


 std::vector<int> invec(3,0);
 for(unsigned int i=0 ; i<invec.size() ; i++ ){
    invec[i]=3*i+1;
  }
 Resources *pgres = new Resources(invec) ; 
 Wlk_Resources wlk_res(pgres,9);
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
}

*/
  



#endif // WALKER_H
