#ifndef VIEW_ADAPTER_HPP
#define VIEW_ADAPTER_HPP

#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <chrono>

#include "Course.hpp"
#include "State.hpp"
#include "Classroom.hpp"

struct CourseSchedule {
	int day;
	int time;
	int duration;
	string room_name;
};

class ViewAdapter {
public:
	ViewAdapter();

	void add_room(const string room_description);
	void add_course(const string course_description);

	void move_course(const string course_name, const string room_name,
					 const int dest_day, const int dest_time);

	CourseSchedule get_course_result(const string course_name) const;

	void randomize_schedule();

private:
	std::map<std::string, pCourse> course_by_name;
	std::map<std::string, pRoom> room_by_name;

	void update_courses(const CourseVector& course_results);
};

#endif // !VIEW_ADAPTER_HPP
