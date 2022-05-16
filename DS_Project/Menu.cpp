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
vector<string> LOGDATA;



void Menu::login() {
	string name, pass;

	system("cls");
	cout << "\n";
	cout << "                        ************           * Student Ums *           *************\n ";
	cout << endl;
	cout << "                                           **********************\n";
	cout << "                                           *     login page     *\n";
	cout << "                                           **********************\n";

	cout << "Enter your username : \n";
	cin >> name;
	transform(name.begin(), name.end(), name.begin(), ::tolower);

	cout << "Enter your password :\n";
	cin >> pass;
	transform(pass.begin(), pass.end(), pass.begin(), ::tolower);

	cout << "\n\n";

	if (Check_Admin_Data(name, pass)) {
		adminmenu(name);
	}
	else {
		if (Check_Stud_Data(name, pass)) {
			studmenu(name);
		}
		else {
			cout << " Your Username Or Password is Wrong !  \n";
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
	cout << "1-AddCourse\n";
	cout << "2-AddStudent\n";
	cout << "3-Update Course\n";
	cout << "4-View List OF Student in Specific Course\n";
	cout << "5-View List OF  All Finished Course of Specific Student\n";
	cout << "6-Exit\n";

	cout << "Enter your choice : ";
	cin >> choice;

	switch (choice)
	{
	case 1:
		system("cls");
		admin.Addcourse();

		break;
	case 2:
		system("cls");

		break;

	case 3:
		system("cls");
		admin.ModifyCourses();
		break;

	case 4:
		system("cls");
		/*admin.list_student_of_course();*/
		break;
	case 5:
		system("cls");
		/*admin.list_Courses_of_Student();*/
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
		cout << "Sorry Wrong Choice !!\n";

	then:adminmenu(name);
	}
}

/******************************************************************/

void Menu::studmenu(string name) {
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
	cout << "1-   \n";
	cout << "2-   \n";
	cout << "3-   \n";
	cout << "4- Exist \n ";
	cout << "Enter your choice : ";
	cin >> choice;

	switch (choice)
	{
	case 1:system("cls");
		break;
	case 2:system("cls");

		break;

	case 3:system("cls");
		break;
	case 4:
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
bool Menu::Check_Stud_Data(string name, string password) {
	for (auto x : DataBase::students_map) {

		if (x.second.get_f_name() == name, x.second.get_student_password() == password) {
			return true;
		}
		else {
			return false;
		}
	}
}
bool Menu::Check_Admin_Data(string name, string password) {
	for (auto x : DataBase::admins_map) {

		if (x.second.get_fname() == name, x.second.get_admin_pass() == password) {
			return true;
		}
		else {
			return false;
		}
	}



}