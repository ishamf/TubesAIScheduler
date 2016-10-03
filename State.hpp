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
  State();
  State(const RoomVector& rooms, const CourseVector& courses);
  State(const State& s);

  template<class URNG>
  void init_random_schedule(  URNG& generator);

  int fitness_score();
  double room_percentage();

  template<class URNG>
  State mutate( URNG& generator );
  //static State crossover( const State&, const State& );
  friend void crossover( State&, State& );

  CourseVector get_courses() const;
  RoomVector get_rooms() const;

  friend std::ostream& operator<< (std::ostream& stream, const State& state);

private:

  // all variable should be kept immutable
  RoomVector rooms;
  CourseVector courses;
};

template<class URNG>
Schedule generate_random_schedule(const shared_ptr<Course>& course, URNG& generator) {
  // random location & day
  std::vector<shared_ptr<Classroom>> crooms = course->get_possible_classroom();
  shuffle( crooms.begin(), crooms.end(), generator);

  const auto& course_possible_day = course->get_possible_day();

  vector<pair<shared_ptr<Classroom>,Day>> possible;
  for( auto& r : crooms ){
    const auto& room_possible_day = r->get_possible_day();

    //intersect to find possible day for course it in room
    vector<Day> possible_day;
    std::set_intersection(room_possible_day.begin(),room_possible_day.end(),course_possible_day.begin(),course_possible_day.end(),back_inserter(possible_day));
    for( auto& d:possible_day){
      possible.push_back(make_pair(r,d));
    }
  }

  possible.erase(
    remove_if(possible.begin(),possible.end(),[&course](const pair<shared_ptr<Classroom>,Day>& location_day){
      const shared_ptr<Classroom>& room = location_day.first;
      const int ot = std::max( room->open_time, course->open_time );
      const int ct = std::min( room->close_time, course->close_time );
      if( ct-course->duration < ot ) return true;
      return false;
    }),
    possible.end()
  );

  if( possible.empty() ) throw new exception();

  std::uniform_int_distribution<int> location_day_dist(0,possible.size()-1);

  pair<shared_ptr<Classroom>,Day> location_day = possible[ location_day_dist(generator) ];

  shared_ptr<Classroom> room = location_day.first;
  Day d = location_day.second;
  // random time
  const int ot = std::max( room->open_time, course->open_time );
  const int ct = std::min( room->close_time, course->close_time );
  std::uniform_int_distribution<int> start_time_dist(ot,ct-course->duration);
  int st = start_time_dist(generator);
  int et = st + course->duration;

  return Schedule(room,d,st,et);
}

template<class URNG>
void State::init_random_schedule( URNG& generator ){
  for( auto& it : courses ){
    it->set_schedule(generate_random_schedule(it, generator));
  }
}


template<class URNG>
State State::mutate( URNG& generator ){
  State s = *this;
  //alter state randomly
  
  vector<int> conflict_courses;

  for (int i = 0;i < s.courses.size()-1;i++) {
    int j = i + 1;
    while ((j < s.courses.size()) && !Schedule::intersect(s.courses[i]->get_schedule(), s.courses[j]->get_schedule())) {
      j++;
    }
    if (j < s.courses.size()) {
      conflict_courses.push_back(i);
    }
  }

  std::uniform_int_distribution<int> course_dist(0,(conflict_courses.size()-1));

  //random course
  shared_ptr<Course> altered_course = s.courses[conflict_courses[course_dist(generator)]];

  altered_course->set_schedule( generate_random_schedule( altered_course, generator ) );
/*
  for (auto& it : s.courses) {
    std::cout << *it << endl;
  }
*/
  return s;
}


#endif
