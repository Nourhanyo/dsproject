#include "Course.h"
#include"sqlite/sqlite3.h"
Course::Course(string cod, string nam, int h, int max) {
	code = cod;
	name = nam;
	hours = h;
	max_numstud = max;
}
////////////////////////////////////////////

////////////////////////////////////////////
Course::~Course() {}
