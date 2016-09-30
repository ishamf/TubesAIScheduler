#ifndef MATA_KULIAH_H
#define MATA_KULIAH_H

#include "Schedule.hpp"
#include "Classroom.hpp"
#include <memory>
#include <set>
#include <string>
#include <exception>
#include <vector>
#include <ostream>

class Course;

typedef shared_ptr<Course> pCourse;
typedef std::vector<pCourse> CourseVector;

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


const std::vector<Day> every_day = { Day::Monday, Day::Tuesday, Day::Wednesday, Day::Thursday, Day::Friday };

class Course {
public:
  Course(const string& name, const int duration, const int open_time, const int close_time, const vector<shared_ptr<Classroom>>& rooms, const std::vector<Day>& days = every_day);
  Course(const Course& c);

  void check_schedule() const;
  void check_schedule(const Schedule& s) const;

  const vector<shared_ptr<Classroom>>& get_possible_classroom() const;
  const vector<Day> get_possible_day() const;
  void set_schedule(const Schedule&);
  const Schedule& get_schedule() const ;


  const string name;
  const int duration;
  const int open_time;
  const int close_time;

  friend std::ostream& operator<< (std::ostream& stream, const Course& course);

private:
  unique_ptr<Schedule> schedule;
  vector<shared_ptr<Classroom>> possible_classroom;
  vector<Day> possible_day;
};

std::ostream& operator<< (std::ostream& stream, const Course& course);

#endif
