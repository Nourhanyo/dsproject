#include "Course.h"
#include"sqlite/sqlite3.h"
#include<vector>
#include <algorithm>
Course::Course(string cod, string nam, int h, int max) {
	code = cod;
	name = nam;
	hours = h;
	max_numstud = max;
}

int Course::get_max_numstud() {
	return max_numstud;
}
void Course::set_max_numstud(int maxx) {
	max_numstud = maxx;
}
//////////////////////////////////////////////////////
int Course::get_hours() {
	return hours;
}
void Course::set_hours(int hour) {
	hours = hour;
}
//////////////////////////////////////////////////////
string Course::get_Course_name() {
	return name;
}
void Course::set_Course_Name(string nam) {
	name = nam;
}
//////////////////////////////////////////////////////
string Course::get_code() {
	return code;
}
void Course::set_code(string cod) {
	code = cod;
}
////////////////////////////////////////////
Course::Course() {
	hours = 0;
	name = "";
	code = "";
	max_numstud = 0;
}
////////////////////////////////////////////
Course::~Course() {}