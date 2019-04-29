#ifndef WALKER_H
#define WALKER_H

#include <iostream>
#include <vector>
#include <memory>         
#include "history.h"
#include <cassert>
#include "resources.h"


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
  int parent_id, child_id, position, destination;
  history hist;
  Wlk_Resources alloc_res;
 public:
  /* Default constructor for a walker, it must be initialized before the
   * walker is simulated.
   */
  walker();
  
  
  /* This constructor creates and initialize a walker */
  walker(const int pos, const int par_id, const int ch_id);
  
  int get_parent_id() const noexcept; //{return parent_id;}
  int get_child_id() const noexcept; //{return child_id;}
  int get_pos() const noexcept ;//{return position;}
  int get_destination() const noexcept;
  const history  get_history() const noexcept ;//{return hist;}
  
  
  void addtq (const float time);//{hist.addtimeque(time);}
  /* Moves the walker in the next position */
  void moveto(const int pos);
  
  void start(const float time, const int dest, const Wlk_Resources res);
  /* add here resources as output */
  void stop (Wlk_Resources * res);
  void check_parent_sons(const int id);

};


/* Overload the << operator for the walker */
std::ostream& operator<<(std::ostream& os, const walker& w);


class Group {
  //nwalker is the number of active walkers, totwalker is the number
  //of walker from the beginning
  int nwalker, next_to_finish, totwalker;
  float tot_time;
  std::vector<walker> walker_list;
  std::vector<int> queue, status,running;
  std::vector<float> exec_time;
public:
    Group();

    void evolve();

    void create_walker(const int pos, const int par_id,
                       const int ch_id);

    void add_time_queue(const float time);

    void move_walker(const int id, const int pos);

    void activate_process(const int id, const float t, const int dest,
                          const int queue_pos, const Wlk_Resources res);

    //void  print_queue() const noexcept{std::cout<< queue << std::endl;};

    /* When a walker is deleted it updates all the walkers*/
    void erased_update(const int id);
    
    /* Maybe at the end of this we shoud free the resources
     * running_pos is the position in the vector of running
     * processes.
     */
    void end_process(const int running_pos, Wlk_Resources * res);


    void print_status();


};
  



#endif // WALKER_H
