#pragma once
#include <iostream>
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
	int password;
	int acadamic_year;
	
public:
	Student* next;
	Student* next1;
	Student();
	Student(string, string, string  , int, int);

	string get_f_name();
	string get_s_name();
	string get_th_name();
	string get_finished_coursese();
	string get_courses_in_progress();
	int get_student_password();
	int get_acadamic_year();
	int get_student_id();
	~Student();

};


