#ifndef CLASSROOM_HPP
#define CLASSROOM_HPP

#include <string>
#include <vector>
#include "Day.hpp"

using namespace std;

class Classroom {
public:
  Classroom(const string& name, const int ot, const int ct, const std::vector<Day>& days = every_day);
  const vector<Day> get_possible_day() const;
  
  const string name;
  const int open_time;
  const int close_time;
  vector<Day> possible_day;
};

#endif