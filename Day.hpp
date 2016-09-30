#ifndef DAY_HPP
#define DAY_HPP

enum class Day {
  Monday = 1,
  Tuesday = 2,
  Wednesday = 3,
  Thursday = 4,
  Friday = 5,
  Undefined
};

const std::vector<Day> every_day = { Day::Monday, Day::Tuesday, Day::Wednesday, Day::Thursday, Day::Friday };

#endif