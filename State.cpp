#include "State.hpp"
#include <iostream>
#include <ctime>
#include <stdlib.h>

// do deep copy for courses and shallow copy for classroom
State::State(const RoomVector& r, const CourseVector& c) : rooms(r){
  for( auto& it : c ){
    courses.emplace_back(new Course(*it));
  }
}

State::State(const State& s) : State(s.rooms,s.courses){
}

void State::init_random_schedule(){
  std::default_random_engine generator;

  std::uniform_int_distribution<int> day_dist(0,4);

  for( auto& it : courses ){
    // random location
    auto& crooms = it->get_possible_classroom();
    std::uniform_int_distribution<int> room_idx_dist(0,crooms.size()-1);

    shared_ptr<Classroom> room = crooms[ room_idx_dist(generator) ];

    // random time
    const int ot = std::max( room->open_time, it->open_time );
    const int ct = std::min( room->close_time, it->close_time );
    std::uniform_int_distribution<int> start_time_dist(ot,ct-it->duration);

    Day d = static_cast<Day>( day_dist(generator) );
    int st = start_time_dist(generator);
    int et = st + it->duration;

    it->set_schedule(Schedule(room,d,st,et));
  }
  
  std::cout << "Init\n";
  for (auto& it : courses) {
    std::cout << it->get_schedule().room->name << "_" << static_cast<int>(it->get_schedule().day) << "_" << it->get_schedule().start_time << "_" << it->get_schedule().end_time << "  ";
  }
  std::cout << "\n";
}

int State::fitness_score(){
  // TODO : calculate fitness score
  return 1;
}

State State::mutate(){
  State s = *this;
  // TODO : alter state randomly
  
  //std::default_random_engine generator( (unsigned int)time(0) );
  
  //random course
  //std::uniform_int_distribution<int> idx_dist(0,s.courses.size()-1);
  shared_ptr<Course> altered_course = s.courses[rand()%s.courses.size()];
  
  // random location
  auto& crooms = altered_course->get_possible_classroom();
  //std::uniform_int_distribution<int> room_idx_dist(crooms.size()-1);
  shared_ptr<Classroom> room  =crooms[rand()%crooms.size()];
  
  // random time
  const int ot = std::max( room->open_time, altered_course->open_time );
  const int ct = std::min( room->close_time, altered_course->close_time );
  //std::uniform_int_distribution<int> start_time_dist(ot,ct-altered_course->duration);
  //std::uniform_int_distribution<int> day_dist(0,4);

  Day d = static_cast<Day>( rand()%5 );
  //int st = start_time_dist(generator);
  int st = rand()%(ct-altered_course->duration-ot)+ot;
  int et = st + altered_course->duration;
  
  altered_course->set_schedule(Schedule(room,d,st,et));
  
  //std::cout << "size" << s.courses.size();
  for (auto& it : s.courses) {
    std::cout << it->get_schedule().room->name << "_" << static_cast<int>(it->get_schedule().day) << "_" << it->get_schedule().start_time << "_" << it->get_schedule().end_time << "  ";
  }
  std::cout << "\n";
  return s;
}

State State::crossover( const State& lhs, const State& rhs){
  State res = lhs;
  // TODO : Do crossover
  return res;
}
