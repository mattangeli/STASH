#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include <vector>
#include <memory>         

/*--------------------
    History Class
--------------------*/

/*---------------------------------------------------------------------------
  Class for the history of the walker: it saves all the positions and the
  time spent in every block. In the future it will save also the cost.
---------------------------------------------------------------------------*/


class history {
    /*--------------------------------------------------------------------------
      length  in input describes the starting value for the history length,
              and after it is used to keep trace of the number of steps done
      skip    is the distance in record between one chronological record and
              the next (2 for the time, maybe one for the cost in the future..)
    --------------------------------------------------------------------------*/
    int length, _skip;
    std::vector<float> record;
    std::vector<int> positions;
public:
    /* Default constructor */
    history():
        length{0},
        _skip{1},
        record{std::vector<float>()},
        positions{std::vector<int>()}
    {}

    /* Constructor for history of positions and times */
 history(const int pos, const float _time):
        length{1},
        _skip{3},
        record{std::vector<float>(3,0.)},
        positions{std::vector<int>(1,0)}
	{
	  positions[0]=pos;
	  record[0]=_time;
    }

    /* These functions add the time spent in the queue and ??? */
    void addtimeque(const float T){record[_skip*(length-1)+1]+=T;}
    void addtimeexe(const float T){record[_skip*(length-1)+2]=T;}
    int len() const noexcept {return length;}
    int skip() const noexcept {return _skip;}


    const std::vector<int>  get_positions() const noexcept { return positions; }
    const std::vector<float>  get_record() const noexcept { return record; }

    const std::vector<float>  get_times(){
      std::vector<float> times(2*length);
      for (auto i=0;i<length; i++){
	times[2*i]=record[_skip*i+1];
	times[2*i+1]=record[_skip*i+2];
      }						
      return times;
    }


    /* This function update the position in the history of the walker */
    void next_step(const int npos){
	auto new_time=record[(length-1)*_skip]+record[(length-1)*_skip+1]+record[(length-1)*_skip+2];
	record.push_back(new_time);
        record.push_back(0.);
        record.push_back(0.);
        positions.push_back(npos);
	length++;
    }
    

};

/* Overload the << operator for the history */
std::ostream& operator<<(std::ostream& os, const history& v);


#endif // HISTORY_H
