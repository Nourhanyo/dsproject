#include<iostream>
#include "Student.h"
#include "Admin.h"
#include "sqlite/sqlite3.h"
#include<string>
 int Student :: callback(void* data, int argc, char** argv, char** azColName)
{
	int i;
	fprintf(stderr, "%s: ", (const char*)data);

	Student stud;
	
	string a  = argv[4];
	int s_password = stoi(a);
	stud.password = s_password;
	string b =  argv[5];
	int academic_year_ = stoi(b);
	stud.acadamic_year = academic_year_;
	
	printf("\n");
	return 0;
}

 int Student::callback1(void* data, int argc, char** argv, char** azColName)
 {
	 Student s1; 
	 s1.finished_courses = argv[1];
	 

	 return 0;
 }
 int Student::callback2(void* data, int argc, char** argv, char** azColName)
 {
	 Student s2;
	
	 s2.courses_in_progress = argv[1];

	 return 0;
 }

 
int Student::id = 0;/*for static variable (id)*/
Student::Student(int id ,string fnam, string snam, string thnam , int pass, int aca) {
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
	return  to_string(password);
}
string Student::get_acadamic_year()
{
	return  to_string(acadamic_year);
}
string Student::get_student_id()
{
	return   to_string(id);


}

void Student::Edit_Stud_data()
{
	Student stud;
	int id_;
	cout << "Enter student  id  you want to edite ?: \n ";
	cin >> id_;
	
	cout << "  \n\n ";
	cout << "Enter student password : \n ";
	cin >> stud.password;
	cout << "  \n\n ";
	cout << "Enter student  academic year : \n ";
	cin >> stud.acadamic_year;
	
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	string sql;
	const char* data = "Callback function called";

	rc = sqlite3_open("myDb.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return;
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}




	sql =("UPDATE STUDENT SET (PASSWORD , ACADEMIC_YEAR) = ('" + to_string(stud.password) + "', '" + to_string(stud.acadamic_year) + "') where ID ='" + to_string(id_) + "' ");

	rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operation done successfully\n\n");
	}
	sqlite3_close(db);
}

void Student::Edit_f_course_data()
{
	cout << "welcome in edit finished courses " << endl;
	Student s1;
	int id_s;
	string f_course;
	cout << "Enter student  id  you want to edite the course ?: \n ";
	cin >> id_s;
	cout << "enter course name " << endl;
	cin >> f_course;
	cout << "enter finished course name you that  want " << endl;
	cin >> s1.finished_courses;
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	string sql;
	const char* data = "callback1 function called";

	rc = sqlite3_open("myDb.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return;
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}




	sql = ("UPDATE COURSE_FINSHED SET (COURE_FINISHED) = ('" + s1.finished_courses +  "') where STUD_ID ='" + to_string(id_s) + "' AND COURE_FINISHED ='"+ f_course+"'  ");

	rc = sqlite3_exec(db, sql.c_str(), callback1, (void*)data, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operation done successfully\n\n");
	}
	sqlite3_close(db);
}

void Student::Edit_in_p_course_data()
{
	cout << "welcome in edit in progress courses " << endl;
	Student s2;
	int id_s_;
	string in_p_course;
	cout << "Enter student  id  you want to edite the course ?: \n ";
	cin >> id_s_;
	cout << "enter course name " << endl;
	cin >> in_p_course;
	cout << "enter  course name you that  want " << endl;
	cin >> s2.courses_in_progress;
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	string sql;
	const char* data = "callback2 function called";

	rc = sqlite3_open("myDb.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return;
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}




	sql = ("UPDATE COURSE_PROG SET (COURE_IN_PROGRESS) = ('" + s2.courses_in_progress + "') where STUD_ID ='" + to_string(id_s_) + "' AND COURE_IN_PROGRESS ='" + in_p_course + "'  ");

	rc = sqlite3_exec(db, sql.c_str(), callback2, (void*)data, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operation done successfully\n\n");
	}
	sqlite3_close(db);
}



Student ::~Student() {
}

