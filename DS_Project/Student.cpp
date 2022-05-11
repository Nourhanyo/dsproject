#include<iostream>
#include "Student.h"
#include "Admin.h"
#include "Course.h"
#include "sqlite/sqlite3.h"
#include<string>
#include <vector>
#include <algorithm>
using namespace std;
sqlite3* DB;
vector<string> allCourses_vec;
vector<string> finishedCourses_vec;
vector<string> preRequisite_vec;
vector<string> remainCrs_vec;
vector<string> AvailabeCrs_vec;
int Student::callbackup(void* data, int argc, char** argv, char** azColName)
{
	fprintf(stderr, "%s \n", (const char*)data);
	for (int i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}
///////////////////////////////////////////////////////////////////////////
int Student::callback_req(void* data, int argc, char** argv, char** azColName)
{
	string query;
	int rc;
	cout << "\n\n enter ID for student: ";
	int id;
	cin >> id;
	cout << "\n";
	char* err;
	Course course;
	course.set_code(argv[0]);
	course.set_Course_Name(argv[1]);
	query = "insert into COURSE_PROG VALUES('" + to_string(id) + "','" + course.get_Course_name() + "');";
	cout << query << endl;
	rc = sqlite3_exec(DB, query.c_str(), NULL, NULL, &err);
	return 0;
}
///////////////////////////////////////////////////////////////////////////
int Student::callback_ALL(void* data, int argc, char** argv, char** azColName)
{
	fprintf(stderr, "%s \n", (const char*)data);

	for (int i = 0; i < argc; i++) {
		printf(" %s\n", argv[i] ? argv[i] : "NULL");
	}

	return 0;
}
///////////////////////////////////////////////////////////////////////////
static int allCrs_callback(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		allCourses_vec.push_back(argv[i]);
		// printf(" %s\n", argv[i] ? argv[i] : "NULL");
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////
static int finishedCrs_callback(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		finishedCourses_vec.push_back(argv[i]);
		// printf(" %s\n", argv[i] ? argv[i] : "NULL");
	}

	return 0;
}
///////////////////////////////////////////////////////////////////////////
static int preRequisiteList_callback(void* data, int argc, char** argv, char** azColName)
{

	for (int i = 0; i < argc; i++)
	{
		preRequisite_vec.push_back(argv[i]);
		// printf(" %s\n", argv[i] ? argv[i] : "NULL");
	}

	return 0;
}
///////////////////////////////////////////////////////////////////////////
int Student::id = 0;/*for static variable (id)*/
Student::Student(int id, string fnam, string snam, string thnam, string pass, string aca) {
	this->id = id;
	f_name = fnam;
	s_name = snam;
	th_name = thnam;
	password = pass;
	id++;
	next = NULL;
}
Student::Student() {
	next1 = NULL;
	next2 = NULL;
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
string Student::get_finished_coursese()
{
	return  finished_courses;
}
string Student::get_courses_in_progress()
{
	return   courses_in_progress;
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
/*
	we should edit it
*/
void Student::Edit_Stud_data()
{
	Student stud;
	int id_;
	cout << "Enter student  id  you want to edite ?: \n ";
	cin >> id_;
	/*
	remove it and take id from login...
	*/
	cout << "  \n\n ";
	cout << "Enter student password : \n ";
	cin >> stud.password;
	cout << "  \n\n ";
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	string sql;
	const char* data = "************************************************";
	rc = sqlite3_open("myDb.db", &db);
	sql = ("UPDATE STUDENT SET (PASSWORD) = ('" + stud.password + "') where ID ='" + to_string(id_) + "' ");
	rc = sqlite3_exec(db, sql.c_str(), NULL, (void*)data, &zErrMsg);
	sqlite3_close(db);
}
///////////////////////////////////////////////////////////////////////////
void Student::Drop_courses()
{
	Student s2;
	int id_s_;
	string in_p_course;
	cout << "Enter student  id  you want to edite the course ?: \n ";
	cin >> id_s_;

	/* will take it from login*/
	view_prog_courses(id_s_);
	cout << "enter course name you want to drop  " << endl;
	cin >> in_p_course;
	sqlite3* db;
	char* zErrMsg = 0;
	const char* data = "";
	int rc = sqlite3_open("myDb.db", &db);
	string sql= "DELETE from  COURSE_PROG  where STUD_ID ='" + to_string(id_s_) + "' AND COURE_IN_PROGRESS ='" + in_p_course + "'  ";
	rc = sqlite3_exec(db, sql.c_str(), NULL, (void*)data, &zErrMsg);
	sqlite3_close(db);
}
///////////////////////////////////////////////////////////////////////////
void Student::CourseDetails() {
	system("cls");
	cout << "*********************************CourseDetails*******************************\n\n\n";
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("myDb.db", &DB);
	string data("*********************************");
	string sql;
	string name;
	cout << "Enter Course name ...\n\n";
	cin >> name;
	sql = ("SELECT * FROM COURSE where NAME ='" + name + "' ;");
	int rc = sqlite3_exec(DB, sql.c_str(), callbackup, (void*)data.c_str(), NULL);
	int choose{};
	system("pause 0");
	sqlite3_close(DB);
}
///////////////////////////////////////////////////////////////////////////
void Student::Request_Course(string REQ_COURSE) {
	int exit = 0;
	exit = sqlite3_open("myDb.db", &DB);
	string data("CALLBACK FUNCTION");
	string sql;
	sql = ("SELECT * FROM COURSE where CODE ='" + REQ_COURSE + "' ;");
	if (exit) {
		std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		return;
	}
	else
		std::cout << "Opened Database Successfully! " << std::endl;

	int rc = sqlite3_exec(DB, sql.c_str(), callback_req, (void*)data.c_str(), NULL);

	if (rc != SQLITE_OK)
		cerr << "Error SELECT" << endl;
	else {
		cout << "Operation OK!" << endl;
	}
	sqlite3_close(DB);
}
///////////////////////////////////////////////////////////////////////////
void Student::VIEW_STUD_COURSES() {
	int IID = 0, rc;
	cout << "enter stud ID : ";
	cin >> IID;
	cout << "\n"; 
	view_prog_courses(IID);
	cout << "*********************************************************\n";
	view_finished_courses(IID);

}
///////////////////////////////////////////////////////////////////////////
void Student:: view_prog_courses(int iid) {
	sqlite3_open("myDb.db", &DB);
	string data("*********************************************************");
	string sql = ("SELECT COURE_IN_PROGRESS FROM COURSE_PROG where STUD_ID ='" + to_string(iid) + "' ;");
	cout << "\nCourses in Progress\n\n";
	int rc = sqlite3_exec(DB, sql.c_str(), callback_ALL, (void*)data.c_str(), NULL);
	sqlite3_close(DB);
}
///////////////////////////////////////////////////////////////////////////
void Student::view_finished_courses(int iid) {
	sqlite3_open("myDb.db", &DB);
	string data("*********************************************************");
	string sql = ("SELECT COURE_FINISHED FROM COURSE_FINSHED where STUD_ID ='" + to_string(iid) + "' ;");
	cout << "\n\nCourses finished\n\n";
	int rc = sqlite3_exec(DB, sql.c_str(), callback_ALL, (void*)data.c_str(), NULL);
	sqlite3_close(DB);
}
///////////////////////////////////////////////////////////////////////////
void Student::ViewAv_list()
{
	system("cls");
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("myDb.db", &DB);
	string data("CALLBACK FUNCTION");
	string sql;

	/*if (exit) {
		std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
		return;
	}
	else
		std::cout << "Opened Database Successfully! \n " << std::endl;*/

		// Selecting All Courses from DB
	sql = (" SELECT NAME   FROM COURSE  ;");
	int rc = sqlite3_exec(DB, sql.c_str(), allCrs_callback, (void*)data.c_str(), NULL);




	// Selecting Finished Courses form DB
	/*VIIIIP*/

	string var = "2"; // Should be stored from student who logged in 
	sql = (" SELECT COURE_FINISHED  FROM  COURSE_FINSHED  where  STUD_ID = '" + var + "'  ;");
	rc = sqlite3_exec(DB, sql.c_str(), finishedCrs_callback, (void*)data.c_str(), NULL);



	GetRemainCrs(); // Difference Between All Courses & Finished Courses -> remainCrs_vec 


  // Selecting Prerequisite List for each remain course from DB
	for (int i = 0; i < remainCrs_vec.size(); i++)
	{
		string preCrsName = remainCrs_vec[i];
		sql = (" SELECT preq  FROM COURSE_PREREQUISITE  where  COURSE_NAME = '" + preCrsName + "'  ;");
		rc = sqlite3_exec(DB, sql.c_str(), preRequisiteList_callback, (void*)data.c_str(), NULL);

		GetAvailableCrs(i); //Get Available Courses by checking Prerequisite of remain course vector


		preRequisite_vec.clear(); // reset Prerequisite vector after each itteration of RemainCrs vector 
	}

	// Printing Avaliable Crs
	cout << "AvaliableCrs\n*************\n";
	for (size_t i = 0; i < AvailabeCrs_vec.size(); i++)
	{
		cout << AvailabeCrs_vec[i] << endl;
	}

	/*
	if (rc != SQLITE_OK)
		cerr << "Error SELECT" << endl;

	else
		cout << "Operation OK!" << endl;
		*/


}
///////////////////////////////////////////////////////////////////////////
void Student::GetRemainCrs() {
	for (int i = 0; i < allCourses_vec.size(); i++)
	{
		int flag = 0;
		for (int j = 0; j < finishedCourses_vec.size(); j++) {

			if (allCourses_vec[i] == finishedCourses_vec[j])
				flag = 1;

		}
		if (flag == 0)
			remainCrs_vec.push_back(allCourses_vec[i]);
	}

}
///////////////////////////////////////////////////////////////////////////
void Student::GetAvailableCrs(int remainIndx) {

	string av_Crs = remainCrs_vec[remainIndx];
	int flag2 = -1;
	for (int j = 0; j < preRequisite_vec.size(); j++) {
		flag2 = 1;
		for (int z = 0; z < finishedCourses_vec.size(); z++) {

			if (preRequisite_vec[j] == finishedCourses_vec[z])
			{
				flag2 = 0;
				break;
			}
		}
	}
	if (flag2 == 0 || preRequisite_vec.size() == 0)
		AvailabeCrs_vec.push_back(av_Crs);

}
///////////////////////////////////////////////////////////////////////////
Student ::~Student() {}