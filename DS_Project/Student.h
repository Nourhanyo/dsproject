#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include"sqlite/sqlite3.h"
using namespace std;
class Student
{
private:
	static int id;
	string f_name;
	string s_name;
	string th_name;
	string finished_courses;
	string courses_in_progress;
	string password;
	string acadamic_year;
	vector<string> finishedCrs;
public:

	static int callbackup(void* data, int argc, char** argv, char** azColName);
	static int callback_req(void* data, int argc, char** argv, char** azColName);
	static int callback_ALL(void* data, int argc, char** argv, char** azColName);
	///////////////////////////////////////////////////////////////////////////
	Student* next;
	Student* next1;
	Student* next2;
	///////////////////////////////////////////////////////////////////////////
	Student();
	Student(int, string, string, string, string, string);
	///////////////////////////////////////////////////////////////////////////
	string get_f_name();
	string get_s_name();
	string get_th_name();
	string get_finished_coursese();
	string get_courses_in_progress();
	string get_student_password();
	string get_acadamic_year();
	string get_student_id();
	void set_student_id(int);
	void set_f_name(string);
	void set_s_name(string);
	void set_th_name(string);
	void set_student_password(string);
	void set_acadamic_year(string);
	///////////////////////////////////////////////////////////////////////////
	void Edit_Stud_data();
	void Drop_courses();
	void CourseDetails();
	void Request_Course(string);
	void VIEW_STUD_COURSES();
	void view_prog_courses(int);
	void view_finished_courses(int);
	void ViewAv_list();
	void GetRemainCrs();
	void GetAvailableCrs(int);
 	
	~Student();
};
