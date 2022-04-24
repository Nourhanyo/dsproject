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
	int password;
	int acadamic_year;
public:
	Student* next;
	Student(string, string, string, int, int);

	string get_f_name();
	string get_s_name();
	string get_th_name();
	int get_student_password();
	int get_acadamic_year();
	int get_student_id();
	~Student();

};


