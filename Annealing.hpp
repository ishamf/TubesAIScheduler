#ifndef ANNEALING_HPP
#define ANNEALING_HPP

#include "State.hpp"
#include <cmath>

class Annealing {
public:
  Annealing(State init, const double t, const double c);
  double countAcceptanceRate(const int currentscore, const int newscore);
  void simulatedAnnealing();
  void hillClimbing();

  State currentstate;
  double temp;
  const double coolingrate;
};


#endif
