#include<iostream>
#include "Student.h"
#include "sqlite/sqlite3.h"
int Student::id = 0;/*for static variable (id)*/
Student::Student(string fnam, string snam, string thnam , int pass, int aca) {
	f_name = fnam;
	s_name = snam;
	th_name = thnam;
	password = pass;
	id++;
	next = NULL;

}



Student::Student()
{
	
	next1 = NULL;
	next2 = NULL;
}

string Student::get_f_name()
{
	return  f_name;
}
string Student::get_s_name()
{
	return s_name;
}
string Student::get_th_name()
{
	return th_name;
}
string Student::get_finished_coursese()
{
	return  finished_courses;
}
string Student::get_courses_in_progress()
{
	return   courses_in_progress; 
}
int Student::get_student_password()
{
	return  password;
}
int Student::get_acadamic_year()
{
	return  acadamic_year;
}
int Student::get_student_id()
{
	return   id;


}

Student ::~Student() {
}
