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

bool Schedule::intersect(const Schedule& lhs, const Schedule& rhs){
  if( lhs.day != rhs.day ) return false;
  if( lhs.room != rhs.room ) return false;
  if( lhs.end_time - 1 < rhs.start_time ) return false;
  if( rhs.end_time - 1 < lhs.start_time ) return false;

  return true;
}

void Schedule::printdata() const{
  cout << "Schedule: room " << room->name;
  printf(" day %d st %d et %d\n", day, start_time, end_time);
}
