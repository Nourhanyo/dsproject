#include "Menu.h"
#include <iostream>
#include <fstream>
#include "Admin.h"
#include "Student.h"
#include"Course.h"
#include"sqlite/sqlite3.h"
#include <vector>
#include <algorithm>
#include "DataBase.h"
using namespace std;
vector<string> LOGDATA;
string Menu::name;
string Menu::name2;
string Menu::name3;
int Menu::id;

void Menu::login() {
	string  pass;

	system("cls");
	cout << "\n";
	cout << "                        ************           * Student Ums *           *************\n ";
	cout << endl;
	cout << "                                           **********************\n";
	cout << "                                           *     login page     *\n";
	cout << "                                           **********************\n";

	cout << "Enter your full name : \n";
	cin >> name;
	transform(name.begin(), name.end(), name.begin(), ::tolower);
	cin >> name2;
	transform(name2.begin(), name2.end(), name2.begin(), ::tolower);
	cin >> name3;
	transform(name3.begin(), name3.end(), name3.begin(), ::tolower);

	cout << "Enter your password :\n";
	cin >> pass;
	transform(pass.begin(), pass.end(), pass.begin(), ::tolower);

	cout << "\n\n";

	if (Check_Admin_Data(pass)) {
		adminmenu(name);
	}
	else {
		if (Check_Stud_Data( pass)) {
			studmenu(name);
		}
		else {
			cout << "Your Username Or Password is Wrong !  \n";
			system("pause 0");
			system("cls");
			login();
		}
	}

}

void Menu::adminmenu(string name) {
	Admin admin;
	int choice;
	system("cls");
	cout << "\n";
	cout << "                        ************           * Student Ums *           *************\n ";
	cout << endl;
	cout << "                                           **********************\n";
	cout << "                                           *      Admin Page    *\n";
	cout << "                                           **********************\n";
	cout << " Welcome, " << name << "\n";
	cout << "**********************\n";
	cout << "1-Add New Course\n";
	cout << "2-Add New Student\n";
	cout << "3-Update/Delete Course\n";
	cout << "4-View List OF Students in Specific Course\n";
	cout << "5-View List OF Courses of Specific Student\n";
	cout << "6-Fill prerequisite of Specific Course\n";
	cout << "7-Add finished courses and progressed courses\n";
	cout << "8-Exit\n";

	cout << "Enter your choice : ";
	cin >> choice;

	string course_name;
	switch (choice)
	{
	case 1:
		system("cls");
		course_name=admin.Addcourse();
		cout << "If ypu want to add course prerequisite press 1,else press 0\n";
		int p;
		cin >> p;
		if (p == 1) {
			admin.fill_prerequisite_list(course_name);
		}
		else {
			system("pause");
			adminmenu(name);
		}
		break;
			
	case 2:
		system("cls");
		admin.add_stud();
		system("pause");
		adminmenu(name);
		break;

	case 3:
		system("cls");
		admin.ModifyCourses();
		break;

	case 4:
		system("cls");
		admin.view_studs_of_course();
		system("pause");
		adminmenu(name);
		break;
	case 5:
		system("cls");
		admin.view_courses_of_stud();
		system("pause");
		adminmenu(name);
		break;
	case 6:
		system("cls");
		cout << "Enter Course name\n";
		cin >> course_name;
		admin.fill_prerequisite_list(course_name);
		system("pause");
		adminmenu(name);
		break;
	case7:
		system("cls");
		admin.add_f_course_in_p_course();
		system("pause");
		adminmenu(name);
		break;
	case 8:
		system("cls");
		cout << "                                                                      \n\n\n";
		cout << "                                  ______________________________________\n\n";
		cout << "                                  ************ See You Soon ************\n";
		cout << "                                  ______________________________________\n\n\n\n";
		break;
	default:
		system("cls");
		cout << "Sorry Wrong Choice !!\n";

	then:adminmenu(name);
	}
}

/******************************************************************/

void Menu::studmenu(string name) {
	Student stud;
	for (auto x: DataBase::students_map) {
		if (name == x.second.get_f_name() && name2 == x.second.get_s_name() && name3 == x.second.get_th_name()) {
			id = stoi(x.first);
			break;
		}
	}
	int choice;
	system("cls");
	cout << "\n";
	cout << "                        ************           * Student Ums *           *************\n ";
	cout << endl;
	cout << "                                           **********************\n";
	cout << "                                           *     Student Page   *\n";
	cout << "                                           **********************\n";
	cout << " Welcome, " << name << "\n";
	cout << "**********************\n";
	cout << "1-View List of Available Courses\n";
	cout << "2-View Details of specific Course\n";
	cout << "3-Regisiter for A Course\n";
	cout << "4-View My Courses\n";
	cout << "5-Edit My data\n";
	cout << "6- Exist \n ";
	cout << "Enter your choice : ";
	cin >> choice;
	int p;
	string s;
	switch (choice)
	{
	case 1:system("cls");
		cout << "Your Available courses:\n";
		stud.view_available_courses(id);
		system("pause");
		studmenu(name);
		break;
	case 2:system("cls");
		cout << "Your Available courses:\n";
		stud.view_available_courses(id);
		cout << endl;
		stud.View_CoursesDetails();
		system("pause");
		studmenu(name);
		break;

	case 3:system("cls");
		cout << "Your Available courses:\n";
		stud.view_available_courses(id);
		cout << "press 1 to view details of specific Course...press 2 to register for a course: ";
		cin >> p;
		if (p == 1) {
			s=stud.View_CoursesDetails();
			cout << "If you want to regisiter for this course press 1\n";
			cin >> p;
			if (p == 1) {
				stud.Request_course(s,id);

			}
			else {
				cout << "invalid choice\n";
				studmenu(name);
			}

		}
		else if(p==2) {
			cout << "\nEnter Course Came\n";
			cin >> s;
			stud.Request_course(s,id);
		}
		else {
			cout << "invalid choice\n";
			studmenu(name);
		}
		system("pause");
		studmenu(name);
		break;

	case 4:
		stud.view_stud_courses(id);
		system("pause");
		studmenu(name);
		break;
	case 5:
		stud.edit_stud_data(id);
		system("pause");
		studmenu(name);
		break;
	case 6:
		system("cls");
		cout << "                                                                      \n\n\n";
		cout << "                                  ______________________________________\n\n";
		cout << "                                  ************ See You Soon ************\n";
		cout << "                                  ______________________________________\n\n\n\n";
		break;
	default:
		system("cls");
		cout << "Sorry Wrong Choice....!";
		studmenu(name);
	}
}
bool Menu::Check_Stud_Data( string password) {
	for (auto x : DataBase::students_map) {

		if (x.second.get_f_name() == name&& x.second.get_student_password() == password&&x.second.get_s_name()==name2&& x.second.get_th_name() == name3) {
			return true;
		}
		else {
			return false;
		}
	}
}
bool Menu::Check_Admin_Data(string password) {
	for (auto x : DataBase::admins_map) {

		if (x.second.get_fname() == name && x.second.get_admin_pass() == password&& x.second.get_lname() == name2) {
			return true;
		}
		else {
			return false;
		}
	}



}