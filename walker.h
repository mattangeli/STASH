#include <iostream>
#include <vector>
#include <memory>         //unique_ptr


//If you need a vector of a class you need a default constractor!!
    
class walker{
  int parent_id, child_id, steps, position, max_resources, type_resources;
  std::vector< float > history;
  int * resources;
  
public:

  walker(): 
    parent_id{0}, 
    child_id{0}, 
    steps{0}, 
    position{0},
    history{std::vector<float>(1)},
    max_resources{0}, 
    type_resources{0}
  {}

  walker(const std::size_t hist_lenght,
	 const int r_types,  const int max_r):
    history{std::vector<float> (2*hist_lenght)},
    steps{0},
    resources{new int [max_r*r_types]},
    position{0},
    parent_id{0},
    child_id{0},
    max_resources{max_r}, 
    type_resources{r_types}
  {for (auto i=0;i<max_resources*max_resources;i++) 
      resources[i]=-1;}

  int get_parent_id(){return parent_id;};
  int get_child_id(){return child_id;};
  
};

class Group{
  std::size_t _size, nwalker, queue_lenght;
  std::vector<walker> walker_list;
  std::vector<int> queue, status;
public:

  
  Group(const std::size_t init_lenght, const std::size_t hist_lenght, 
	const std::size_t resource_types,  const std::size_t max_resources) : 
    walker_list{std::vector<walker>(init_lenght)}    ,
	//    walker_list{std::vector<walker>(init_lenght)},/
    queue{std::vector<int>(init_lenght)}    ,
    status{std::vector<int> (init_lenght)}    ,
    _size{init_lenght},
    nwalker{0},
    queue_lenght{0}
  {fill(walker_list.begin(),walker_list.end(),walker(hist_lenght, resource_types, max_resources));}
};




int main(){
  Group test(5,1,1,1) ;
}


  
