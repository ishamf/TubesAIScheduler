#include "Course.hpp"
#include <cassert>

Course::Course(const string& n, const Day dy, const shared_ptr<Classroom>& r, const int d )
:
name(n),
room(std::move(r)),
duration(d),
day(dy) {

}

const set<int>& Course::get_possible_start_time() const {
  return possible_start_time;
}

Course::Day Course::get_day() const {
  return day;
}

int Course::get_duration() const {
  return duration;
}
const string& Course::get_name() const {
  return name;
}


void Course::seed_single_domain(int start_time){
  assert( room->open_time < start_time && start_time + duration <= room->close_time );
  possible_start_time.clear();
  possible_start_time.insert(start_time);
}

void Course::seed_domain_by_room_schedule(){
  possible_start_time.clear();

  const int ot = room->open_time;
  const int ct = room->close_time;

  for( int t = ot; t + duration <= ct; ++ t ){
    possible_start_time.insert(t);
  }
}

void Course::remove_from_domain(int start_time){
  possible_start_time.erase( start_time );
}
