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
  int lenght, _skip;
  std::vector<float> record;
  std::vector<int> positions;
public:
  //default constructor
 history(): 
  lenght{0},
    record{std::vector<float>()},
      positions{std::vector<int>()}, 
	_skip{1}
	{}
	
	//Constructor for history of positions and times
 history(const int pos): 
     lenght{1},
       record{std::vector<float>(2,0.)},
	 positions{std::vector<int>(1,0)},
    _skip{2}
  {positions[0]=pos;}
  
  //These functions add the time spent in the que and  
  void addtimeque(const float T){record[_skip*(lenght-1)]+=T;};
  void addtimeexe(const float T){record[_skip*(lenght-1)+1]=T;};
  int len() const noexcept {return lenght;};
  int skip() const noexcept {return _skip;};
  const std::vector<int>  get_positions() const noexcept { return    positions;   };
  const std::vector<float>  get_record() const noexcept { return    record;   };
  //This function update the position in the history of 
  //the walker
  void nextstep(const int npos){
    lenght++;
    record.push_back(0.);
    record.push_back(0.);
    positions.push_back(npos);
  };
    

};
      
std::ostream& operator<<(std::ostream& os, const history& v) {
  os << v.len() << "  ";
  for (const auto l : v.get_positions())
    os << l << "  ";
  for (const auto l : v.get_record())
    os << l << "  ";
  os << std::endl;
  return os;
};
