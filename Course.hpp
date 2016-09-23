#ifndef MATA_KULIAH_H
#define MATA_KULIAH_H

#include "Schedule.hpp"
#include "Classroom.hpp"
#include <memory>
#include <set>
#include <string>

class Course {
public:
  Course(const string& name, const int duration, const int open_time, const int close_time );

  const set<Schedule>& get_possible_schedule() const;

  void seed_domain(const shared_ptr<Classroom>& room, const Day day);
  void seed_domain(const shared_ptr<Classroom>& room);
  void clear_domain();
  void remove_from_domain(const Schedule&);

  const string name;
  const int duration;
  const int open_time;
  const int close_time;
private:
  set<Schedule> possible_schedule;
};

#endif
