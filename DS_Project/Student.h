#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include"sqlite/sqlite3.h"
#include"Course.h"
#include"Admin.h"

using namespace std;
class Student
{
private:
	int id;
	string f_name;
	string s_name;
	string th_name;
	string password;
	string acadamic_year;
	bool check_num_courses(int);
	bool check_taken_course_before(int, string);
	bool check_course_exist(string);
	bool check_max_num_studs(string, string);
	bool check_row_exist(string, string);
	bool check_row_exist_f(int, string);
	bool check_row_exist_p(int, string);
	bool check_course_name_exist(string);
public:
	static bool STUDENT_CHANGED;
	///////////////////////////////////////////////////////////////////////////
	Student();
	Student(int, string, string, string, string, string);
	///////////////////////////////////////////////////////////////////////////
	string get_student_id();
	string get_f_name();
	string get_s_name();
	string get_th_name();
	string get_student_password();
	string get_acadamic_year();
	/////////////////////////////////////////////////////////////////////////////
	void set_student_id(int);
	void set_f_name(string);
	void set_s_name(string);
	void set_th_name(string);
	void set_student_password(string);
	void set_acadamic_year(string);
	string View_CoursesDetails();
	///////////////////////////////////////////////////////////////////////////
	void edit_stud_data(int);
	void edit_f_and_p_course();
	/////////////////////////////////////////////////////////////////////////////
	void view_stud_courses(int);
	void view_prog_courses(int);
	void vies_finished_courses(int);
	///////////////////////////////////////////////////////////////////////////
	void Request_course(string,int);
	///////////////////////////////////////////////////////////////////////////
	void view_available_courses(int);
	void fill_available_crsVector(string s);
	void fill_pre_list();
	void get_remain_courses();
	void get_finished_courses(int id);

	~Student();
};
