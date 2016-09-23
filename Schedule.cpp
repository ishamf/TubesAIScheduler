#include "Schedule.hpp"

Schedule::Schedule(const shared_ptr<Classroom>& r,const Day d,int s,int e)
: room(move(r)), day(d), start_time(s), end_time(e){

}

bool Schedule::operator<(const Schedule& lhs) const{
  if( static_cast<int>(day) < static_cast<int>(lhs.day) )
    return true;
  if( static_cast<int>(day) > static_cast<int>(lhs.day) )
    return false;

  return ( start_time < lhs.start_time );
}
