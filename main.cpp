#include <iostream>

#include "Course.hpp"
#include "Classroom.hpp"
#include "State.hpp"
#include "Annealing.hpp"
#include "GA.hpp"

#include <memory>
#include <random>
#include <chrono>

using namespace std;

int main(){
  set<Day> days {Day::Monday,Day::Wednesday,Day::Friday};
  set<Day> days2 {Day::Tuesday, Day::Thursday};
  RoomVector rooms;
  rooms.emplace_back(new Classroom("7602",7,14));
  rooms.emplace_back(new Classroom("7603",7,14,days));
  rooms.emplace_back(new Classroom("7610",9,12));
  rooms.emplace_back(new Classroom("Labdas2",10,14,days2));

  CourseVector courses;
  RoomVector room1, room2;
  room1.emplace_back(new Classroom("7602",7,14));
  room2.emplace_back(new Classroom("7610",9,12));

  set<Day> day34 {Day::Wednesday, Day::Thursday};
  set<Day> day345 {Day::Wednesday, Day::Thursday, Day::Friday};
  courses.emplace_back(new Course("IF2110",4, 7, 12, room1));
  courses.emplace_back(new Course("IF2130",3, 10, 16, rooms, day34));
  courses.emplace_back(new Course("IF2150",2, 9, 13, rooms, days));
  courses.emplace_back(new Course("IF2170",3, 7, 12, room2));
  courses.emplace_back(new Course("IF3110",2, 7, 9, room1));
  courses.emplace_back(new Course("IF3130",2, 7, 12, rooms, day345));
  courses.emplace_back(new Course("IF3170",2, 7, 9, room1));
  courses.emplace_back(new Course("IF3111",2, 7, 12, rooms));

  //Mersenne Twister Random generator
  /*
  typedef std::mt19937 MyRNG;
  uint32_t seed_val = std::chrono::system_clock::now().time_since_epoch().count();
  MyRNG generator;
  generator.seed(seed_val);
  cout << "Seed " << seed_val << endl;

  State s(rooms,courses);
  s.init_random_schedule( generator );

  Annealing a(s,100,0.0003);
  //for (int i=0 ; i<100 ; i++)
	  //cout << a.countAcceptanceRate(50,rand()%50) << endl;

  //a.simulatedAnnealing();
  a.hillClimbing( generator );
  */
  int dum;
  int last_worst = -1, last_best = -1, unchanged = 0;
  GA test1(rooms, courses, 50, 0.15, 0.1);
  test1.find_alpha_omega();
  while ((test1.get_alpha().fitness_score() > 0)&&(unchanged < 50)) {
    test1.selection();
    test1.xover();
    test1.mutation();
    test1.elitist();

    unchanged++;
    if (last_worst != test1.get_omega()){
      last_worst = test1.get_omega();
      unchanged = 0;
    }
    if (last_best != test1.get_alpha().fitness_score()){
      last_best = test1.get_alpha().fitness_score();
      unchanged = 0;
    }

    //printf("========>> %d\n", unchanged);
    //scanf("%d", &dum); //<- for step by step

  }
  printf("\n\n============DONE=============\n\n");
  State result = test1.get_alpha();
  cout << result << endl;
  return 0;
}
