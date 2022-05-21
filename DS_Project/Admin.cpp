#include "Admin.h"
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <stack>
#include <string>
#include"sqlite/sqlite3.h"
#include"DataBase.h"
#include <string>
#include "Menu.h"
sqlite3* dd;
using namespace std;
//FLAGS TO UBDATE DATA OF STUDENT AND PROGRESSED COURSES IN DB
bool Admin::ADMIN_CHANGED = false;
bool Admin::PRE_LIST_CHANGED = false;
//STACK FOR UNDO EDIT AND DELETE
stack<Course>undo;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
Admin::Admin(int iid, string Fnam, string lName, string pass) {
	id = iid;
	get_fname() = Fnam;
	get_lname() = lName;
	password = pass;
}
Admin::Admin() {
}
Admin::~Admin() {}
/*******************************************************************************************************************/
//GETTER FOR ADMIN DATA.....
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
//SETTER FOR ADMIN DATA.....
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
/*******************************************************************************************************************/
//THIS FUNCTION FILL PREREQUISITE COURSES
void Admin::fill_prerequisite_list(string cName)
{
	vector<string> preList_vec;
	int numOfPre;
	string preName;
	const int size = 4;
	transform(cName.begin(), cName.end(), cName.begin(), ::tolower);// to change  string into lowercase
	if (check_course_name_exist(cName)) {
		//CHECK IF THIS COURSE ALREADY EXIST
		cout << "Enter number of prerequisite courses :\n";
		cin >> numOfPre;
		if (numOfPre <= size) {
			for (int i = 0; i < numOfPre; i++)
			{
				cout << "Enter Course number " << i + 1 << " : \n";
				cin >> preName;
				transform(preName.begin(), preName.end(), preName.begin(), ::tolower);  // to change  string into lowercase
				if (check_course_name_exist(preName)) {
					//CHECK IF THIS COURSE ALREADY EXIST
					if (check_pre_exist(cName, preName)) {
						DataBase::prerequisite_vector.push_back(make_pair(cName, preName));
						PRE_LIST_CHANGED = true;
					}
					else {
						cout << "This course's prerequisite is already exist \n";
						i--;
					}
				}
				else {
					cout << "Invalid course name\n";
					i--;
				}
			}
		}
		else {
			cout << "The Number of  Prerequisite Courses Exceeds the limits (4)...\n";
			system("pause");
			system("cls");
		}
	}
	else {
		cout << "Invalid course name\n";
		system("pause");
		system("cls");
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Admin::add_stud()
{
	int num_of_students;
	string f_name1, s_name1, th_name1, password1, academic_year1;
	cout << "Enter the number of students you want to add  " << endl;
	cin >> num_of_students;
	for (int i = 0; i < num_of_students; i++) {
		cout << "Enter student number: " << i + 1 << endl;
		cout << "Enter student Full Name: ";
		cin >> f_name1 >> s_name1 >> th_name1;
		transform(f_name1.begin(), f_name1.end(), f_name1.begin(), ::tolower);// to change  string into lowercase
		transform(s_name1.begin(), s_name1.end(), s_name1.begin(), ::tolower);
		transform(th_name1.begin(), th_name1.end(), th_name1.begin(), ::tolower);
		cout << "\nEnter student password: ";
		cin >> password1;
		transform(password1.begin(), password1.end(), password1.begin(), ::tolower);
		cout << "\nEnter student acadamic_year: ";
		cin >> academic_year1;
		if (stoi(academic_year1) > 4) {
			cout << "Academic year is out of range....(1...4)\n";
			cout << "\nEnter student acadamic_year again: ";
			cin >> academic_year1;
		}
		Student student(DataBase::students_map.size() + 1, f_name1, s_name1, th_name1, password1, academic_year1);
		DataBase::students_map.insert(make_pair(to_string(DataBase::students_map.size() + 1), student));
		student.STUDENT_CHANGED = true;
		cout << "\n\n-----------------------------------------------------------------------------------------------\n\n";
	}
	cout << "\nDONE" << endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
		if (Admin::check_if_id_exist(stud.get_student_id())) {
			student = DataBase::students_map[to_string(id_)];
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
		system("cls");
		cout << "Enter student ID " << endl;
		cin >> id_;
		stud.set_student_id(id_);
		if (Admin::check_if_id_exist(stud.get_student_id())) {
			student = DataBase::students_map[to_string(id_)];
			if (check_num_courses_can_add(id_) < 7) {
				int available_num_courses = (7 - check_num_courses_can_add(id_));
				if (available_num_courses != 7) {
					cout << "stuent name: " << student.get_f_name() << " " << student.get_s_name() << " " << student.get_th_name() << " Takes: " << endl;
					int c = 1;
					for (auto x : DataBase::progress_vector) {
						if (id_ == x.first) {
							cout << c << "- " << x.second << "\n";
							c++;
						}
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
					cout << "You can add to " << student.get_f_name() << " " << student.get_s_name() << " " << student.get_th_name() << " at most " << available_num_courses << " Courses\n";
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
string Admin::Addcourse() {
	system("cls");
	cout << "******************************Add Course Page******************************\n\n\n";
	string cod, nam;
	int maxstud, ho;
	cout << "Enter Course Code : \n";
	cin >> cod;
	transform(cod.begin(), cod.end(), cod.begin(), ::tolower);
	/*
		WE NEED TO ADD COURSE SO WE WANT THAT CODE AND NAME UNIQUE..
		FUNCTIONS CHECK RETURN TRUE IF THAT CODE OR NAME IS EXIST So WE WANT THE OPPOSITE OF THIS PROCESS
	*/
	if (!check_course_code_exist(cod)) {
		cout << "  \n";
		cout << "Enter Course Name : \n";
		cin >> nam;
		transform(nam.begin(), nam.end(), nam.begin(), ::tolower);
		if (!check_course_name_exist(nam)) {
			cout << "  \n";
			cout << "Enter Max_numstud  : \n";
			cin >> maxstud;
			if (check_num_maxstud(maxstud)) {
				cout << "  \n";
				cout << "Enter Course hours : \n";
				cin >> ho;
				if (check_num_hours(ho)) {
					cout << "  \n";
					Course course(cod, nam, ho, maxstud);
					DataBase::courses_map.insert(make_pair(cod, course));
					cout << "Course Data inserted successfully \n";
					course.COURSE_CHANGED = true;
					return nam;
				}
				else {
					cout << "the Number of hours Exceeds the limits (5)...\n";
					system("pause 0");
					system("cls");
					Addcourse();
				}
			}
			else {
				cout << "the Number of Student Exceeds the limits (2000)...\n";
				system("pause 0");
				system("cls");
				Addcourse();
			}
		}
		else {
			cout << "This Name Is Duplicated...\n";
			system("pause 0");
			system("cls");
			Addcourse();
		}
	}
	else {
		cout << "This Code Is Duplicated...\n";
		system("pause 0");
		system("cls");
		Addcourse();
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
		Menu m;
		m.adminmenu();
		break;
	default:
		system("cls");
		cout << "Enter valid number please ....\n\n";
		system("pause 0 ");
		ModifyCourses();
		break;
	}
}
void Admin::Edit() {
	system("cls");
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
		Course course1 = DataBase::courses_map[(codeee)];
		undo.push(course1);
		cout << "  \n";
		cout << "Enter New Course Name : \n";
		cin >> nam;
		if (check_cname2_exist(nam, oldname)) {
			cout << "  \n";
			cout << "Enter New Course Code : \n";
			cin >> cod;
			if (check_ccode2_exist(cod, codeee)) {
				cout << "  \n";
				cout << "Enter New Course hours : \n";
				cin >> hour;
				if (check_num_hours(hour)) {
					cout << "  \n";
					cout << "Enter New max_numstud : \n";
					cin >> maxx;
					if (check_num_maxstud(maxx)) {
						cout << "\n";
						DataBase::courses_map.erase(codeee);
						Course course(cod, nam, hour, maxx);
						undo.push(course);
						DataBase::courses_map.insert(make_pair(cod, course));
						course.COURSE_CHANGED = true;
						cout << "Course Updated succesfully \n\n";
						/**********************************************************/
						cout << "1-if you Wanna Undo your Old Course Data\n\n"
							<< "2-if you Wanna go back choose\n\n"
							<< "3-if you Wanna go Home choose\n\n"
							<< "if you Wanna Exit choose Else number\n\n";
						cout << "ENTER YOUR Choice ...\n";
						cin >> choice;
						switch (choice)
						{
						case 1:
							DataBase::courses_map.erase(undo.top().get_code());
							undo.pop();
							DataBase::courses_map.insert(make_pair(undo.top().get_code(), undo.top()));
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
							Menu m;
							m.adminmenu();
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
						ModifyCourses();
					}
				}
				else {
					cout << "the Number of hours Exceeds the limits (5)...\n";
					system("pause 0");
					system("cls");
					ModifyCourses();
				}
			}
			else {
				cout << "This Code Is Duplicated...\n";
				system("pause 0");
				system("cls");
				ModifyCourses();
			}
		}
		else {
			cout << "This Name Is Duplicated...\n";
			system("pause 0");
			system("cls");
			ModifyCourses();
		}
	}
	else {
		cout << "This Code Not Found..!\n";
		system("pause 0");
		system("cls");
		ModifyCourses();
	}
}
void Admin::Delete() {
	system("cls");
	Course course;
	string code;
	cout << "*********************************DELETE PAGE *************************************\n\n\n";
	cout << "Enter COURSE code YOU WANT to DELETE ? ....\n";
	cin >> code;
	if (check_course_code_exist(code)) {
		Course course1 = DataBase::courses_map[(code)];
		undo.push(course1);

		DataBase::courses_map.erase(course1.get_code());
		course.COURSE_CHANGED = true;
		cout << "Course " << code << " Deleted succesfully\n\n";
		int choice;
		cout << endl << endl;
		cout << "1-if you Wanna Undo your Old Course Data\n\n"
			<< "2-if you Wanna go back choose\n\n"
			<< "3-if you Wanna go Home choose\n\n"
			<< "if you Wanna Exit choose Else number\n\n";
		cout << "ENTER YOUR Choice ...\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			DataBase::courses_map.insert(make_pair(undo.top().get_code(), undo.top()));
			cout << "Old Course Data undo succesfully\n\n";
			undo.pop();
			break;
		case 2:
			ModifyCourses();
			break;
		case 3:
			Menu m;
			m.adminmenu();
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
/*THERE FUNCTIONS VIEW ALL COURSES OF STUDENT*/
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
void Admin::view_stud_finished_courses(int id_) {
	vector<string>finish_course;
	Student student = DataBase::students_map[to_string(id_)];
	for (auto x : DataBase::finished_vector) {
		if (id_ == x.first) {
			finish_course.push_back(x.second);
		}
	}
	if (finish_course.size() != 0) {
		cout << "The Finished Courses for " << student.get_f_name() << " " << student.get_s_name() << " " << student.get_th_name() << " are:\n";
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
/*THIS FUNCTION VIEW LIST OF STUDENTS IN SPECIFIC COURSE (PROGRESS & FINISHED)*/
void Admin::view_studs_of_course() {
	string course_name;
	vector <int>id_prog;
	vector <int>id_finish;
	cout << "Enter the course name\n";
	cin >> course_name;
	transform(course_name.begin(), course_name.end(), course_name.begin(), ::tolower);
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
		/*HERE WE MADE TWO VECTORS TO BUSH ID OF STUDENTS IN THEM
		 IF THE SIZE OF VECTOR IS MORE THAN 0,WE WILL PRINT LIST OF STUDENTS WHO TAKING OR FINISHED THIS COURSE
		 IF THE SIZE OF VECTOR EQUALS TO 0 ,IT MEANS THAT NO ONE TAKES OR FINISHED THIS COURSE*/
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
				Student student = DataBase::students_map[to_string(id_finish[i])];
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
int Admin::check_num_courses_can_add(int iid) {
	int count = 0;
	for (auto x : DataBase::progress_vector) {
		if (iid == x.first) {
			count++;
		}
	}
	return count;
}
/************************************************************************/
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
/************************************************************************/
bool Admin::check_num_maxstud(int numstud) {
	Course course;
	const int maxnum_of_stud = 2000;
	if (numstud <= maxnum_of_stud) {
		return true;
	}
	else {
		return false;
	}
}
/************************************************************************/
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
/************************************************************************/
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
/************************************************************************/
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
/************************************************************************/
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
bool Admin::check_pre_exist(string course_name, string pre_name)
{
	for (auto x : DataBase::prerequisite_vector) {
		if (course_name == x.first && pre_name == x.second) {
			return false;
		}
	}
	return true;
}
/************************************************************************/
bool Admin::check_course_code_exist(string code) {
	for (auto x : DataBase::courses_map) {
		if (code == x.first)
			return true;
	}
	return false;
}
/************************************************************************/
bool Admin::check_course_name_exist(string name) {
	for (auto x : DataBase::courses_map) {
		if (name == x.second.get_Course_name())
			return true;
	}
	return false;
}
/************************************************************************/
bool Admin::check_ccode2_exist(string code, string codeee) {
	for (auto x : DataBase::courses_map) {
		if (code == x.first && code != codeee)
			return false;
	}
	return true;
}
/************************************************************************/
bool Admin::check_cname2_exist(string name, string nam) {
	for (auto x : DataBase::courses_map) {
		if (name == x.second.get_Course_name() && name != nam)
			return false;
	}
	return true;
}
/************************************************************************/