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

void State::init_random_schedule(){
  //Mersenne Twister Random generator
  typedef std::mt19937 MyRNG;
  uint32_t seed_val = std::chrono::system_clock::now().time_since_epoch().count();
  MyRNG generator;
  generator.seed(seed_val);

  std::uniform_int_distribution<int> day_dist(0,4);

  for( auto& it : courses ){
    // random location & day
    auto& crooms = it->get_possible_classroom();
    std::uniform_int_distribution<int> room_idx_dist(0,crooms.size()-1);

    shared_ptr<Classroom> room;

    vector<Day> room_possible_day;
	vector<Day> course_possible_day;
	vector<Day> possible_day;
	while (possible_day.empty()) { //if no possible_day for selected room and course
		room = crooms[ room_idx_dist(generator) ];    
		room_possible_day = room->get_possible_day();
		course_possible_day = it->get_possible_day();
		//intersect to find possible day for course it in room
		std::set_intersection(room_possible_day.begin(),room_possible_day.end(),course_possible_day.begin(),course_possible_day.end(),back_inserter(possible_day));
	}
    Day d = static_cast<Day>( day_dist(generator) );
	//search for a day that is possible
	while( !(std::find(possible_day.begin(), possible_day.end(), d) != possible_day.end())) {
		d = static_cast<Day>( day_dist(generator) );
	}
	
	// random time
    const int ot = std::max( room->open_time, it->open_time );
    const int ct = std::min( room->close_time, it->close_time );
    std::uniform_int_distribution<int> start_time_dist(ot,ct-it->duration);
    int st = start_time_dist(generator);
    int et = st + it->duration;

    it->set_schedule(Schedule(room,d,st,et));
  }
  
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

State State::mutate(){
  State s = *this;
  //alter state randomly
  
  //Mersenne Twister Random generator
  typedef std::mt19937 MyRNG;
  uint32_t seed_val = std::chrono::system_clock::now().time_since_epoch().count();
  MyRNG generator;
  generator.seed(seed_val);
  
  std::uniform_int_distribution<int> day_dist(0,4);
  std::uniform_int_distribution<int> course_dist(0,(s.courses.size()-1));
  
  //random course
  shared_ptr<Course> altered_course = s.courses[course_dist(generator)];
  
  // random location & day
  auto& crooms = altered_course->get_possible_classroom();
  std::uniform_int_distribution<int> room_idx_dist(0,crooms.size()-1);

  shared_ptr<Classroom> room;

  vector<Day> room_possible_day;
  vector<Day> course_possible_day;
  vector<Day> possible_day;
  while (possible_day.empty()) { //if no possible_day for selected room and course
    room = crooms[ room_idx_dist(generator) ];    
    room_possible_day = room->get_possible_day();
    course_possible_day = altered_course->get_possible_day();
    //intersect to find possible day for course altered_course in room
    std::set_intersection(room_possible_day.begin(),room_possible_day.end(),course_possible_day.begin(),course_possible_day.end(),back_inserter(possible_day));
  }
  Day d = static_cast<Day>( day_dist(generator) );
  //search for a day that is possible
  while( !(std::find(possible_day.begin(), possible_day.end(), d) != possible_day.end())) {
    d = static_cast<Day>( day_dist(generator) );
  }


  // random time
  const int ot = std::max( room->open_time, altered_course->open_time );
  const int ct = std::min( room->close_time, altered_course->close_time );
  std::uniform_int_distribution<int> start_time_dist(ot,ct-altered_course->duration);
  int st = start_time_dist(generator);
  int et = st + altered_course->duration;

  altered_course->set_schedule(Schedule(room,d,st,et));
  /*for (auto& it : s.courses) {
    std::cout << it->get_schedule().room->name << "_" << static_cast<int>(it->get_schedule().day) << "_" << it->get_schedule().start_time << "_" << it->get_schedule().end_time << "\n";
  }*/
  return s;
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
