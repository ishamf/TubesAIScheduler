#include "State.hpp"
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <chrono>
#include <random>

// do deep copy for courses and shallow copy for classroom
State::State(){}

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

double State::room_percentage(){
  double room_hours = 0;
  //sum room hours
  for(auto& it : rooms) {
    double hours_per_day = it->close_time - it->open_time;
    room_hours += (hours_per_day * it->possible_day.size());
  }

  double course_hours = 0;
  for (int i = 0;i < courses.size();i++) {
    int start_i = courses[i]->get_schedule().start_time;
    int end_i = courses[i]->get_schedule().end_time;
    vector<int> vec_i;
    for (int x = start_i ; x < end_i ; x++) {
      vec_i.emplace_back(x);
    }
    std::sort(vec_i.begin(), vec_i.end());
    double reduction;

    //check intersection
    for (int j = i+1;j < courses.size();j++) {
      if (Schedule::intersect(courses[i]->get_schedule(), courses[j]->get_schedule())) {
        int start_j = courses[j]->get_schedule().start_time;
        int end_j = courses[j]->get_schedule().end_time;

        //make vec_j
        vector<int> vec_j;
        for (int x = start_j ; x < end_j ; x++) {
          vec_j.emplace_back(x);
        }
        std::sort(vec_j.begin(), vec_j.end());

        vector<int> diff;
        std::set_difference(vec_i.begin(), vec_i.end(), vec_j.begin(), vec_j.end(), 
                        std::inserter(diff, diff.begin()));
        vec_i = diff;
      }
    }
    course_hours += vec_i.size();
  }
  double result = course_hours/room_hours * 100;
  return result;
}

CourseVector State::get_courses() const
{
	CourseVector cs;
	for (auto& it : courses) {
		cs.emplace_back(new Course(*it));
	}

	return cs;
}

RoomVector State::get_rooms() const
{
	RoomVector rs;
	for (auto& it : rooms) {
		rs.emplace_back(new Classroom(*it));
	}

	return rs;
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

std::ostream& operator<< (std::ostream& stream, const State& state){
  stream << "State:" << endl;
  for( auto& it : state.courses ){
    stream << *it << endl;
  }
  return stream;
}
