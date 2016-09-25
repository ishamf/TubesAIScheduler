#include "State.hpp"

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

  std::uniform_int_distribution<int> room_idx_dist(0,rooms.size()-1);
  std::uniform_int_distribution<int> day_dist(0,4);

  for( auto& it : courses ){
    // random location
    shared_ptr<Classroom> room = rooms[ room_idx_dist(generator) ];

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
  // TODO : calculate fitness score
  return 1;
}

State State::mutate(){
  State s = *this;
  // TODO : alter state randomly
  return s;
}

State State::crossover( const State& lhs, const State& rhs){
  State res = lhs;
  // TODO : Do crossover
  return res;
}
