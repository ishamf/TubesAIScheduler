#ifndef DAY_HPP
#define DAY_HPP

enum class Day {
  Monday,
  Tuesday,
  Wednesday,
  Thursday,
  Friday,
  Undefined
};

const std::vector<Day> every_day = { Day::Monday, Day::Tuesday, Day::Wednesday, Day::Thursday, Day::Friday };

#endif