#include <iostream>
#include "walker.h"

template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec){
  for(auto i : vec){
    os<<i<<"  ";
  }
  return os;}



/* Default constructor for a walker, it must be initialized before the
 * walker is simulated.
 */

walker::walker():
	my_id{0},
	parent_id{0},
	position{-1},
	destination{std::vector<int>(1,-1)},
	children_id{std::vector<int>(1,my_id)},
	hist{history()},
	alloc_res{Wlk_Resources()}
{}

    /* This constructor creates and initialize a walker */


walker::walker(const int pos, const int par_id,
	       const int _my_id, const float time):
        my_id{_my_id},
	parent_id{par_id},
        position{pos},
	destination{std::vector<int>(1,-1)},
	children_id{std::vector<int>()},
        hist{history(pos, time)},
	alloc_res{Wlk_Resources()}
{if (my_id==parent_id) children_id=std::vector<int>(1,my_id);}

walker:: walker(const int pos, const int par_id, const int _my_id, 
		const float time,  const int ntype_res):
  my_id{_my_id},      
	parent_id{par_id},
	position{pos},
	destination{std::vector<int>(1,-1)},
	children_id{std::vector<int>()},
	hist{history(pos, time)},
	alloc_res{Wlk_Resources(ntype_res)}
{if (my_id==parent_id) children_id=std::vector<int>(1,my_id);}




int walker::get_parent_id() const noexcept {return parent_id;}
int walker::get_pos() const noexcept {return position;}
std::vector<int> walker::get_child_id() const noexcept {return children_id;}
std::vector<int> walker::get_destination() const noexcept {return destination;}
const history  walker::get_history() const noexcept {return hist;}


void walker::addtq (const float time){hist.addtimeque(time);}
/* Moves the walker in the next position */
void walker::moveto(const int pos){
  position=pos;
  hist.next_step(pos);
}


/*We have to think to something in the case after this process we have to create
 a son walker */
void walker::start(const float time, const std::vector<int> dest){
        /* Maybe we could say that destination -1 is the end? */
        destination=dest;
        hist.addtimeexe(time);
}

void walker::stop(){
  //do we need to enforce a deep copy?
  if ((int)destination.size()==1){
    if (destination[0]!=-1) moveto(destination[0]);
  }
}

/* Allocate resources to a walker */
int walker::add_res(Wlk_Resources const& needed , Resources * global_res){
    int do_start = global_res->res_allocate(needed, alloc_res);
	return do_start;
    }

void walker::release_res(Resources & global_res) {
	global_res.res_release(alloc_res);
	}


vector<int> walker::get_alloc_res() {
	return alloc_res.get_resources();
}


void walker::removed(const int id){
  if (my_id!=parent_id){
    if (my_id>id) my_id--;
    if (parent_id>id) parent_id--;
  }
  else{
    int remove_son=-1;
    if (my_id>id) my_id--;
    if (parent_id>id) parent_id--;
    for (auto i=0; i!=(int)children_id.size(); i++){
      if (children_id[i]>id){
	children_id[i]--;
      }
      else if (children_id[i]==id) remove_son=i;
    }
    if (remove_son>=0) children_id.erase(children_id.begin()+remove_son);
  }
}

void walker::add_son(const int id){children_id.push_back(id);}

/* Overload the << operator for the walker */
std::ostream& operator<<(std::ostream& os, const walker& w) {
  
  os << "par_id " << w.get_parent_id() << "  ";
  os << "child_id " <<w.get_child_id() << "  ";
  os << "pos " <<w.get_pos() << "  ";
  os << "history " <<w.get_history() << " ";
  return os;
}




Group::Group() :
  nwalker{0},
  next_to_finish{-1},
  totwalker{0},
        //    walker_list{std::vector<walker>(init_length)},/
  tot_time{0.0},
  walker_list{std::vector<walker>()}    ,
  queue{std::vector<int>()}    ,
  status{std::vector<int> ()}    ,
  running{std::vector<int>()} ,
  exec_time{std::vector<float>()}
{}


//void Group::evolve(){
//}


void Group::create_walker(const int pos, const int par_id,
			  const int my_id, const int ntype_res){
  walker_list.push_back(walker(pos,par_id, my_id, tot_time,  ntype_res));
  if (par_id!=my_id) walker_list[par_id].add_son(my_id);
  status.push_back(0);
  nwalker++;
  totwalker++;
  //maybe if "pos" is a logic gate we can put it at the top of the cue ;)
  queue.push_back(nwalker-1);
  //  std::cout<< "Passi qui, queue"<< queue<< std::endl;
}



void Group::add_time_queue(const float time){
  /* Add the time to the processes in the queue */
  for (auto i=0;i<nwalker;i++)
    if (status[i]==0)
      walker_list[i].addtq(time);
  /* removes from the remaining execution time the time
   * spent waiting for the next action.
   */
  for (auto  i=exec_time.begin();i!=exec_time.end();i++)
    *i-=time;

  tot_time+=time;
}



void Group::activate_process(const int id, const float t, const std::vector<int> dest,
			     const int queue_pos){
  status[id]=1;
  queue.erase(queue.begin()+queue_pos);
  running.push_back(id);
  exec_time.push_back(t);
  walker_list[id].start(t,dest);
}

/* Maybe at the end of this we shoud free the resources
 * running_pos is the position in the vector of running
 * processes.
 */
void Group::end_process(const int running_pos, Resources & tot_res){
  int id{running[running_pos]};
  walker_list[id].stop();
  walker_list[id].release_res(tot_res);
  //free the resources
  running.erase(running.begin()+running_pos);
  exec_time.erase(exec_time.begin()+running_pos);
  status[id]=0;
  if (walker_list[id].get_destination()[0]==-1){
    //print history
    walker_list.erase(walker_list.begin()+id);
    status.erase(status.begin()+id);                 
    erased_update(id);
    nwalker--;        
    std::cout <<"After killing walker "<< id <<std::endl;
  }
  else   queue.push_back(id);
  //  std::cout <<"Queue after end process "<< queue<<std::endl;
}


void Group::print_status(){
  for (auto i=0;i<(int)walker_list.size();i++)
    std::cout<< i <<" "<<walker_list[i]<<" "<< status[i]<<std::endl;
  //  std::cout<< "Queue vector "<< queue<< std::endl;
}


void Group::erased_update(const int id){
  for (auto  i=0;i!=running.size();i++){
    if (running[i]>id) running[i]--;
  }
  for (auto  i=0;i!=queue.size();i++){
    if (queue[i]>id) queue[i]--;
  }
  for (auto i=0;i!=walker_list.size();i++){
    walker_list[i].removed(id);
  }
  /*  for (auto  i=walker_list.begin()+id;i!=running.end();i++)
    *i.check_parent_sons(id);
    */
}


int Group::add_res(const int id, Wlk_Resources const& needed , Resources * global_res) {
	return walker_list[id].add_res(needed,global_res);
}


vector<int> Group::get_alloc_res(const int id) {
	return walker_list[id].get_alloc_res();
}


void Group::check_stop_evolve(Resources & tot_res){
  float eps{0.000001};
  //Wlk_Resources res(tot_res.get_ntype());
  std::vector<int> to_stop;
  for (auto  i=0;i!=(int)running.size();i++){
    if (exec_time[i]<eps) {
      to_stop.push_back(i);
    }
  }
  for (auto i=0;i!=(int)to_stop.size();i++)
    end_process(to_stop[i]-i, tot_res);
}




void Group::check_queue(Resources global_res, vector<unique_ptr<Block>> & blocksVector){
  std::vector <int> dest, to_start, queue_pos;
  float process_time;
  int do_start{-10};
  int j{0};
  
  for (auto i=queue.begin();i!=queue.end();i++){
    do_start = get_block_info(*blocksVector[walker_list[*i].get_pos()],
			      *i, dest, process_time, global_res);
    //    std::cout<< "Passi qui, do_start "<< do_start<< std::endl;
    if (abs(do_start)==1) {
      to_start.push_back(*i);
      queue_pos.push_back(j);
    }
    j++;
    if (do_start<0) break;
  }
  for (auto i=0;i!=(int)to_start.size();i++) activate_process(to_start[i], process_time, dest, queue_pos[i]-i);
}




int Group::get_block_info(Block blk, const int id, vector<int>& destinations , 
		   float & _time, Resources & global_res )
{
  int do_start = add_res(id,blk.get_res_needed( (int)global_res.get_ntype()), &global_res);
  destinations = blk.get_idsOut();
  _time = (float)id+1+destinations[0]*0.1; //Here we need to adjust
  //  std::cout<< "Passi qui, destinations, id, _time"<<destinations<< " "<<id <<" " << _time<<std::endl;
  return 1;
  //return do_start; // Return
}
  
int Group::next_operation(int & new_pos, float & next_time){
  if (nwalker>0){
    
    next_time=exec_time[0];
    for (auto  i=exec_time.begin();i!=exec_time.end();i++)  if (next_time>*i) next_time=*i;
  }
  else next_time=0;
  return 1;
}

float Group::get_exec_time(){
  return tot_time;
}


