#include "Admin.h"
#include "Finished__course.h"
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
int Admin::id = 0; /*for static variable (id)*/
Admin::Admin(string Fnam, string lName, string pass) {
	id++;
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
bool Admin::check_if_id_exist(int  id )
{
	bool flag = false;


	for (auto x : DataBase::students_map) {
		if (to_string(id) == x.first) {

			flag = true;
		}


	}

	return flag;
}
bool Admin::check_row_repeated(int id ,string f_course )
{
	
	bool flag = true;


	for (auto x : DataBase::finished_vector) {
		if ( id == x.first && f_course == x.second) {

			flag = false;
		}


	}

	return flag;
}
void Admin::add_stud()
{
	int num_of_students;
	int press;
	int s_id; 
	string f_name1;
	string s_name1;
	string th_name1;
	string password1;
	string academic_year1;
	cout << "enter the number of stdent you want to add  " << endl;
    cin >> num_of_students;
	for (int i = 0; i < num_of_students; i++) {
		cout << "enter the id of student" << endl;
		cin >> s_id;
		cout << "enter student name " << endl;
		cin >> f_name1 >> s_name1 >> th_name1;
		cout << "enter student password " << endl;
		cin >> password1;
		cout << "enter student acadamic_year " << endl;
		cin >> academic_year1;
		Student student;
		student.set_student_id(s_id);
		student.set_f_name(f_name1);
		student.set_s_name(s_name1);
		student.set_th_name(th_name1);
		student.set_student_password(password1);
		student.set_acadamic_year(academic_year1);
		if(Admin::check_id_repeated(student.get_student_id())){
			DataBase::students_map.insert(make_pair(student.get_student_id(), student));
			student.STUDENT_CHANGED = true;
		}
		


	}






}

void Admin::add_f_course_in_p_course()
{
	
	int press;
	int id_;
	int clk;
	int stud_num;
	string f_courses;
	string in_p_courses;
	cout << "if you want to add finished courses for student press 1 " << endl;
	cout << "if you want to add in progress  courses for student press 2 " << endl;
	cout << "if you want to exit press 3 " << endl;
	cin >> press;
	switch (press) {

	case 1:
		cout << "enter the number of stdent you want to add  " << endl;
		cin >> stud_num;
		for (int i = 0; i < stud_num ; i++) {
			cout << "enter student id " << endl;
			cin >> id_;
			Finished__course stud_f_course;
			stud_f_course.set_student_id_(id_);
			if (Admin::check_if_id_exist(stud_f_course.get_student_id_())) {
				vector<Finished__course> finish_course;
				cout << "enter the number of finished courses you want add " << endl;
					cin >> clk;
					for (int j = 0; j < clk; j++) {
						
						cout << "enter finished course name" << endl;
						cin >> f_courses;
						stud_f_course.set_finished_course(f_courses);
						//st.push_back(stud.get_student_id(), stud.get_f_name(), stud.get_s_name(), stud.get_th_name(), stud.get_student_password(), stud.get_acadamic_year());
					}

					//if (Admin::check_row_repeated(stoi(stud.get_student_id()), stud.get_finished_course())) {
					//	DataBase::finished_vector.push_back(make_pair(stoi(stud.get_student_id()), stud.get_finished_course()));


				//	}

			}

			//else {


				//cout << "id does not exist " << endl;

			//}
		}
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
			cout << "  \n\n";
			cout << "Enter Course hours : \n";
			cin >> ho;
			course.set_hours(ho);
			cout << "  \n\n";
			DataBase::courses_map.insert(make_pair(course.get_code(), course));
			/////
			//insert prerequest courses after sohyp respond ?
			////
			cout << "Course Data inserted successfully \n";
			course.COURSE_CHANGED = true;
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
	auto it = DataBase::courses_map.find(codeee);
	oldcode = it->first;
	oldname = it->second.get_Course_name();
	oldhours = it->second.get_hours();
	oldmaxstud = it->second.get_max_numstud();
	if (check_course_exist(codeee)) {
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

				cout << "  \n";
				cout << "Enter New max_numstud : \n";
				cin >> maxx;
				course.set_max_numstud(maxx);

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
				cout << "This Code Is Duplicated...\n";
				system("pause 0");
				system("cls");
				Edit();///////// &&&&&&&&&&        change to     +++++    <<<<<<<<<<<<<<<<<<<<<<<<<
			}
		}
		else {
			cout << "This Name Is Duplicated...\n";
			system("pause 0");
			system("cls");
			Edit();///////// &&&&&&&&&&        change to     +++++    <<<<<<<<<<<<<<<<<<<<<<<<<
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
void Admin::Delete() {
	system("cls");
	Course course;
	string code;
	cout << "*********************************DELETE PAGE *************************************\n\n\n";
	cout << "Enter COURSE code YOU WANT to DELETE ? ....\n";
	cin >> code;
	if (check_course_exist(code)) {
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
bool Admin::check_course_exist(string code) {
	for (auto x : DataBase::courses_map) {
		if (code == x.first)
			return true;
	}
	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Admin::check_cname_exist(string name) {
	for (auto x : DataBase::courses_map) {
		if (name == x.second.get_Course_name())
			return false;
	}
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Admin::check_ccode_exist(string code) {
	for (auto x : DataBase::courses_map) {
		if (code == x.first)
			return false;
	}
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Admin::check_ccode2_exist(string code, string codeee) {
	for (auto x : DataBase::courses_map) {
		if (code == x.first && code != codeee)
			return false;
	}
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Admin::check_cname2_exist(string name, string nam) {
	for (auto x : DataBase::courses_map) {
		if (name == x.second.get_Course_name() && name != nam)
			return false;
	}
	return true;
}