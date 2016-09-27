#include "Course.hpp"
#include <cassert>
#include <algorithm>

const char* ScheduleNotDefined::what() const throw() {
  return "Schedule is not defined";
}

ScheduleInvalid::ScheduleInvalid(const string& variable) : message("Schedule\'s "+variable+" is not valid") {}

const char* ScheduleInvalid::what() const throw() {
  return message.c_str();
}

Course::Course(const string& n, const int d, const int ot, const int ct )
:
name(n),
duration(d),
open_time(ot),
close_time(ct),
schedule(nullptr)
{

}

Course::Course(const Course& c) : Course(c.name,c.duration,c.open_time,c.close_time) {
  if( c.schedule )
    set_schedule(*c.schedule);
}

const Schedule& Course::get_schedule() const {
  if( !schedule )
    throw ScheduleNotDefined();
  return *schedule;
}

void Course::set_schedule(const Schedule& s){
  check_schedule(s);
  schedule.reset();
  schedule = unique_ptr<Schedule>( new Schedule(s) );
}

void Course::check_schedule() const {
  if( !schedule )
    throw ScheduleNotDefined();
  check_schedule(*schedule);
}

void Course::check_schedule(const Schedule& s) const {
  const int ot = std::max( s.room->open_time, open_time );
  const int ct = std::min( s.room->close_time, close_time );

  if( s.start_time < ot ) throw ScheduleInvalid("start_time");
  if( s.end_time > ct ) throw ScheduleInvalid("end_time");
  if( s.end_time - s.start_time != duration ) throw ScheduleInvalid("duration");
}
