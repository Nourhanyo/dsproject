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
Student::Student(int idd, string fnam, string snam, string thnam, string pass, string aca) {
	id = idd;
	f_name = fnam;
	s_name = snam;
	th_name = thnam;
	password = pass;
}
Student::Student() {}
///////////////////////////////////////////////////////////////////////////
string Student::get_f_name() {
	return  f_name;
}
string Student::get_s_name() {
	return s_name;
}
string Student::get_th_name() {
	return th_name;
}
string Student::get_student_password() {
	return  password;
}
string Student::get_acadamic_year() {
	return  acadamic_year;
}
void Student::edit_stud_data()
{
	Student stud2;
	int id;
	int p;
	string password1;
	string new_password;
	int clk1;
	string f_name1;
	string s_name1;
	string th_name1;
	string academic_year1;
	cout << "enter the password of student you want to edit " << endl;
	cin >> password1;
	cout << "enter the id of student you want to edit " << endl;
	cin >> id;
	stud2.set_student_id(id);
	if (Student::check_row_exist(stud2.get_student_id(), password1)) {
		cout << "if you want to editt password   for student press 1 " << endl;
		cout << "if you want to exit  press 2 " << endl;
		cin >> p;
		auto b = DataBase::students_map.find(stud2.get_student_id());

		f_name1 = b->second.get_f_name();
		s_name1 = b->second.get_s_name();
		th_name1 = b->second.get_th_name();
		academic_year1 = b->second.get_acadamic_year();
		stud2.set_f_name(f_name1);
		stud2.set_s_name(s_name1);
		stud2.set_th_name(th_name1);
		stud2.set_acadamic_year(academic_year1);		
		switch (p) {
		case 1:
			cout << "enter the new password you want  " << endl;
			cin >> new_password;
			stud2.set_student_password(new_password);
			cout << "if you want to submit click 1 else click any number " << endl;
			cin >> clk1;
			if (clk1 == 1) {
				
				DataBase::students_map.erase(stud2.get_student_id());
				DataBase::students_map.insert(make_pair(stud2.get_student_id(), stud2));
				stud2.STUDENT_CHANGED = true;
			}
			else {

				cout << "index does not be  modified " << endl;



			}
		case 2:
			break;
		
		
	default:
			break;
		}
	}
	else {

		cout << "student  does not  exist " << endl;


	}
}
void Student::edit_f_and_p_course()
{
	Student stud1;
	int id;
	int p;
	string password;
	int num_of_finished_c;
	int num_of_in_p;
	string f_course_name;
	string in_p_name;
	string new_f_course; 
	string new_p_course;

	int clk;
	cout << "enter the password of student you want to edit " << endl;
	cin >> password;
	stud1.set_student_password(password);
	cout << "enter the id of student you want to edit " << endl;
	cin >> id;
	stud1.set_student_id(id);
	if (Student::check_row_exist(stud1.get_student_id(), stud1.get_student_password())) {
		cout << "if you want to edit finished courses for student press 1 " << endl;
		cout << "if you want to edit in progress  courses for student press 2 " << endl;
		cout << "if you want to exit t press 3 " << endl;

		cin >> p;
		switch (p) {
		case 1:
			cout << "enter the number of  finished courses you want to edit " << endl;
			cin >> num_of_finished_c;
			if (num_of_finished_c <= DataBase::finished_vector.capacity()) {
				for (int i = 0; i < num_of_finished_c; i++) {
					cout << "enter the name of finished course you want to edit " << endl;
					cin >> f_course_name;
					if (Student::check_row_exist_f(id, f_course_name)) {
						cout << "enter the name of finished course you want  " << endl;
						cin >> new_f_course;
						cout << "if you want to submit click 1 else click any number " << endl;
						cin >> clk;
						if (clk == 1) {
							int index = 0;
							for (auto x : DataBase::finished_vector) {
								if (x.first == id && x.second == f_course_name)
								{

									break;


								}

								index++;


							}
							cout << index;
							DataBase::finished_vector[index].first = id;
							DataBase::finished_vector[index].second = new_f_course;


						}
						else {

							cout << "index does not be  modified " << endl;



						}
					}
					else {

						cout << "course does not  exist " << endl;


					}
				}
			}
			else {


				cout << "index out of range " << endl;
			}
			break;
		case 2:
			cout << "enter the number of  in progress courses you want to edit " << endl;
			cin >> num_of_in_p;
			if (num_of_in_p <= DataBase::progress_vector.capacity()) {
				for (int i = 0; i < num_of_in_p; i++) {
					cout << "enter the name of  in progress course you want to edit " << endl;
					cin >> in_p_name;
					if (Student::check_row_exist_p(id, in_p_name)) {
						cout << "enter the name of  in progress course you want  " << endl;
						cin >> new_p_course;
						cout << "if you want to submit click 1 else click any number " << endl;
						cin >> clk;
						if (clk == 1) {
							int index = 0;
							for (auto x : DataBase::progress_vector) {
								if (x.first == id && x.second == in_p_name)
								{

									break;


								}

								index++;


							}
							cout << index;
							DataBase::progress_vector[index].first = id;
							DataBase::progress_vector[index].second = new_p_course;


						}
						else {

							cout << "index does not be  modified " << endl;



						}
					}
					else {

						cout << "course does not  exist " << endl;


					}
				}
			}
			else {


				cout << "index out of range " << endl;
			}
			break;
		case 3:
			break;
		default:
			break;
		}

		
	}
}
bool Student::check_row_exist(string id, string password)
{
	bool flag = false;


	for (auto x : DataBase::students_map) {
		if (id == x.first && password == x.second.get_student_password()) {

			flag = true;
		}


	}

	return flag;
}
bool Student::check_row_exist_f( int id , string f_course  )
{
	bool flag = false;


	for (auto x : DataBase::finished_vector) {
		if (id == x.first && f_course == x.second) {

			flag = true;
		}


	}

	return flag;
}
bool Student::check_row_exist_p(int id , string in_p_course  )
{
	bool flag = false;


	for (auto x : DataBase::progress_vector) {
		if (id == x.first && in_p_course == x.second) {

			flag = true;
		}


	}

	return flag;
}




string Student::get_student_id() {
	return   to_string(id);
}

///////////////////////////////////////////////////////////////////////////
void Student::set_student_id(int idd) {
	id = idd;
}
void Student::set_f_name(string f) {
	f_name = f;
}
void Student::set_s_name(string s) {
	s_name = s;
}
void Student::set_th_name(string th) {
	th_name = th;
}
void Student::set_student_password(string pass) {
	password = pass;
}
void Student::set_acadamic_year(string aca) {
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
void Student::view_stud_courses() {
	cout << endl << "Enter id: ";//take from login
	int id_;
	cin >> id_;
	view_prog_courses(id_);
	vies_finished_courses(id_);
}
/*****************************************/
void Student::view_prog_courses(int iid) {
	vector<string>prog_course;
	for (auto x : DataBase::progress_vector) {
		if (iid == x.first) {
			prog_course.push_back(x.second);
		}
	}
	if (prog_course.size() != 0) {
		cout << "Your Courses in Progress are: \n";
		int count = 1;
		for (auto x : prog_course) {
			cout << count << "- " << x << endl;
			count++;
		}
	}
	else
		cout << " You Has NO Progress Courses\n";
}
/*************************************************/
void Student::vies_finished_courses(int iid) {
	vector<string>finish_course;
	for (auto x : DataBase::progress_vector) {
		if (iid == x.first) {
			finish_course.push_back(x.second);
		}
	}
	if (finish_course.size() != 0) {
		cout << "Your Finished Courses are: \n";
		int count = 1;
		for (auto x : finish_course) {
			cout << count << "- " << x << endl;
			count++;
		}
	}
	else
		cout << " You Has NO Finished Courses\n";
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
bool Student::check_num_courses(int iid) {
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
bool Student::check_taken_course_before(int iid, string course_name) {
	for (auto x : DataBase::progress_vector) {
		if (iid == x.first && course_name == x.second) {
			return false;
		}
	}
	return true;
}
/***************************************************************************/
bool Student::check_course_exist(string code) {
	for (auto x : DataBase::courses_map) {
		if (code == x.first)
			return true;
	}
	return false;
}
/******************************************************/
bool Student::check_max_num_studs(string course_name, string code)
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
	cout << "Enter Your Id :\n";
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
void Student::fill_available_crsVector(string remain) {
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
	if (flag2 == 0 || preList_forStud_vec.size() == 0)
		AvailabeCrs_vec.push_back(remain);
}
///////////////////////////////////////////////////////////////////////////
void Student::fill_pre_list()
{
	for (int i = 0; i < remainCrs_vec.size(); i++) {
		string reamain_ok = remainCrs_vec[i];
		for (auto x : DataBase::prerequisite_vector)
		{
			if (remainCrs_vec[i] == x.first) { preList_forStud_vec.push_back(x.second); }
		}
		// fill av_vector
		fill_available_crsVector(reamain_ok);
		// clear pre_vec
		preList_forStud_vec.clear();
	}
}
///////////////////////////////////////////////////////////////////////////
void Student::get_finished_courses(int iid) {
	for (auto x : DataBase::finished_vector)
	{
		if (iid == x.first) { finishedCourses_forStud_vec.push_back(x.second); }
	}
}
///////////////////////////////////////////////////////////////////////////
void Student::get_remain_courses() {
	for (auto i : DataBase::courses_map) // all courses
	{
		int flag = 0;
		for (auto j : finishedCourses_forStud_vec) { // finished courses
			if (i.second.get_Course_name() == j)
				flag = 1;
		}
		if (flag == 0)
			remainCrs_vec.push_back(i.second.get_Course_name()); // difference between all & finished
	}
}
////////////////////////////////////////////////////////////////////////////
Student::~Student() {
}