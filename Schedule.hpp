#ifndef SCHEDULE_HPP
#define SCHEDULE_HPP

#include <memory>
#include "Classroom.hpp"
#include <iostream>
#include "Day.hpp"

using namespace std;

class Schedule {
public:
  Schedule(const shared_ptr<Classroom>&, const Day, int start, int end);

  bool operator<(const Schedule&) const;

  const shared_ptr<Classroom> room;
  const Day day;
  const int start_time;
  const int end_time;

  static bool intersect(const Schedule&, const Schedule& );

};

std::ostream& operator<< (std::ostream& stream, const Schedule& schedule);

#endif
