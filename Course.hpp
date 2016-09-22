#ifndef MATA_KULIAH_H
#define MATA_KULIAH_H

#include "Classroom.hpp"
#include <memory>
#include <set>
#include <string>

class Course {
public:
  Course(const string& name, const shared_ptr<Classroom>& room, const int duration );
  
  const string& get_name() const;
  int get_duration() const;
  const set<int>& get_possible_start_time() const;
  
  void seed_single_domain(int start_time);
  void seed_domain_by_room_schedule();
  void remove_from_domain(int start_time);
  
private:
  set<int> possible_start_time;
  const string name;
  const shared_ptr<Classroom> room;
  const int duration;
};

#endif