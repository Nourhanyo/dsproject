#pragma once
#include <iostream>
using namespace std;

class Finished__course
{
private:
	int stud_id;
	string finished_course;
public:
	Finished__course();
	Finished__course(int , string );
	string get_finished_course();
	int  get_student_id_();
	void set_finished_course(string);
	void set_student_id_(int);


};

