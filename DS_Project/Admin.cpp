#include "Admin.h"
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <stack>
#include <string>
#include"sqlite/sqlite3.h"
#include"DataBase.h"
#include <string>
sqlite3* dd;
using namespace std;
bool Admin::ADMIN_CHANGED = false;
bool Admin::PRE_LIST_CHANGED = false;
Admin::Admin(int iid,string Fnam, string lName, string pass) {
	id = iid;
	get_fname() = Fnam;
	get_lname() = lName;
	password = pass;
}
Admin::Admin() {
}
Admin::~Admin() {}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string Admin::get_admin_id() {
	return to_string(id);
}
string Admin::get_fname() {
	return  fname;
}
string Admin::get_lname() {
	return lname;
}
string Admin::get_admin_pass() {
	return password;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Admin::set_admin_id(int idd) {
	id = idd;
}
void Admin::set_fname(string fnam) {
	fname = fnam;
}
void Admin::set_lname(string lnam) {
	lname = lnam;
}
void Admin::set_admin_pass(string pas) {
	password = pas;
}
//////////////////////////////////////////////////////////////////////////
void Admin::fill_prerequisite_list()
{
	vector<string> preList_vec;
	int numOfPre;
	string preName;
	string cName;

	cout << "Enter course Name :\n";
	cin >> cName;
	transform(cName.begin(), cName.end(), cName.begin(), ::tolower);// to change  string into lowercase

	cout << "Enter number of prerequist courses :\n";
	cin >> numOfPre;
	for (int i = 0; i < numOfPre; i++)
	{
		cout << "Enter Course number " << i + 1 << " : \n";
		cin >> preName;
		transform(preName.begin(), preName.end(), preName.begin(), ::tolower);  // to change  string into lowercase

		DataBase::prerequisite_vector.push_back(make_pair(cName, preName));
	}
	PRE_LIST_CHANGED = true;
}
//////////////////////////////////////////////////////////////////////////
bool Admin::check_id_repeated(string st_id)
{
	bool flag = true;
	for (auto x : DataBase::students_map) {
		if (st_id == x.first) {
			cout << " id already exist " << endl;
			flag = false;
		}
	}

	return flag;
}
/****************************************************/
bool Admin::check_if_id_exist(string  id)
{
	bool flag = false;

	for (auto x : DataBase::students_map) {
		if (id == x.first) {
			flag = true;
		}
	}

	return flag;
}
/***************************************************/
bool Admin::check_row_repeated(int id, string f_course)
{
	bool flag = true;

	for (auto x : DataBase::finished_vector) {
		if (id == x.first && f_course == x.second) {
			flag = false;
		}
	}

	return flag;
}
/****************************************************************/
bool Admin::check_row_repeated2(int id, string progress_course)
{
	bool flag = true;

	for (auto x : DataBase::progress_vector) {
		if (id == x.first && progress_course == x.second) {
			flag = false;
		}
	}

	return flag;
}
/************************************************************************/
void Admin::add_stud()
{
	Student student;
	int num_of_students;
	int s_id;
	string f_name1;
	string s_name1;
	string th_name1;
	string password1;
	string academic_year1;
	cout << "Enter the number of students you want to add  " << endl;
	cin >> num_of_students;
	for (int i = 0; i < num_of_students; i++) {
		cout << "\t\t\t\t" << i+1 <<endl;
		cout << "Enter student Full Name: " ;
		cin >> f_name1 >> s_name1 >> th_name1;
		cout << "\nEnter student password: " ;
		cin >> password1;
		cout << "\nEnter student acadamic_year: ";
		cin >> academic_year1;
		student.set_student_id(DataBase::students_map.size() + 1);
		student.set_f_name(f_name1);
		student.set_s_name(s_name1);
		student.set_th_name(th_name1);
		student.set_student_password(password1);
		student.set_acadamic_year(academic_year1);
		DataBase::students_map.insert(make_pair(student.get_student_id(), student));
		student.STUDENT_CHANGED = true;
		cout << "\n\n-----------------------------------------------------------------------------------------------\n\n";
	}
	cout << "\nDONE" << endl;
}
void Admin::add_f_course_in_p_course()
{
	bool flag = true;
	int press;
	int id_;
	int clk;
	int stud_num;
	string f_courses;
	string in_p_courses;
	Student stud, student;

	cout << "IF you want to add finished courses for student press 1 " << endl;
	cout << "IF you want to add in progress  courses for student press 2 " << endl;
	cout << "IF you want to exit press 3 " << endl;
	cin >> press;

	switch (press) {
	case 1:

		cout << "enter student id " << endl;
		cin >> id_;
		stud.set_student_id(id_);
		student = DataBase::students_map[to_string(id_)];
		if (Admin::check_if_id_exist(stud.get_student_id())) {
			cout << "This Student is " << student.get_f_name() << " " << student.get_s_name() << " " << student.get_th_name() << endl;
			cout << "Enter the number of finished courses you want add " << endl;
			cin >> clk;
			for (int j = 0; j < clk; j++) {
				cout << "Enter finished course name" << endl;
				cin >> f_courses;
				if (check_course_name_exist(f_courses)) {
					if (Admin::check_row_repeated(stoi(stud.get_student_id()), f_courses)) {
						DataBase::finished_vector.push_back(make_pair(stoi(stud.get_student_id()), f_courses));
					}
					else {
						cout << student.get_f_name() << " " << student.get_s_name() << " " << student.get_th_name() << " Has already Taken " << f_courses << endl;
					}
				}
				else {
					cout << "\nEnter a Correct Course Name\n";
				}
			}
		}
		else {
			cout << "ID does not exist " << endl;
		}

		break;
	case 2:

		cout << "Enter student ID " << endl;
		cin >> id_;
		stud.set_student_id(id_);
		student = DataBase::students_map[to_string(id_)];
		if (Admin::check_if_id_exist(stud.get_student_id())) {
			if (check_num_courses_can_add(id_) < 7) {
				int available_num_courses = (7 - check_num_courses_can_add(id_));
				cout << "This Student is " << student.get_f_name() << " " << student.get_s_name() << " " << student.get_th_name() << endl;
				if (available_num_courses != 7) {
					cout << student.get_f_name() << " " << student.get_s_name() << " " << student.get_th_name() << "Takes: " << endl;
					int c = 1;
					for (auto x : DataBase::progress_vector) {
						if (id_ == x.first)
							cout << c << "- " << x.second << "\n";
					}
				}
				cout << "\nYou can add to this student at most " << available_num_courses << " Courses\n";
				cout << "Enter the number of in progrss  courses you want add " << endl;
				cin >> clk;
				if (clk <= available_num_courses) {
					for (int j = 0; j < clk; j++) {
						cout << "Enter Course name" << endl;
						cin >> in_p_courses;
						if (check_course_name_exist(in_p_courses)) {
							if (Admin::check_row_repeated2(stoi(stud.get_student_id()), in_p_courses)) {
								DataBase::progress_vector.push_back(make_pair(stoi(stud.get_student_id()), in_p_courses));
							}
							else {
								cout << student.get_f_name() << " " << student.get_s_name() << " " << student.get_th_name() << " Is Taking " << f_courses << " Right Now" << endl;
								j--;
							}
						}
						else {
							cout << "\nEnter a Correct Course Name\n";
							continue;
						}
					}
				}
				else {
					cout << "You can add to" << student.get_f_name() << " " << student.get_s_name() << " " << student.get_th_name() << " at most " << available_num_courses << " Courses\n";
				}
			}

			else {
				cout << student.get_f_name() << " " << student.get_s_name() << " " << student.get_th_name() << " Has already  7 Courses" << endl;
			}
		}
		else {
			cout << "ID does not exist " << endl;
		}
		break;
	case 3:
		flag = false;
		break;
	}

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Admin::Addcourse() {
	system("cls");
	cout << "******************************Add Course Page******************************\n\n\n";
	Course course;
	string cod, nam;
	int maxstud, ho;
	cout << "Enter Course Code : \n";
	cin >> cod;
	course.set_code(cod);

	if (check_ccode_exist(course.get_code())) {
		cout << "  \n\n";
		cout << "Enter Course Name : \n";
		cin >> nam;
		course.set_Course_Name(nam);
		if (check_cname_exist(course.get_Course_name())) {
			cout << "  \n\n";
			cout << "Enter Max_numstud  : \n";
			cin >> maxstud;
			course.set_max_numstud(maxstud);
			if (check_num_maxstud(course.get_max_numstud())) {
				cout << "  \n\n";
				cout << "Enter Course hours : \n";
				cin >> ho;
				course.set_hours(ho);
				if (check_num_hours(course.get_hours())) {
					cout << "  \n\n";
					DataBase::courses_map.insert(make_pair(course.get_code(), course));
					/////
					//insert prerequest courses after sohyp respond ?
					////
					cout << "Course Data inserted successfully \n";
					course.COURSE_CHANGED = true;
				}
				else {
					cout << "the Number of hours Exceeds the limits (5)...\n";
					system("pause 0");
					system("cls");
					Addcourse();///////// &&&&&&&&&&        change to     +++++    <<<<<<<<<<<<<<<<<<<<<<<<<
				}
			}
			else {
				cout << "the Number of Student Exceeds the limits (10,000)...\n";
				system("pause 0");
				system("cls");
				Addcourse();///////////////////////////////change/>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

			}
		}

		else {
			cout << "This Name Is Duplicated...\n";
			system("pause 0");
			system("cls");
			Addcourse();///////// &&&&&&&&&&        change to     +++++    <<<<<<<<<<<<<<<<<<<<<<<<<

		}
	}
	else {
		cout << "This Code Is Duplicated...\n";
		system("pause 0");
		system("cls");
		Addcourse();/////////                   change to admin Menu+++++ <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Admin::ModifyCourses() {
	system("cls");
	cout << "***********************************Update_Page***********************************\n\n\n";
	cout << "1-Edite Course Data \n\n";
	cout << "2-Delete Course    \n\n";
	cout << "3-Go Back    \n\n";
	int choice;
	cout << "Enter your Choice\n";
	cin >> choice;
	switch (choice)
	{
	case 1:
		Edit();
		break;
	case 2:
		Delete();
		break;
	case 3:
		/*Menu m;
		m.adminmenu();*/
		break;
	default:
		system("cls");
		cout << "Enter valid number please ....\n\n";
		system("pause 0 ");
		ModifyCourses();
		break;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Admin::Edit() {
	system("cls");
	Course course;
	string nam = "";
	string cod = "";
	string oldname;
	string oldcode;
	int oldhours;
	int oldmaxstud;
	int hour;
	int maxx;
	int choice;
	string codeee;
	cout << "******************************Edite_PAGE************************************\n\n\n";
	cout << "Enter Course Code  you want to edite ?: \n";
	cin >> codeee;
	if (check_course_code_exist(codeee)) {
		auto it = DataBase::courses_map.find(codeee);
		oldcode = it->first;
		oldname = it->second.get_Course_name();
		oldhours = it->second.get_hours();
		oldmaxstud = it->second.get_max_numstud();
		cout << "  \n";
		cout << "Enter New Course Name : \n";
		cin >> nam;
		course.set_Course_Name(nam);
		if (check_cname2_exist(course.get_Course_name(), oldname)) {
			cout << "  \n";
			cout << "Enter New Course Code : \n";
			cin >> cod;
			course.set_code(cod);
			if (check_ccode2_exist(course.get_code(), codeee)) {
				cout << "  \n";
				cout << "Enter New Course hours : \n";
				cin >> hour;
				course.set_hours(hour);
				if (check_num_hours(course.get_hours())) {
					cout << "  \n";
					cout << "Enter New max_numstud : \n";
					cin >> maxx;
					course.set_max_numstud(maxx);
					if (check_num_maxstud(course.get_max_numstud())) {
						cout << "\n";
						DataBase::courses_map.erase(codeee);
						DataBase::courses_map.insert(make_pair(course.get_code(), course));
						course.COURSE_CHANGED = true;
						cout << "Course Updated succesfully \n\n";
						cout << "1-if you Wanna Undo your Old Course Data\n\n"
							<< "2-if you Wanna go back choose\n\n"
							<< "3-if you Wanna go Home choose\n\n"
							<< "if you Wanna Exit choose Else number\n\n";
						cout << "ENTER YOUR Choice ...\n";
						cin >> choice;
						switch (choice)
						{
						case 1:
							DataBase::courses_map.erase(course.get_code());
							course.set_Course_Name(oldname);
							course.set_code(oldcode);
							course.set_hours(oldhours);
							course.set_max_numstud(oldmaxstud);
							DataBase::courses_map.insert(make_pair(course.get_code(), course));
							system("cls");
							cout << endl;
							cout << "Old Course Data undo succesfully\n\n";
							cout << "press Enter to go back Modify Course Menu !\n\n";
							system("pause 0");
							ModifyCourses();
							break;
						case 2:
							ModifyCourses();
							break;
						case 3:
							/*
							* Admin Home()
							*/
							break;
						default:
							system("cls");
							cout << "                                                                      \n\n\n";
							cout << "                                  ______________________________________\n\n";
							cout << "                                  ************ See You Soon ************\n";
							cout << "                                  ______________________________________\n\n\n\n";
							break;
						}
					}
					else {
						cout << "the Number of Student Exceeds the limits (10,000)...\n";
						system("pause 0");
						system("cls");
						ModifyCourses();///////// &&&&&&&&&&        change to     +++++    <<<<<<<<<<<<<<<<<<<<<<<<<
					}
				}
				else {
					cout << "the Number of hours Exceeds the limits (5)...\n";
					system("pause 0");
					system("cls");
					ModifyCourses();///////// &&&&&&&&&&        change to     +++++    <<<<<<<<<<<<<<<<<<<<<<<<<
				}
			}
			else {
				cout << "This Code Is Duplicated...\n";
				system("pause 0");
				system("cls");
				ModifyCourses();///////// &&&&&&&&&&        change to     +++++    <<<<<<<<<<<<<<<<<<<<<<<<<

			}
		}
		else {
			cout << "This Name Is Duplicated...\n";
			system("pause 0");
			system("cls");
			ModifyCourses();///////// &&&&&&&&&&        change to     +++++    <<<<<<<<<<<<<<<<<<<<<<<<<
		}
	}
	else {
		cout << "This Code Not Found..!\n";
		system("pause 0");
		system("cls");
		ModifyCourses();
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Admin::Delete() {
	system("cls");
	Course course;
	string code;
	cout << "*********************************DELETE PAGE *************************************\n\n\n";
	cout << "Enter COURSE code YOU WANT to DELETE ? ....\n";
	cin >> code;
	if (check_course_code_exist(code)) {
		course.set_code(code);
		DataBase::courses_map.erase(course.get_code());
		course.COURSE_CHANGED = true;
		cout << "Course " << code << " Deleted succesfully\n\n";
		int choice;
		cout << endl << endl;
		cout << "if you Wanna go back choose (1) \n\n" << "if you Wanna exist choose (0)\n\n";
		cout << "ENTER YOUR Choice ...\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			ModifyCourses();
			break;
		default:
			cout << "..........................................................\n";
			cout << ".......................See You Soon....................... \n";
			cout << "..........................................................\n\n";
			break;
		}
	}
	else {
		cout << "This Code Is Incorrect..\n";
		system("pause 0");
		system("cls");
		ModifyCourses();
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Admin::check_course_code_exist(string code) {
	for (auto x : DataBase::courses_map) {
		if (code == x.first)
			return true;
	}
	return false;
}
/***********************************************************/
bool Admin::check_course_name_exist(string name) {
	for (auto x : DataBase::courses_map) {
		if (name == x.second.get_Course_name())
			return true;
		
	}
	return false;
}
/**********************************************************/
bool Admin::check_cname_exist(string name) {
	for (auto x : DataBase::courses_map) {
		if (name == x.second.get_Course_name())
			return false;
	}
	return true;
}
/********************************************************/
bool Admin::check_ccode_exist(string code) {
	for (auto x : DataBase::courses_map) {
		if (code == x.first)
			return false;
	}
	return true;
}
/*********************************************************/
bool Admin::check_ccode2_exist(string code, string codeee) {
	for (auto x : DataBase::courses_map) {
		if (code == x.first && code != codeee)
			return false;
	}
	return true;
}
/*******************************************************************/
bool Admin::check_cname2_exist(string name, string nam) {
	for (auto x : DataBase::courses_map) {
		if (name == x.second.get_Course_name() && name != nam)
			return false;
	}
	return true;
}
/*******************************************************************/
void Admin::view_courses_of_stud() {
	int stud_id;
	cout << "Enter the ID for Student \n";
	cin >> stud_id;
	if (DataBase::students_map.size() >= stud_id) {
		view_stud_prog_courses(stud_id);
		view_stud_finished_courses(stud_id);
	}
	else {
		cout << "This ID Has NO Student...\n";
	}
}
/****************************************/
void Admin::view_stud_prog_courses(int id_) {
	vector<string>prog_course;
	Student student = DataBase::students_map[to_string(id_)];
	for (auto x : DataBase::progress_vector) {
		if (id_ == x.first) {
			prog_course.push_back(x.second);
		}
	}
	if (prog_course.size() != 0) {
		cout << "The Courses in Progress for " << student.get_f_name() << " " << student.get_s_name() << " " << student.get_th_name() << " are:\n";
		int count = 1;
		for (auto x : prog_course) {
			cout << count << "- " << x << endl;
			count++;
		}
	}
	else
		cout << student.get_f_name() << " " << student.get_s_name() << " " << student.get_th_name() << " Has NO Progress Courses\n";
}
/****************************************************/
void Admin::view_stud_finished_courses(int id_) {
	vector<string>finish_course;
	Student student = DataBase::students_map[to_string(id_)];
	for (auto x : DataBase::finished_vector) {
		if (id_ == x.first) {
			finish_course.push_back(x.second);
		}
	}
	if (finish_course.size() != 0) {
		cout << "The Courses in Progress for " << student.get_f_name() << " " << student.get_s_name() << " " << student.get_th_name() << " are:\n";
		int count = 1;
		for (auto x : finish_course) {
			cout << count << "- " << x << endl;
			count++;
		}
	}
	else
		cout << student.get_f_name() << " " << student.get_s_name() << " " << student.get_th_name() << " Has NO Finished Courses\n";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Admin::view_studs_of_course() {
	string course_name;
	vector <int>id_prog;
	vector <int>id_finish;
	cout << "Enter the course name\n";
	cin >> course_name;
	if (check_course_name_exist(course_name)) {
		for (auto x : DataBase::progress_vector) {
			if (course_name == x.second)
			{
				id_prog.push_back(x.first);
			}
		}
		for (auto x : DataBase::finished_vector) {
			if (course_name == x.second)
			{
				id_finish.push_back(x.first);
			}
		}
		if (id_prog.size() != 0) {
			cout << "Students Who Are Taking " << course_name << " Right Now:\n\n";
			cout << "ID             Full Nmae\n";
			cout << "-------------------------------\n";
			for (int i = 0; i < id_prog.size(); i++)
			{
				Student student = DataBase::students_map[to_string(id_prog[i])];
				cout << student.get_student_id() << "    -->   " << student.get_f_name() << " " << student.get_s_name() << " " << student.get_th_name() << endl;
			}
		}
		else
			cout << "No One Is Taking " << course_name << " Right Now\n\n";
		/********************************************************************************/
		cout << "\n-----------------------------------------------------------------------------------\n";
		if (id_finish.size() != 0) {
			cout << "\nStudents Who Finished " << course_name << " Before:\n\n";
			cout << "ID             Full Nmae\n";
			cout << "-------------------------------\n";
			for (int i = 0; i < id_finish.size(); i++)
			{
				Student student = DataBase::students_map[to_string(id_prog[i])];
				cout << student.get_student_id() << "    -->   " << student.get_f_name() << " " << student.get_s_name() << " " << student.get_th_name() << endl;
			}
		}
		else
			cout << "No One Finished " << course_name << " Before\n\n";
	}
	else
		cout << "\nEnter a Correct Course Name\n";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Admin::check_num_courses_can_add(int iid){
	int count = 0;
	for (auto x : DataBase::progress_vector) {
		if (iid == x.first) {
			count++;
		}
	}
	return count;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Admin::check_num_hours(int hours) {
	Course course;
	const int max_hours = 5;
	if (hours <= max_hours) {

		return true;
	}
	else {
		return false;
	}
}
///////////////////////////////////////////////////////////////////////////
bool Admin::check_num_maxstud(int numstud) {
	Course course;
	const int maxnum_of_stud = 100000;
	if (numstud <= maxnum_of_stud) {

		return true;
	}
	else {
		return false;
	}
}
