#include <iostream>

#include "Course.hpp"
#include "Classroom.hpp"

#include <memory>

using namespace std;

int main(){
  const shared_ptr<Classroom> room( new Classroom("7606",8,16) );
  shared_ptr<Course> course( new Course("AI",Course::Day::Thursday, room, 2) );

  course->seed_domain_by_room_schedule();

  const set<int>& pst = course->get_possible_start_time();

  for( auto it : pst ){
    cout << it << endl;
  }

  return 0;
}
