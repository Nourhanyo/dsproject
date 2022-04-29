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
	static int callback(void* data, int argc, char** argv, char** azColName);
	static int callback1(void* data, int argc, char** argv, char** azColName);

	Student* next;
	Student* next1;
	Student* next2;

	Student();
	Student(int ,string, string, string  , int, int);

	string get_f_name();
	string get_s_name();
	string get_th_name();
	string get_finished_coursese();
	string get_courses_in_progress();
	string get_student_password();
	string get_acadamic_year();
	string get_student_id();
	void Edit_Stud_data();
	
	//static int select_data();
	//static int callback(void* NotUsed, int argc, char** argv, char** azColName);
	~Student();

};


