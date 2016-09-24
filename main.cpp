#include <iostream>

#include "Course.hpp"
#include "Classroom.hpp"

#include <memory>

using namespace std;

int main(){
  const shared_ptr<Classroom> room( new Classroom("7606",8,16) );
  const shared_ptr<Classroom> room2( new Classroom("7602",8,16) );
  shared_ptr<Course> course( new Course("AI",2, 7, 15) );

//  course->set_schedule(Schedule(room,Day::Monday,8,9));
//  course->get_schedule();

  Schedule s1(room,Day::Monday,8,9);
  Schedule s2(room2,Day::Monday,7,9);

  cout << Schedule::intersect(s1,s2) << endl;


  return 0;
}
