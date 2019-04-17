#include <iostream>
#include "walker.h"


/* Overload the << operator for the walker */
std::ostream& operator<<(std::ostream& os, const walker& w) {
    os << w.get_parent_id() << "  ";
    os << w.get_child_id() << "  ";
    os << w.get_pos() << "  ";
    os << w.get_history() << " ";
    return os;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec){

  for(auto i : vec){
     os<<i<<"  ";

  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const Wlk_Resources& res) {
  os << res.get_resources()<<endl;
  os << res.get_variables()<<endl;
  return os;
};

