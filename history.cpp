#include <iostream>
#include "history.h"


/* Overload the << operator for the history */
std::ostream& operator<<(std::ostream& os, const history& v) {
    os << v.len() << "  ";
    for (const auto l : v.get_positions())
      os << l << "  ";
    for (const auto l : v.get_record())
        os << l << "  ";
    os << std::endl;
    return os;
}
