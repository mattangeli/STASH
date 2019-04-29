#include <iostream>
#include "walker.h"

//Esattamente perche' abbiamo ridefinito questo operatore per un generico vettore?
template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec){

  for(auto i : vec){
    os<<i<<"  ";
    
  }
  return os;
}

/* Default constructor for a walker, it must be initialized before the
 * walker is simulated.
 */
walker::walker():
  parent_id{0},
	child_id{0},
	position{-1},
	destination{-1},
	hist{history()},
	alloc_res{Wlk_Resources()}
{}


    /* This constructor creates and initialize a walker */
walker::walker(const int pos, const int par_id,
	       const int ch_id):
  parent_id{par_id},
        child_id{ch_id},
        position{pos},
        hist{history(pos)},
	alloc_res{Wlk_Resources()}
    {}

int walker::get_parent_id() const noexcept {return parent_id;}
int walker::get_child_id() const noexcept {return child_id;}
int walker::get_pos() const noexcept {return position;}
int walker::get_destination() const noexcept {return destination;}
    const history  walker::get_history() const noexcept {return hist;}


    void walker::addtq (const float time){hist.addtimeque(time);}
    /* Moves the walker in the next position */
    void walker::moveto(const int pos){
        assert(pos >= 0);// if pos negative ??
        position=pos;
        hist.next_step(pos);
    }


/*We have to think to something in the case after this process we have to create
 a son walker */
void walker::start(const float time, const int dest, const Wlk_Resources res){
        /* Maybe we could say that destination -1 is the end? */
        destination=dest;
        hist.addtimeexe(time);
	alloc_res=res;
    }

    /* add here resources as output */
void walker::stop (Wlk_Resources * res){
  //do we need to enforce a deep copy?
  *res=alloc_res;
  if (destination!=-1) moveto(destination);
  alloc_res=Wlk_Resources();
}


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
  walker_list{std::vector<walker>()}    ,
        //    walker_list{std::vector<walker>(init_length)},/
  queue{std::vector<int>()}    ,
  status{std::vector<int> ()}    ,
  running{std::vector<int>()} ,
  exec_time{std::vector<float>()}
{}


void Group::evolve(){
}




void Group::create_walker(const int pos, const int par_id,
			  const int ch_id){

  if (par_id>=0)
    walker_list.push_back(walker(pos,par_id, ch_id));
  else
    walker_list.push_back(walker(pos,totwalker, ch_id));
  status.push_back(0);
  nwalker++;
  totwalker++;
  //maybe if "pos" is a logic gate we can put it at the top of the cue ;)
  queue.push_back(nwalker-1);
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
}

/*
void Group::move_walker(const int id){
  if (pos!=-1){
    walker_list[id].moveto(pos);
    //maybe if "pos" is a logic gate we can put it at the top of the cue ;)
    queue.push_back(id);
    status[id]=0;
  } 
  else {
    //write history
    walker_list.erase(walker_list.begin()+id)
    status.erase(status.begin()+id);
    group.erased_update(id);
    
  }
  }*/

void Group::activate_process(const int id, const float t, const int dest,
			     const int queue_pos, const Wlk_Resources res){
  status[id]=1;
  queue.erase(queue.begin()+queue_pos);
  running.push_back(id);
  exec_time.push_back(t);
  walker_list[id].start(t,dest,res);
}

/* Maybe at the end of this we shoud free the resources
 * running_pos is the position in the vector of running
 * processes.
 */
void Group::end_process(const int running_pos, Wlk_Resources * res){
  int id{running[running_pos]};
  walker_list[id].stop(res);
  //free the resources
  running.erase(running.begin()+running_pos);
  exec_time.erase(exec_time.begin()+running_pos);
  status[id]=0;
  if (walker_list[id].get_destination()==-1){
    //print history
    walker_list.erase(walker_list.begin()+id);
    status.erase(status.begin()+id);                                                                                                                 
    erased_update(id);
    nwalker--;
  }
}


void Group::print_status(){
  for (auto i=0;i<(int)walker_list.size();i++)
    std::cout<< i <<" "<<walker_list[i]<<" "<< status[i]<<std::endl;
}


void Group::erased_update(const int id){
  for (auto  i=running.begin();i!=running.end();i++)
    if (*i>id) *i--;
  for (auto  i=queue.begin();i!=queue.end();i++)
    if (*i>id) *i--;
  /*  for (auto  i=walker_list.begin()+id;i!=running.end();i++)
    *i.check_parent_sons(id);
    */
}




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

    void Wlk_Resources::add_res(int tres, int nres, Resources * global_res ){ // tres type resources to alloc nres how much of it
       assert( tres < ntype_res);
       vector<int> needed(ntype_res,0);
       needed[tres]=nres;
       global_res->res_allocate(needed,resources);
    }

//release resources not really needed just call the function in the REs Container
    void Wlk_Resources::release_res(Resources * global_res){
        global_res-> res_release(resources);

    }
    void Wlk_Resources::add_res(vector<int> const& needed , Resources * global_res){
       assert( needed.size() == global_res->get_ntype() );
       assert( needed.size() == resources.size() );

       global_res->res_allocate(needed,resources);

    }
    std::vector<int>  Wlk_Resources::get_resources() const {
       return resources;
    }

    std::vector<int> Wlk_Resources::get_variables() const { // return all  the other protected variables in a vector [ntype_res, num_tot_res, num_res_alloc]
       std::vector<int> var{ntype_res, num_tot_res, num_res_alloc};
       return var;
    }



std::ostream& operator<<(std::ostream& os, const Wlk_Resources& res) {
  os << res.get_resources()<<endl;
  os << res.get_variables()<<endl;
  return os;
};

