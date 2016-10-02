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
#include "GA.hpp"

struct CourseSchedule {
	string course_name;
	int day;
	int time;
	int duration;
	string room_name;
};

typedef std::mt19937 MyRNG;

class ViewAdapter {
public:
	ViewAdapter();

	void add_room(const string room_description);
	void add_course(const string course_description);

	bool move_course(const string course_name, const string room_name,
					 const int dest_day, const int dest_time);

	bool can_move_course(const string course_name, const string room_name,
		const int dest_day, const int dest_time);

	CourseSchedule get_course_result(const string course_name) const;
	vector<CourseSchedule> get_course_results() const;

	void randomize_schedule();

	void run_simulated_annealing();
	void run_genetic_algorithm();
	void run_hill_climbing();

	void build_solution(const string filename);

private:
	std::map<std::string, pCourse> course_by_name;
	std::map<std::string, pRoom> room_by_name;
	MyRNG generator;

	void update_courses(CourseVector course_results);
	CourseSchedule build_course_schedule(const pCourse& c) const;
	State build_state() const;
};

#ifdef EMSCRIPTEN
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(tubes_ai) {
	register_vector<CourseSchedule>("CourseScheduleVector");

	value_object<CourseSchedule>("CourseSchedule")
		.field("course_name", &CourseSchedule::course_name)
		.field("day", &CourseSchedule::day)
		.field("time", &CourseSchedule::time)
		.field("duration", &CourseSchedule::duration)
		.field("room_name", &CourseSchedule::room_name)
		;

	class_<ViewAdapter>("ViewAdapter")
		.constructor<>()
		.function("add_room", &ViewAdapter::add_room)
		.function("add_course", &ViewAdapter::add_course)
		.function("move_course", &ViewAdapter::move_course)
		.function("can_move_course", &ViewAdapter::can_move_course)
		.function("get_course_result", &ViewAdapter::get_course_result)
		.function("get_course_results", &ViewAdapter::get_course_results)
		.function("randomize_schedule", &ViewAdapter::randomize_schedule)
		.function("run_simulated_annealing", &ViewAdapter::run_simulated_annealing)
		.function("run_genetic_algorithm", &ViewAdapter::run_genetic_algorithm)
		.function("run_hill_climbing", &ViewAdapter::run_hill_climbing)
		;
}

#endif

#endif // !VIEW_ADAPTER_HPP
