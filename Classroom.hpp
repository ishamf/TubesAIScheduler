#ifndef CLASSROOM_HPP
#define CLASSROOM_HPP

#include <string>
#include <vector>
#include <memory>

using namespace std;

class Classroom;

typedef std::shared_ptr<Classroom> pRoom;
typedef std::vector<pRoom> RoomVector;

class Classroom {
public:
  Classroom(const string& name, const int ot, const int ct);
  
  const string name;
  const int open_time;
  const int close_time;
};

#endif