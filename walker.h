#include <iostream>
#include <vector>
#include <memory>         
#include "history.h"


//////////////////////
//    Walker Class
//////////////////////

////////////////////////////////////////////////////////////////////////////
//Class for the walkers of the system. It manages the position, id, history,
//and resources allocated.
////////////////////////////////////////////////////////////////////////////
class walker{
  //Maybe we could say that destination -1 is the end?
  int parent_id, child_id, position, destination, max_resources, type_resources;
  history hist;
  int * resources;
  public:
  //Default constructor for a walker, it must be initialized before the 
  //walker is simulated
  walker(): 
    parent_id{0}, 
    child_id{0}, 
    position{-1},
      destination{-1},
    hist{history()},
    max_resources{0}, 
    type_resources{0}
  {}
  //Basilar constructor for the walker, it creates an unitialized but
  //working walker
 walker(const int r_types,  const int max_r):
    hist{history()},
    resources{new int [max_r*r_types]},
    position{-1},
    destination{-1},
    parent_id{0},
    child_id{0},
    max_resources{max_r}, 
    type_resources{r_types}
    {}

  //This constructor creates and initialize a walker
  walker(const int pos, const int par_id,
	 const int ch_id, const int r_types,  const int max_r):
    hist{history(pos)},
    resources{new int [max_r*r_types]},
    position{pos},
    parent_id{par_id},
    child_id{ch_id},
    max_resources{max_r}, 
    type_resources{r_types}
  {}

  int get_parent_id() const noexcept {return parent_id;};
  int get_child_id()const noexcept {return child_id;};
  int get_pos() const noexcept {return position;};
  const history  get_history() const noexcept {return hist;};


  void addtq (const float time){hist.addtimeque(time);}
  //moves the walker in the next position
  void moveto(const int pos){
    position=pos;
    hist.next_step(pos);
  };

  void start(const float time, const int dest, const std::vector<int> res){
    //Maybe we could say that destination -1 is the end?
    destination=dest;
    hist.addtimeexe(time);
  };
  //add here resources as output
  void stop (){
    moveto(destination);
  };
};

std::ostream& operator<<(std::ostream& os, const walker& w) {
  os << w.get_parent_id() << "  ";
  os << w.get_child_id() << "  ";
  os << w.get_pos() << "  ";
  os << w.get_history() << " ";
  return os;
};



class Group{
  int nwalker;
  std::vector<walker> walker_list;
  std::vector<int> queue, status,running;
  std::vector<float> exec_time;
 public:
   Group(const int resource_types,  const int max_resources) : 
  walker_list{std::vector<walker>()}    ,
    //    walker_list{std::vector<walker>(init_lenght)},/
    queue{std::vector<int>()}    ,
    status{std::vector<int> ()}    ,
      running{std::vector<int>()},
      exec_time{std::vector<float>()},
      nwalker{0}
    {}
    
    void create_walker(const int pos, const int par_id,
		       const int ch_id, const int r_types,  const int max_r){
      walker_list.push_back(walker(pos,par_id, ch_id, r_types,max_r));
      status.push_back(0);
      nwalker++;
      queue.push_back(nwalker-1);
    };

    void add_time_queue(const float time){
      //Add the time to the processes in the que
      for (auto i=0;i<nwalker;i++)
	if (status[i]==0)
	  walker_list[i].addtq(time);
      //removes from the remaining execution time the time
      // spent waiting for the next action.
      for (auto  i=exec_time.begin();i!=exec_time.end();i++)
	*i-=time;
    };

    void move_walker(const int id, const int pos){
      walker_list[id].moveto(pos);
      queue.push_back(id);
      status[id]=0;
    };
    
    void activate_process(const int id, const float t, const int dest,
			  const int queue_pos, const std::vector<int> res){
      status[id]=1;
      queue.erase(queue.begin()+queue_pos);
      running.push_back(id);
      exec_time.push_back(t);
      walker_list[id].start(t,dest,res);
    };
    
    //Maybe at the end of this we shoud free the resources
    //running_pos is the position in the vector of running 
    //processes
    void end_process(const int id, const int running_pos){
      walker_list[id].stop();
      status[id]=0;
      running.erase(running.begin()+running_pos);
      exec_time.erase(exec_time.begin()+running_pos);
    };


    void print_status(){
    for (auto i=0;i<walker_list.size();i++)
      std::cout<< i <<" "<<walker_list[i]<< status[i]<<std::endl;
  };


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
}


  
*/
