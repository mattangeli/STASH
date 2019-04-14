#include <iostream>
#include <vector>
#include <memory>         

//////////////////////
//    History Class
//////////////////////

////////////////////////////////////////////////////////////////////////////
//Class for the history of the walker: it saves all the positions and the
//time spent in every block. In the future it will save also the cost
////////////////////////////////////////////////////////////////////////////

class history{
  //lenght in input describes the starting value for the history lenght,
  //       and after it is used to keep trace of the number of steps done
  //skip   is the distance in record between one chronological record and 
  //       the next (2 for the time, maybe one for the cost in the future..)
  int lenght, skip;
  std::vector<float> record;
  std::vector<int> positions;
public:
  //default constructor
  history(): 
    lenght{0},
    record{std::vector<float>(1)},
    positions{std::vector<int>(1)}, 
    skip{1}
  {std::cout << "Ciao 1";}

  //Constructor for history of positions and times
  history(const int len, const int pos): 
    lenght{0},
    record{std::vector<float>(2*len)},
    positions{std::vector<int>(len)},
    skip{2}
  {positions[0]=pos;
    std::cout << "Ciao 2";}
  
  //These functions add the time spent in the que and  
  void addtimeque(const float T){record[skip*(lenght-1)]+=T;};
  void addtimeexe(const float T){record[skip*(lenght-1)+1]=T;};
  int len(){return lenght;};
  int sk(){return skip;};

  //This function update the position in the history of 
  //the walker
  void nextstep(const int npos){
    positions[lenght]=npos;
    record[skip*lenght]=0.0;
    lenght++;
  };
};

// Operator overloading << for history, printing the history
// of a walker
/*std::ostream & operator<<(std::ostream &os, const history h){
  int leng{h.len()}, sk{h.sk()};
  os << leng << " ";
  
  os << std::endl;
  return os;
}
*/











//////////////////////
//    Walker Class
//////////////////////

////////////////////////////////////////////////////////////////////////////
//Class for the walkers of the system. It manages the position, id, history,
//and resources allocated.
////////////////////////////////////////////////////////////////////////////
class walker{
  int parent_id, child_id, position, max_resources, type_resources;
  history hist;
  int * resources;
  public:

  //Default constructor for a walker, it must be initialized before the 
  //walker is simulated
    walker(): 
    parent_id{0}, 
    child_id{0}, 
    position{-1},
    hist{history()},
    max_resources{0}, 
    type_resources{0}
  {}
  
  //Basilar constructor for the walker, it creates an unitialized but
  //working walker
  walker(const std::size_t hist_lenght,
	 const int r_types,  const int max_r):
    hist{history(hist_lenght,0)},
    resources{new int [max_r*r_types]},
    position{-1},
    parent_id{0},
    child_id{0},
    max_resources{max_r}, 
    type_resources{r_types}
  {for (auto i=0;i<max_resources*max_resources;i++) 
      resources[i]=-1;}

  //This constructor creates and initialize a walker
  walker(const std::size_t hist_lenght, const int pos, const int par_id,
	 const int ch_id, const int r_types,  const int max_r):
    hist{history(hist_lenght,pos)},
    resources{new int [max_r*r_types]},
    position{pos},
    parent_id{par_id},
    child_id{ch_id},
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


  
  Group(const int init_lenght, const int hist_lenght, 
	const int resource_types,  const int max_resources) : 
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


  
