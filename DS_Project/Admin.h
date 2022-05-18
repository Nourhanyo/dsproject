#pragma once
#include "Student.h"
#include<vector>
#include <iostream>
#include"Course.h"
using namespace std;
class Admin

{
private:
	int id;
	string fname;
	string lname;
	string password;
	void Delete();
	void Edit();
	bool check_course_code_exist(string);
	bool check_course_name_exist(string);
	bool check_cname_exist(string);
	bool check_ccode_exist(string);
	bool check_ccode2_exist(string, string);
	bool check_cname2_exist(string, string);
	bool check_num_hours(int hours);
	bool check_num_maxstud(int numstud);
	bool check_id_repeated(string);
	bool check_if_id_exist(string);
	bool check_row_repeated(int, string);
	bool check_row_repeated2(int, string);
	bool check_pre_exist(string, string);
	int check_num_courses_can_add(int);
public:
	static bool ADMIN_CHANGED;
	static bool PRE_LIST_CHANGED;
	Admin();
	Admin(int, string Fnam, string lName, string pass);
	string get_admin_id();
	string get_fname();
	string get_lname();
	string get_admin_pass();
	/////////////////////////////////////////////////////////////
	void set_admin_id(int);
	void set_fname(string);
	void set_lname(string);
	void set_admin_pass(string);
	///////////////////////////////////////////////////////
	void fill_prerequisite_list(string);
	~Admin();
	/////////////////////////////////////////////////////////////
	void add_stud();
	void add_f_course_in_p_course();
	/////////////////////////////////////////////////////////////
	string Addcourse();
	void ModifyCourses();
	/////////////////////////////////////////////////////////////
	void view_courses_of_stud();
	void view_stud_prog_courses(int);
	void view_stud_finished_courses(int);
	/////////////////////////////////////////////////////////////
	void view_studs_of_course();
	/////////////////////////////////////////////////////////////
};
