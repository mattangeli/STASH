#ifndef WALKER_H
#define WALKER_H

#include <iostream>
#include <vector>
#include <memory>         
#include "history.h"
#include <cassert>
#include "resources.h"
#include "Wlk_Resources.h"
#include "block.h"


template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec);





/*--------------------
     Walker Class
--------------------*/

/*---------------------------------------------------------------------------
  Class for the walkers of the system. It manages the position, id, history,
  and resources allocated.
---------------------------------------------------------------------------*/


class walker {
  /* Maybe we could say that destination -1 is the end? */
  int my_id, parent_id, position;
  std::vector<int> destination, children_id;
  history hist;
  Wlk_Resources alloc_res;
 public:
  /* Default constructor for a walker, it must be initialized before the
   * walker is simulated.
   */
  walker();
  
  
  /* This constructor creates and initialize a walker */
  walker(const int pos, const int par_id, const int _my_id, const float time);
  walker(const int pos, const int par_id, const int _my_id, const float time, const int ntyp_res);


  std::vector<int> get_child_id() const noexcept;
  int get_parent_id() const noexcept; //{return parent_id;}
  int get_my_id() const noexcept; //{return child_id;}
  int get_pos() const noexcept ;//{return position;}
  std::vector<int> get_destination() const noexcept;
  const history  get_history() const noexcept ;//{return hist;}
    

  void addtq (const float time);//{hist.addtimeque(time);}
  /* Moves the walker in the next position */
  void moveto(const int pos);
  
  void start(const float time, const std::vector<int> dest);
  /* add here resources as output */


  
  void removed(const int id);
  void add_son(const int id);

  void check_parent_sons(const int id);
  int add_res(Wlk_Resources const& needed , Resources & global_res);
  void release_res(Resources & global_res);


  vector<int> get_alloc_res();

};


/* Overload the << operator for the walker */
std::ostream& operator<<(std::ostream& os, const walker& w);


class Group {
  //nwalker is the number of active walkers, totwalker is the number
  //of walker from the beginning
  int nwalker, next_to_finish, totwalker, nblocks;
  float tot_time;
  std::vector<walker> walker_list;
  std::vector<int> queue, status,running;
  std::vector<float> exec_time;
  vector<unique_ptr<Block>> blocksVector;

public:
    Group();

	Group( vector<unique_ptr<Block>> & blocksVector_);

    void check_stop_evolve();

    void readnblocks(const int _nblocks);

    void create_walker(const int pos, const int par_id,
                       const int my_id, const int ntype_res);

    void add_time_queue(const float time);

    void move_walker(const int id, const int pos);

    void activate_process(const int id, const float t, const std::vector<int> dest,
                          const int queue_pos);

    int get_nwalker(){return nwalker;};
    vector<int> get_alloc_res(const int id);

    //void  print_queue() const noexcept{std::cout<< queue << std::endl;};

    /* When a walker is deleted it updates all the walkers*/
    void erased_update(const int id);
    
    /* Maybe at the end of this we shoud free the resources
     * running_pos is the position in the vector of running
     * processes.
     */
    void end_process(const int running_pos, Resources & tot_res);

    int add_res(const int id,Wlk_Resources const& needed , Resources & global_res);

    void check_stop_evolve(Resources & total_res);

    void print_status();

    //It can be a source of segmentation fault
    void check_queue(Resources & global_res);
   
    int get_block_info(unique_ptr<Block> & blk, const int id, vector<int>& destinations , 
		       float & time, Resources & global_res );

    int next_operation(int & new_pos, float & next_time);

    float get_exec_time();

    float next_walker(int & new_pos);
};
  



#endif // WALKER_H
