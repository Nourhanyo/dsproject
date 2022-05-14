#include<iostream>
#include "sqlite/sqlite3.h"
#include<string>
#include <vector>
#include <algorithm>
#include"Student.h"
#include"DataBase.h"
using namespace std;
vector<string> finishedCourses_forStud_vec;
vector<string> preList_forStud_vec;
vector<string> remainCrs_vec;
vector<string> AvailabeCrs_vec;
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
Student::Student() {}
///////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////
string Student::get_f_name(){
	return  f_name;
}
string Student::get_s_name(){
	return s_name;
}
string Student::get_th_name(){
	return th_name;
}
string Student::get_student_password(){
	return  password;
}
string Student::get_acadamic_year(){
	return  acadamic_year;
}
string Student::get_student_id(){
	return   to_string(id);
}
///////////////////////////////////////////////////////////////////////////
void Student::set_student_id(int idd){
	id = idd;
}
void Student::set_f_name(string f){
	f_name = f;
}
void Student::set_s_name(string s){
	s_name = s;
}
void Student::set_th_name(string th){
	th_name = th;
}
void Student::set_student_password(string pass){
	password = pass;
}
void Student::set_acadamic_year(string aca){
	acadamic_year = aca;
}
////////////////////////////////////////////////////////////////////////
void Student::View_CoursesDetails() {
	system("cls");
	cout << "  \n                                        .....Your Course Details..... \n\n";
	string code;
	cout << "Enter Course Code You Want to View....\n";
	cin >> code;
	cout << endl;
	if (check_course_exist(code)) {
		for (auto x : DataBase::courses_map) {
			if (code == x.first) {
				cout << "Course Name : " << x.second.get_Course_name() << endl << "Course Code : " << x.first << endl << "Course Hours : " << x.second.get_hours() << endl << "Cours Maximum Num Of Studend : " << x.second.get_max_numstud() << endl;
			}
		}
	}
	else {
		system("cls");
		cout << "  \n                                        .....Your Course Details..... \n\n";
		cout << "Enter valid Course.......!\n\n";
		system("pause 0");
		View_CoursesDetails();
	}
}
///////////////////////////////////////////////////////////////////////////
bool Student::check_course_exist(string code) {
	for (auto x : DataBase::courses_map) {
		if (code == x.first)
			return true;
	}
	return false;
}
///////////////////////////////////////////////////////////////////////////
void Student::view_stud_courses(){
	cout << endl << "Enter id: ";
	int id_;
	cin >> id_;
	view_prog_courses(id_);
	vies_finished_courses(id_);
}
/*****************************************/
void Student::view_prog_courses(int iid){
	cout << "Your Progress courses are :\n";
	int count = 0;
	for (auto x : DataBase::progress_vector) {
		if (iid == x.first) {
			count++;
			cout <<count<<"-" << x.second << endl;
		}
	}
}
/*************************************************/
void Student::vies_finished_courses(int iid){
	cout << "Your Finished courses are :\n";
	int count = 0;
	for (auto x : DataBase::finished_vector) {
		if (iid == x.first) {
			count++;
			cout << count << "-" << x.second << endl;
		}
	}
}
///////////////////////////////////////////////////////////////////////////
void Student::Request_course(int iid) {//Before it ->view available courses
	string code, course_name;
	bool flag = true;
	if (check_num_courses(iid)) {
		while (flag) {
			cout << "Enter Course Code That You Want To Take: ";
			cin >> code;

			if (check_course_exist(code)) {

				for (auto x : DataBase::courses_map) {
					if (code == x.first) {
						course_name = x.second.get_Course_name();
						break;
					}
				}
			}
			else {
				cout << "This Code is incorrect\n";
				system("pause");
				system("cls");
				continue;
			}
			if (check_max_num_studs(course_name, code)) {


				if (check_taken_course_before(iid, course_name)) {
					DataBase::progress_vector.push_back(make_pair(iid, course_name));
					cout << "You Take: " << course_name << " Course Successfully...\n";
					flag = false;
				}
				else {
					cout << "You Have Already Taken: " << course_name << endl;
					flag = false;
				}
			}
			else {
				cout << "\nSorry You Can't take " << course_name << " Course Because It has Max Number of Students...";
			}
		}
	}
	else {
		cout << "Sorry You Can't Take Any Course Because You Have 7 Courses";

	}


}
/***********************************************/
bool Student::check_num_courses(int iid){
	const int max_num_courses = 7;
	int count = 0;
	for (auto x : DataBase::progress_vector) {
		if (iid == x.first) {
			count++;
		}
	}
	if (count < max_num_courses) {
		return true;
	}
	else
		return false;
}
/************************************************/
bool Student::check_taken_course_before(int iid,string course_name){
	for (auto x : DataBase::progress_vector) {
		if (iid == x.first && course_name==x.second) {
			return false;
		}
	}
	return true;
}
/***************************************************************************/
bool Student::check_course_exist(string code){
	for (auto x : DataBase::courses_map) {
		if (code == x.first)
			return true;
	}
	return false;
}
/******************************************************/
bool Student::check_max_num_studs(string course_name,string code)
{
	int count = 0;
	for (auto x : DataBase::progress_vector) {
		if (x.second == course_name)
			count++;
	}
	if (DataBase::courses_map[code].get_max_numstud() == count) {
		return false;
	}
	return true;
}
///////////////////////////////////////////////////////////////////////////
void Student::view_available_courses()
{
	int id;
	cout << "enter your id\n";
	cin >> id;
	get_finished_courses(id);
	get_remain_courses();
	fill_pre_list();
	
	// Printing Avaliable Crs
	  cout << "\nAvaliableCrs\n*************\n";
	  for (size_t i = 0; i < AvailabeCrs_vec.size(); i++)
	  {
		  cout << AvailabeCrs_vec[i] << endl;
	  }
}
/////////////////////////////////////////////////////////////////////////
void Student::fill_available_crsVector(string remain){
  
	int flag2 = -1;
	  for (int j = 0; j < preList_forStud_vec.size(); j++) {
		   flag2 = 1;
		  for (int z = 0; z < finishedCourses_forStud_vec.size(); z++) {

			  if (preList_forStud_vec[j] == finishedCourses_forStud_vec[z])
			  {
				  flag2 = 0;
				  break;
			  }
		  }
	  }
	  if (flag2 == 0 || preList_forStud_vec.size()==0)
		  AvailabeCrs_vec.push_back(remain);
	
}
///////////////////////////////////////////////////////////////////////////
void Student::fill_pre_list() 
{
	for (int i = 0; i < remainCrs_vec.size(); i++) {
		string reamain_ok = remainCrs_vec[i];
		for (auto x : DataBase::prerequisite_vector) 
		{
			if (remainCrs_vec[i] == x.first) { preList_forStud_vec.push_back(x.second);}
		}
		// fill av_vector
		fill_available_crsVector(reamain_ok);
		// clear pre_vec
		preList_forStud_vec.clear();
	}
}
///////////////////////////////////////////////////////////////////////////
void Student::get_finished_courses(int iid)
{
	for (auto x : DataBase::finished_vector)
	{
		if (iid == x.first) { finishedCourses_forStud_vec.push_back(x.second); }
	}
	

}
///////////////////////////////////////////////////////////////////////////
void Student::get_remain_courses() {

	for (auto i: DataBase::courses_map) // all courses
	{
		int flag = 0;
		for (auto j: finishedCourses_forStud_vec) { // finished courses

			if (i.second.get_Course_name() == j)
				flag = 1;

		}
		if (flag == 0)
			remainCrs_vec.push_back(i.second.get_Course_name()); // difference between all & finished
	}
	

}
////////////////////////////////////////////////////////////////////////////
Student::~Student(){
}


