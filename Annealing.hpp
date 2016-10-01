#ifndef ANNEALING_HPP
#define ANNEALING_HPP

#include "State.hpp"
#include <cmath>

class Annealing {
public:
  Annealing(State init, const double t, const double c);
  double countAcceptanceRate(const int currentscore, const int newscore);

  template<class URNG>
  void simulatedAnnealing( URNG& generator );

  template<class URNG>
  void hillClimbing( URNG& generator );

  State currentstate;
  double temp;
  const double coolingrate;
};



template<class URNG>
void Annealing::simulatedAnnealing( URNG& generator ) {
  //currentstate.mutate();
  cout << currentstate.fitness_score() << "\n";
  int count = 0;
  while ((currentstate.fitness_score() > 0) && (temp > 1)) {
	  cout << "1";
    State newstate = currentstate;
	newstate = newstate.mutate( generator );
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
  if (currentstate.fitness_score() > 0) {
	  hillClimbing(generator);
  }
}

template<class URNG>
void Annealing::hillClimbing( URNG& generator ) {
  int count = 0;
  while ((currentstate.fitness_score() > 0) && (count < 100000)) {
    cout << "1";
    State newstate = currentstate;
  	newstate = newstate.mutate( generator );
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

#endif
