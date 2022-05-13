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
	static int id;
	string f_name;
	string s_name;
	string th_name;
	string password;
	string acadamic_year;
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
	///////////////////////////////////////////////////////////////////////////
	void view_stud_courses();
	void view_prog_courses(int);
	void vies_finished_courses(int);
	///////////////////////////////////////////////////////////////////////////
	void Request_course(int);
	bool check_num_courses(int);
	bool check_taken_course_before(int,string);
	bool check_course_exist(string);
	bool check_max_num_studs(string,string);
	~Student();
};
