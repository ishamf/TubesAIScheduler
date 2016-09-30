#include "Classroom.hpp"

Classroom::Classroom(const string& n, const int ot, const int ct, const vector<Day>& days) : 
name(n), open_time(ot), close_time(ct), possible_day(days) {
  
}

const vector<Day> Classroom::get_possible_day() const {
  return possible_day;
}