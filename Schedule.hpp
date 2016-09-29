#ifndef SCHEDULE_HPP
#define SCHEDULE_HPP

#include <memory>
#include "Classroom.hpp"
#include <iostream>

using namespace std;

enum class Day {
  Monday,
  Tuesday,
  Wednesday,
  Thursday,
  Friday
};

class Schedule {
public:
  Schedule(const shared_ptr<Classroom>&,const Day,int,int);

  bool operator<(const Schedule&) const;

  const shared_ptr<Classroom> room;
  const Day day;
  const int start_time;
  const int end_time;

  static bool intersect(const Schedule&, const Schedule& );

  void print_data() const;

};



#endif
