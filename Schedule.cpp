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

std::ostream& operator<< (std::ostream& stream, const Schedule& schedule){
  string day_str;

  switch(schedule.day){
  case Day::Monday: day_str = "Monday"; break;
  case Day::Tuesday: day_str = "Tuesday"; break;
  case Day::Wednesday: day_str = "Wednesday"; break;
  case Day::Thursday: day_str = "Thursday"; break;
  case Day::Friday: day_str = "Friday"; break;
  default: day_str = "Unknown"; break;
  }

  stream << "Schedule: room " << (schedule.room)->name
      << " day " << day_str << " st " << schedule.start_time << " et " << schedule.end_time;
  return stream;
}
