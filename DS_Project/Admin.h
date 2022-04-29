#pragma once
#include "Student.h"

#include <iostream>
using namespace std;

class Admin
{
private:
	static int id;
	
	string name;
	string password;
	int size = 0;
	int size1 = 0;
	int size2 = 0;

	Student* head = NULL;
	Student* tail = NULL;

	Student* head1 = NULL;
	Student* tail1 = NULL;
	Student* head2 = NULL;
	Student* tail2 = NULL;
public:
	Admin();
	
	void insert_At_Student(int ,string, string, string, int, int);
	void insert_At_finished_courses(int , string);
	void insert_At_in_progress_courses(int, string);
	void add(int , string, string  ,  string   , int, int);
	void add_finished_courses(int ,string);
	void add_in_progress_courses(int ,string); 
	void add_courses_only();
	void Add_Student();
	void loop_in_db_f_course();
	void loop_in_db_in_p_course();
	Admin(string , string);
	~Admin();

};


