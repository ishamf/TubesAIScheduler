#include "Annealing.hpp"
#include <iostream>

Annealing::Annealing(State init, const double t, const double c) : currentstate(init), temp(t), coolingrate(c) {

}

double Annealing::countAcceptanceRate(const int currentscore, const int newscore) {
  return (exp((currentscore-newscore)/temp));
}

void Annealing::simulatedAnnealing() {
  //currentstate.mutate();
  cout << currentstate.fitness_score() << "\n";
  int count = 0;
  while ((currentstate.fitness_score() > 0) && (temp > 1)) {
	  cout << "1";
    State newstate = currentstate;
	newstate = newstate.mutate();
	cout << "2";
    int currentscore = currentstate.fitness_score();
    int newscore = newstate.fitness_score();
	temp *= 1-coolingrate;
    if (newscore < currentscore) {
      currentstate = newstate;
	  cout << "3a";
    }
	else {
	  double acceptanceRate = countAcceptanceRate(currentscore,newscore);
	  double randomscore = (rand()%100)/100.00;
	  cout << "\n\n acc rate : " << acceptanceRate << "\n\n";
	  cout << "\n\n random score : " << randomscore << "\n\n";
      if (acceptanceRate > randomscore) {
        currentstate = newstate;
		cout << "3c";
      }
	  cout << "3d";
    }
	count++;
	cout << "fitness: " << currentstate.fitness_score() << "\n";
	cout << "\ncount : " << count << "\n";
	cout << "temp : " << temp << "\n";
  }
	//Use hill climbing here

}

void Annealing::hillClimbing() {
  int count = 0;
  while ((currentstate.fitness_score() > 0) && (count < 100000)) {
    cout << "1";
    State newstate = currentstate;
	newstate = newstate.mutate();
	cout << "2";
    int currentscore = currentstate.fitness_score();
    int newscore = newstate.fitness_score();
    if (newscore < currentscore) {
      currentstate = newstate;
	  cout << "3a";
    }
	count++;
	cout << "fitness: " << currentstate.fitness_score() << "\n";
	cout << "\ncount : " << count << "\n";
	cout << "temp : " << temp << "\n";
  }
}
