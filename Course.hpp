#ifndef MATA_KULIAH_H
#define MATA_KULIAH_H

#include "Schedule.hpp"
#include "Classroom.hpp"
#include <memory>
#include <set>
#include <string>
#include <exception>

class ScheduleNotDefined: public std::exception {
public:
  const char* what() const throw();
};

class ScheduleInvalid: public std::exception {
public:
  ScheduleInvalid(const string& v);
  const char* what() const throw();
private:
  const string message;
};


class Course {
public:
  Course(const string& name, const int duration, const int open_time, const int close_time );

  const set<Schedule>& get_possible_schedule() const;

  void check_schedule() const;
  void check_schedule(const Schedule& s) const;

  void set_schedule(const Schedule&);
  const Schedule& get_schedule() const ;


  const string name;
  const int duration;
  const int open_time;
  const int close_time;
private:
  unique_ptr<Schedule> schedule;
};

#endif
