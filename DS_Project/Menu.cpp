#include "Menu.h"
#include <iostream>
#include <fstream>
#include "Admin.h"
#include "Student.h"
#include"Course.h"
#include"sqlite/sqlite3.h"
#include <vector>
#include <algorithm>
vector<string> LOGDATA;

static int callbacklogin(void* data, int argc, char** argv, char** azColName)
{
	string uname = argv[0];
	string upass = argv[1];
	LOGDATA.push_back(uname);
	LOGDATA.push_back(upass);

	return 0;
}

void Menu::login() {
	string uname, upass, un, up;

	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("myDb.db", &DB);
	string data("CALLBACK FUNCTION");
	string sql;
	system("cls");
	cout << "\n";
	cout << "                           ***************\n";
	cout << "    ************           * Student Ums *           *************\n ";
	cout << "                          ***************\n";
	cout << "              ********************************************\n";
	cout << "              ****************login page******************\n";
	cout << "              ********************************************\n\n";
	cout << "Enter your username : \n";
	cin >> uname;
	transform(uname.begin(), uname.end(), uname.begin(), ::tolower);

	cout << "Enter your password :\n";
	cin >> upass;
	transform(upass.begin(), upass.end(), upass.begin(), ::tolower);

	cout << "\n\n";

	if (uname == "admin" && upass == "admin") {
		adminmenu();
	}
	sql = ("SELECT   ID,PASSWORD    FROM  STUDENT   WHERE ID='" + uname + "' AND PASSWORD ='" + upass + "'  ;");

	if (exit) {
		std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		return;
	}
	else
		std::cout << "Opened Database Successfully! \n" << std::endl;

	int rc = sqlite3_exec(DB, sql.c_str(), callbacklogin, (void*)data.c_str(), NULL);

	if (rc != SQLITE_OK)
		cerr << "Error SELECT" << endl;
	else {
		cout << "Operation OK!" << endl;
	}

	if (uname == LOGDATA.at(0) && upass == LOGDATA.at(1)) {
		studmenu();
	}

	else if (LOGDATA.empty()) {
		cout << "   Your  Username Or Password  is Wrong !  \n";
	}
}

void Menu::adminmenu() {
	Admin admin;
	int choice;
	system("cls");

	cout << "\n";
	cout << "                           ***************\n";
	cout << "    ************           * Student Ums *           *************\n ";
	cout << "                          ***************\n";
	cout << "              ********************************************\n";
	cout << "              ****************Admin page******************\n";
	cout << "              ********************************************\n\n";

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
		admin.addCourse();

		break;
	case 2:
		system("cls");

		break;

	case 3:
		system("cls");
		admin.update();
		break;

	case 4:
		system("cls");
		admin.list_student_of_course();
		break;
	case 5:
		system("cls");
		admin.list_Courses_of_Student();
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
		cout << "sorry wrong choice !!\n";

	then:adminmenu();
	}
}

/******************************************************************/

void Menu::studmenu() {
	int choice;

	cout << "\n";
	cout << "                           ***************\n";
	cout << "    ************           * Student Ums *           *************\n ";
	cout << "                          ***************\n";
	cout << "              ********************************************\n";
	cout << "              ***************  Welcome  ******************\n";
	cout << "              ********************************************\n\n";

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
		cout << "sorry wrong choice !!";
		studmenu();
	}
}