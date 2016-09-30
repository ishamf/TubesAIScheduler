#ifndef STATE_HPP
#define STATE_HPP

#include "Classroom.hpp"
#include "Course.hpp"
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include <iterator>

using namespace std;

class State {
public:
  State(const RoomVector& rooms, const CourseVector& courses);
  State(const State& s);

  void init_random_schedule();

  int fitness_score();
  State mutate();
  //static State crossover( const State&, const State& );
  friend void crossover( State&, State& );

private:

  // all variable should be kept immutable
  RoomVector rooms;
  CourseVector courses;
};

#endif
