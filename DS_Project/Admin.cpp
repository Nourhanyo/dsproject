#include "Admin.h"
#include"sqlite/sqlite3.h"
#include<string>
#include <iostream>
using namespace std;


int Admin::id = 0;


/*for static variable (id)*/
Admin::Admin(string nam, string pass) {
	id++;
	name = nam;
	password = pass;

}




Admin::Admin()
{
}

void Admin::insert_At_Student(string  first_name_student, string second_name_student, string third_name_student, int student_password, int stud_academic_year) {
	char* err;
	sqlite3* db;
	string s = first_name_student, a = second_name_student, b = third_name_student;
	int q = student_password, w = stud_academic_year;

	sqlite3_stmt* stmt;
	sqlite3_open("myDb.db", &db);
	string query = "insert into STUDENT(F_NAME , L_NAME ,TH_NAME , PASSWORD , ACADEMIC_YEAR)VALUES('" + s + "','" + a + "','" + b + "','" + to_string(q) + "','" + to_string(w) + "'); ";
	cout << query << endl;
	int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
	if (rc != SQLITE_OK) {
		cout << "errroooooorrrrr insert: " << err;
	}
}

void Admin::insert_At_finished_courses(int st_id, string f__courses)
{
	char* err;
	sqlite3* db;
	string s = f__courses;
	int  s_id = st_id;
	sqlite3_stmt* stmt;
	sqlite3_open("myDb.db", &db);
	string query = "insert into COURSE_FINSHED(STUD_ID , COURE_FINISHED)VALUES('" + to_string(s_id) + "','" + s + "'); ";
	cout << query << endl;
	int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
	if (rc != SQLITE_OK) {
		cout << "errroooooorrrrr insert: " << err;
	}
}

void Admin::insert_At_in_progress_courses(int st_id, string in_p__courses)
{
	char* err;
	sqlite3* db;
	string s = in_p__courses;
	int q = st_id;

	sqlite3_stmt* stmt;
	sqlite3_open("myDb.db", &db);
	string query = "insert into COURSE_PROG(STUD_ID , COURE_IN_PROGRESS)VALUES('" + to_string(q) + "','" + s + "'); ";
	cout << query << endl;
	int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
	if (rc != SQLITE_OK) {
		cout << "errroooooorrrrr insert: " << err;
	}
}

void Admin::add(string first_name, string second_name, string third_name, int password, int academic_year)
{
	Student* n = new Student(first_name, second_name, third_name, password, academic_year);
	if (size == 0) {

		head = tail = n;

		size++;
		Admin::insert_At_Student(first_name, second_name, third_name, password, academic_year);

	}
	else {

		tail->next = n;

		tail = tail->next;
		size++;
		Admin::insert_At_Student(first_name, second_name, third_name, password, academic_year);

	}



}

void Admin::add_finished_courses(string  f_courses)
{

	Student* b = new Student();

	if (size1 == 0) {

		head1 = tail1 = b;

		size1++;



	}
	else {

		tail1->next1 = b;

		tail1 = tail1->next1;
		size1++;

	}
}

void Admin::add_in_progress_courses(string  in_p_courses)
{

	Student* z = new Student();

	if (size2 == 0) {

		head2 = tail2 = z;

		size2++;



	}
	else {

		tail2->next2 = z;

		tail2 = tail2->next2;
		size2++;

	}
}



string f__course;
string in__p_course;
void Admin::add_courses_only()
{
	int s__id;
	cout << "enter the id of the student you want to add  course for " << endl;
	cin >> s__id;

	int num_of_finished_courses = 0;
	int num_of_in_progress_courses = 0;
	int press_for_course;

	cout << "if the student has no finished courses press 2 else press 1  " << endl;
	cin >> press_for_course;
	switch (press_for_course) {
	case 1:
		cout << "enter the number of student  finished courses" << endl;
		cin >> num_of_finished_courses;
		for (int i = 0; i <= num_of_finished_courses; i++) {
			cout << "add  course " << endl;

			cin >> f__course;
			Admin::add_finished_courses(f__course);
			Admin::insert_At_finished_courses(s__id, f__course);


		}
		cout << "enter the number of student  in progress courses" << endl;
		cin >> num_of_in_progress_courses;
		for (int i = 0; i < num_of_in_progress_courses; i++) {
			cout << "add  course " << endl;

			cin >> in__p_course;

			Admin::add_in_progress_courses(in__p_course);

			Admin::insert_At_in_progress_courses(s__id, in__p_course);


		}
		break;
	case 2:
		cout << "enter the number of student  in progress courses" << endl;
		cin >> num_of_in_progress_courses;
		for (int i = 0; i < num_of_in_progress_courses; i++) {
			cout << "add  course " << endl;

			cin >> in__p_course;

			Admin::add_in_progress_courses(in__p_course);

			Admin::insert_At_in_progress_courses(s__id, in__p_course);
		}
			break;
	default:
		cout << "invalid" << endl;
		break;
		}



	}

void Admin::Add_Student()
{
	int press_;
	string f_name1;
	string s_name1;
	string th_name1;
	int password1;
	int academic_year1;


	cout << "if you want to add multiple students press 1 " << endl;
	cout << "if you want to add one students press 2 " << endl;
	cin >> press_;
	if (press_ == 1) {

		int num_of_students;
		cout << "enter the number of stdent you want to add  " << endl;
		cin >> num_of_students;
		for (int i = 0; i < num_of_students; i++) {
			cout << "enter student name " << endl;
			cin >> f_name1 >> s_name1 >> th_name1;
			cout << "enter student password " << endl;
			cin >> password1;
			cout << "enter student acadamic_year " << endl;
			cin >> academic_year1;
			Admin::add(f_name1, s_name1, th_name1, password1, academic_year1);

			Admin::add_courses_only();



		}
	}
	else if (press_ == 2) {

		cout << "enter student name " << endl;
		cin >> f_name1 >> s_name1 >> th_name1;
		cout << "enter student password " << endl;
		cin >> password1;
		cout << "enter student acadamic_year " << endl;
		cin >> academic_year1;

		Admin::add(f_name1, s_name1, th_name1, password1, academic_year1);
		Admin::add_courses_only();

	}



	else {
		cout << "invaled number " << endl;
	}

}
Admin::~Admin(){
	

}


