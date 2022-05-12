#include<iostream>
#include "sqlite/sqlite3.h"
#include<string>
#include <vector>
#include <algorithm>
#include"Student.h"
#include"DataBase.h"
using namespace std;
sqlite3* DB;
bool Student::STUDENT_CHANGED = false;
int Student::id = 0;/*for static variable (id)*/
Student::Student(int id, string fnam, string snam, string thnam, string pass, string aca) {
	this->id = id;
	f_name = fnam;
	s_name = snam;
	th_name = thnam;
	password = pass;
	id++;
}
Student::Student() {
}
///////////////////////////////////////////////////////////////////////////
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
string Student::get_student_password()
{
	return  password;
}
string Student::get_acadamic_year()
{
	return  acadamic_year;
}
string Student::get_student_id()
{
	return   to_string(id);
}
///////////////////////////////////////////////////////////////////////////
void Student::set_student_id(int idd)
{
	id = idd;
}
void Student::set_f_name(string f)
{
	f_name = f;
}
void Student::set_s_name(string s)
{
	s_name = s;
}
void Student::set_th_name(string th)
{
	th_name = th;
}
void Student::set_student_password(string pass)
{
	password = pass;
}
void Student::set_acadamic_year(string aca)
{
	acadamic_year = aca;
}
///////////////////////////////////////////////////////////////////////////
Student ::~Student() {}