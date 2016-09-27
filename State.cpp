#include "State.hpp"
#include <iostream>
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
  // TODO : alter state randomly
  
  //random course
  shared_ptr<Course> altered_course = s.courses[rand()%s.courses.size()];
  
  // random location
  auto& crooms = altered_course->get_possible_classroom();
  shared_ptr<Classroom> room  =crooms[rand()%crooms.size()];
  
  // random time
  const int ot = std::max( room->open_time, altered_course->open_time );
  const int ct = std::min( room->close_time, altered_course->close_time );

  Day d = static_cast<Day>( rand()%5 );
  int st = rand()%(ct-altered_course->duration-ot)+ot;
  int et = st + altered_course->duration;
  
  altered_course->set_schedule(Schedule(room,d,st,et));
  
  /*for (auto& it : s.courses) {
    std::cout << it->get_schedule().room->name << "_" << static_cast<int>(it->get_schedule().day) << "_" << it->get_schedule().start_time << "_" << it->get_schedule().end_time << "  ";
  }
  std::cout << "\n";*/
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
