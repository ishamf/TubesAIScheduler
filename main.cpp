#include <iostream>

#include "Course.hpp"
#include "Classroom.hpp"
#include "State.hpp"
#include "Annealing.hpp"

#include <memory>

using namespace std;

int main(){
  RoomVector rooms;
  rooms.emplace_back(new Classroom("7606",8,16));
  rooms.emplace_back(new Classroom("7602",8,16));

  CourseVector courses;
  courses.emplace_back(new Course("AI",2, 7, 15, rooms));
  courses.emplace_back(new Course("TBFO",3, 7, 12, rooms));
  courses.emplace_back(new Course("OS",4, 7, 12, rooms));
  courses.emplace_back(new Course("ST",4, 7, 12, rooms));
  courses.emplace_back(new Course("OOP",4, 7, 12, rooms));

  shared_ptr<Classroom> room (new Classroom("7606",8,16));
  Course course("AI",2,7,15, {room});
  Schedule sch(room,Day::Tuesday,8,10);
  cout << sch << endl;
  course.set_schedule(Schedule(room,Day::Tuesday,8,10));
  course.get_schedule();

  Course course2(course);

  cout << course2.get_schedule().start_time << endl;
  cout << course2.get_possible_classroom()[0]->open_time << endl;
  cout << course2 << endl;

  return 0;
}
