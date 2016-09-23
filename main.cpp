#include <iostream>

#include "Course.hpp"
#include "Classroom.hpp"

#include <memory>

using namespace std;

int main(){
  const shared_ptr<Classroom> room( new Classroom("7606",8,16) );
  shared_ptr<Course> course( new Course("AI",2, 7, 15) );

  course->seed_domain(room);

  const set<Schedule>& pst = course->get_possible_schedule();

  for( auto it : pst ){
    cout << static_cast<int>(it.day)+1 << " " << it.start_time << endl;
  }

  return 0;
}
