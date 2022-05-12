#include <iostream>
#include"sqlite/sqlite3.h"
#include<string>
#include"Admin.h"
#include "Student.h"
#include"Course.h"
#include "Menu.h"
#include "DataBase.h"

using namespace std;

using namespace std;
int main() {
	DataBase a;
	a.load_DB();
	/*
		I have changed names of maps ....check it in DataBsse.h // they became static ->goto  DataBase.cpp to see how..
		*****************************************************************************************************************
		To use any vector or map in any class we should write DataBase::(name of vec or map) .. DataBase::courses_map
		like // DataBase::progress_vector.pushback(make_pair(#,#)) \\..// DataBase::students_map[#]=# \\...
									**go to line  657 in Admin.cpp to see example**
										*##don't make object of DataBase...##*
										* ------------------------------------*
		**important**
		if anyone makes changes on any map of student,admin and course, should make the flag of this map to TRUE
											--------------------------------
		                                              **important**
											 $work in pranch not in master$
	*/
	Admin ad;
	ad.test();
	a.update_DB();
	return 0;
}