#ifndef ANNEALING_HPP
#define ANNEALING_HPP

#include "State.hpp"
#include <cmath>

class Annealing {
public:
  Annealing(State init, const double t, const double c);
  double countAcceptanceRate(const int currentscore, const int newscore);

  template<class URNG>
  void simulatedAnnealing( URNG& generator, const int loop );

  template<class URNG>
  void hillClimbing( URNG& generator, const int loop );

  State currentstate;
  double temp;
  const double coolingrate;
};



template<class URNG>
void Annealing::simulatedAnnealing( URNG& generator, const int loop ) {
  int count = 0;
  while ((currentstate.fitness_score() > 0) && (temp > 1)) {
    State newstate = currentstate;
    newstate = newstate.mutate( generator );
    int currentscore = currentstate.fitness_score();
    int newscore = newstate.fitness_score();
    temp *= 1-coolingrate;
    if (newscore < currentscore) { //accept better soltion
      currentstate = newstate;
    }
    else {
      double acceptanceRate = countAcceptanceRate(currentscore,newscore);
      double randomscore = (rand()%100)/100.00;
      if (acceptanceRate > randomscore) { //accept worse solution base on probability
        currentstate = newstate;
      }
    }
	  count++;
  }

	//Use hill climbing here if SA temp drop below 1
  if (currentstate.fitness_score() > 0) {
	  hillClimbing(generator, loop);
  }
}

template<class URNG>
void Annealing::hillClimbing( URNG& generator, const int loop ) {
  int count = 0;
  while ((currentstate.fitness_score() > 0) && (count < loop)) {
    State newstate = currentstate;
    newstate = newstate.mutate( generator );
    int currentscore = currentstate.fitness_score();
    int newscore = newstate.fitness_score();
    if (newscore < currentscore) { //only accept better solution
      currentstate = newstate;
    }
    count++;
  }
}

#endif
