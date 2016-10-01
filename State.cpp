#include "State.hpp"
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <chrono>
#include <random>

// do deep copy for courses and shallow copy for classroom
State::State(const RoomVector& r, const CourseVector& c) : rooms(r){
  for( auto& it : c ){
    courses.emplace_back(new Course(*it));
  }
}

State::State(const State& s) : State(s.rooms,s.courses){
}

int State::fitness_score(){
  int fit = 0;
  for (int i = 0;i < courses.size();i++) {

    //For Debugging Purposes
    //printf("%d %d %d\n", courses[i]->get_schedule().day, courses[i]->get_schedule().start_time, courses[i]->get_schedule().end_time);

    for (int j = i+1;j < courses.size();j++) {
      if (Schedule::intersect(courses[i]->get_schedule(), courses[j]->get_schedule())) {
        fit++;
      }
    }
  }
  return fit;
}

CourseVector State::get_courses() const
{
	CourseVector cs;
	for (auto& it : courses) {
		cs.emplace_back(new Course(*it));
	}

	return cs;
}

void crossover( State& lhs, State& rhs){
  std::random_device rd;
  std::mt19937 seed(rd());
  std::uniform_int_distribution<int> mid(0, (lhs.courses.size()-2));

  //For Debugging Purposes
  /*for (int i = 0;i < lhs.courses.size();i++) {
    printf("lhs course %d: %d %d %d\n", i+1, lhs.courses[i]->get_schedule().day, lhs.courses[i]->get_schedule().start_time, lhs.courses[i]->get_schedule().end_time);
    printf("rhs course %d: %d %d %d\n", i+1, rhs.courses[i]->get_schedule().day, rhs.courses[i]->get_schedule().start_time, rhs.courses[i]->get_schedule().end_time);
  }
  printf("%d\n", mid(seed));
  */
  for (int i = 0;i < mid(seed);i++) { // <---- still need a better random algorithm
    const Schedule s = lhs.courses[i]->get_schedule();
    lhs.courses[i]->set_schedule(rhs.courses[i]->get_schedule());
    rhs.courses[i]->set_schedule(s);
  }

  //For Debugging Purposes
  /*for (int i = 0;i < lhs.courses.size();i++) {
    printf("lhs course %d: %d %d %d\n", i+1, lhs.courses[i]->get_schedule().day, lhs.courses[i]->get_schedule().start_time, lhs.courses[i]->get_schedule().end_time);
    printf("rhs course %d: %d %d %d\n", i+1, rhs.courses[i]->get_schedule().day, rhs.courses[i]->get_schedule().start_time, rhs.courses[i]->get_schedule().end_time);
  }
  */
}
