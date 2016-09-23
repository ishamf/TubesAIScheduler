#include "Course.hpp"
#include <cassert>
#include <algorithm>


Course::Course(const string& n, const int d, const int ot, const int ct )
:
name(n),
duration(d),
open_time(ot),
close_time(ct)
{

}

const set<Schedule>& Course::get_possible_schedule() const {
  return possible_schedule;
}

void Course::seed_domain(const shared_ptr<Classroom>& room, const Day day){

  const int ot = std::max( room->open_time, open_time );
  const int ct = std::min( room->close_time, close_time );

  for( int t = ot; t + duration <= ct; ++ t ){
    possible_schedule.insert(Schedule(room,day,t,t+duration));
  }
}

void Course::seed_domain(const shared_ptr<Classroom>& room){
  seed_domain(room,Day::Monday);
  seed_domain(room,Day::Tuesday);
  seed_domain(room,Day::Wednesday);
  seed_domain(room,Day::Thursday);
  seed_domain(room,Day::Friday);
}

void Course::clear_domain(){
  possible_schedule.clear();
}

void Course::remove_from_domain(const Schedule& s){
  possible_schedule.erase( s );
}
