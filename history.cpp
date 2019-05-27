#include <iostream>
#include "history.h"


/* Overload the << operator for the history */
std::ostream& operator<<(std::ostream& os, const history& v) {
  os << "Total history length "<< v.len() << std::endl;
    for (const auto l : v.get_positions())
      os << "Positions history "<< l << std::endl;
    for (const auto l : v.get_record())
      os << "Record: Global time, Queue time, Exec time "<< l << std::endl;
    os << std::endl;
    return os;
}



