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
