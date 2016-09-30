#include <iostream>

#include "Course.hpp"
#include "Classroom.hpp"
#include "State.hpp"
#include "Annealing.hpp"
//#include "GA.hpp"

#include <memory>

using namespace std;

int main(){
  vector<Day> days;
  vector<Day> days2;
  days.emplace_back(Day::Wednesday);
  days.emplace_back(Day::Monday);
  days.emplace_back(Day::Friday);
  days2.emplace_back(Day::Tuesday);
  days2.emplace_back(Day::Thursday);
  RoomVector rooms;
  rooms.emplace_back(new Classroom("7602",7,14));
  rooms.emplace_back(new Classroom("7603",7,14,days));
  rooms.emplace_back(new Classroom("7610",9,12));
  rooms.emplace_back(new Classroom("Labdas2",10,14,days2));

  CourseVector courses;
  RoomVector room1, room2;
  room1.emplace_back(new Classroom("7602",7,14));
  room2.emplace_back(new Classroom("7610",9,12));
  
  vector<Day> day34, day345;
  day34.emplace_back(Day::Wednesday);
  day34.emplace_back(Day::Thursday);
  day345.emplace_back(Day::Wednesday);
  day345.emplace_back(Day::Thursday);
  day345.emplace_back(Day::Friday);
  courses.emplace_back(new Course("IF2110",4, 7, 12, room1));
  courses.emplace_back(new Course("IF2130",3, 10, 16, rooms, day34));
  courses.emplace_back(new Course("IF2150",2, 9, 13, rooms, days));
  courses.emplace_back(new Course("IF2170",3, 7, 12, room2));
  courses.emplace_back(new Course("IF3110",2, 7, 9, room1));
  courses.emplace_back(new Course("IF3130",2, 7, 12, rooms, day345));
  courses.emplace_back(new Course("IF3170",2, 7, 9, room1));
  courses.emplace_back(new Course("IF3111",2, 7, 12, rooms));

  shared_ptr<Classroom> room (new Classroom("7606",8,16));
  Course course("AI",2,7,15, {room});
  course.set_schedule(Schedule(room,Day::Tuesday,8,10));
  course.get_schedule();

  Course course2(course);

  //cout << course2.get_schedule().start_time << endl;
  //cout << course2.get_possible_classroom()[0]->open_time << endl;

//  course->set_schedule(Schedule(room,Day::Monday,8,9));
//  course->get_schedule();

//  Schedule s1(room,Day::Monday,8,9);
//  Schedule s2(room2,Day::Monday,7,9);

//  cout << Schedule::intersect(s1,s2) << endl;

  //genetic_algorithm(rooms, courses, 10, 0.1, 0.3);
  /*
  State s(rooms,courses);
  s.init_random_schedule();

  State u(rooms,courses);
  u.init_random_schedule();

  printf("Conflict: %d\n", s.fitness_score());
  printf("Conflict: %d\n", u.fitness_score());
  crossover(s, u);
*/
  //course.print_data();
  //course2.print_data();
  State s(rooms,courses);
  s.init_random_schedule();
  for (int i=0 ; i<10 ; i++)
    s = s.mutate();

  Annealing a(s,100,0.0003);
  //for (int i=0 ; i<100 ; i++)
	  //cout << a.countAcceptanceRate(50,rand()%50) << endl;

  //a.simulatedAnnealing();
  a.hillClimbing();
  
  
  return 0;
}
