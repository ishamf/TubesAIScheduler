#include "Annealing.hpp"
#include <iostream>

Annealing::Annealing(State init, const double t, const double c) : currentstate(init), temp(t), coolingrate(c) {

}

double Annealing::countAcceptanceRate(const int currentscore, const int newscore) {
  return (exp((currentscore-newscore)/temp));
}
