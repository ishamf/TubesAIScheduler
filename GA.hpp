#ifndef GA_HPP
#define GA_HPP

#include <iostream>
#include <chrono>
#include <random>
#include "State.hpp"

class GA {
public:
  GA(const RoomVector& r, const CourseVector& c, const int p, const float m, const float x);

  void selection();
  void xover();
  void mutation();
  void elitist();
private:
  vector<State> population;

  float totalfitness;
  const int pop;
  const float pmutate;
  const float pxover;

  State alpha;
  int omega;

  void find_alpha_omega();
};


#endif // GA_HPP
