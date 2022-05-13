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
	void View_CoursesDetails();
	bool check_course_exist(string code);

		 //////////////////////////////////////////////////////////////////////


	~Student();
};
