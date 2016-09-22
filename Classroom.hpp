#ifndef CLASSROOM_HPP
#define CLASSROOM_HPP

#include <string>

using namespace std;

class Classroom {
public:
  Classroom(const string& name, const int ot, const int ct);
  
  const string name;
  const int open_time;
  const int close_time;
};

#endif