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

void Admin::insert_At_Student(int stud_id , string  first_name_student, string second_name_student, string third_name_student, int student_password, int stud_academic_year) {
	char* err;
	sqlite3* db;
	string s = first_name_student, a = second_name_student, b = third_name_student;
	int q = student_password, w = stud_academic_year, d = stud_id;

	sqlite3_stmt* stmt;
	sqlite3_open("myDb.db", &db);
	string query = "insert into STUDENT(ID,F_NAME , L_NAME ,TH_NAME , PASSWORD , ACADEMIC_YEAR)VALUES('" + to_string(d) + "','" + s + "','" + a + "','" + b + "','" + to_string(q) + "','" + to_string(w) + "'); ";
	cout << query << endl;
	int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
	if (rc != SQLITE_OK) {
		cout << "errroooooorrrrr insert: " << err;
	}
	else {
		Admin::add_courses_only();

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

void Admin::add(int student__id ,string first_name, string second_name, string third_name, int password, int academic_year)
{
	Student* n = new Student(student__id ,first_name, second_name, third_name, password, academic_year);
	if (size == 0) {
		n->get_student_id() = student__id;
		n->get_f_name() = first_name;
		n->get_s_name() = second_name;
		n->get_th_name() = third_name;
		n->get_student_password() = password;
		n->get_acadamic_year() = academic_year;

		head = tail = n;

		size++;
	 Admin::insert_At_Student(student__id ,first_name, second_name, third_name, password, academic_year);

	}
	else {
		n->get_student_id() = student__id;
		n->get_f_name() = first_name;
		n->get_s_name() = second_name;
		n->get_th_name() = third_name;
		n->get_student_password() = password;
		n->get_acadamic_year() = academic_year;

		tail->next = n;

		tail = tail->next;
		size++;
		Admin::insert_At_Student(student__id ,first_name, second_name, third_name, password, academic_year);

	}



}

void Admin::add_finished_courses(int Id ,string  f_courses )
{

	Student* b = new Student();

	if (size1 == 0) {
		b->get_student_id() = Id;

		b->get_finished_coursese() = f_courses;
		

		head1 = tail1 = b;

		size1++;



	}
	else {

		b->get_student_id() = Id;

		b->get_finished_coursese() = f_courses;


		tail1->next1 = b;

		tail1 = tail1->next1;
		size1++;

	}
}

void Admin::add_in_progress_courses(int ID ,string  in_p_courses  )
{

	Student* z = new Student();

	if (size2 == 0) {
		z->get_student_id() = ID;

		z->get_courses_in_progress() = in_p_courses;


		head2 = tail2 = z;

		size2++;



	}
	else {

		z->get_student_id() = ID;

		z->get_courses_in_progress() = in_p_courses;


		tail2->next2 = z;

		tail2 = tail2->next2;
		size2++;

	}
}



string f__course;
string in__p_course;
void Admin::add_courses_only()
{
	
	cout << "enter stud id again " << endl;
	int S_ID;
	cin >> S_ID;
	int num_of_finished_courses = 0;
	int num_of_in_progress_courses = 0;
	int press_for_course;

	cout << "if the student has no finished courses press 2 else press 1  " << endl;
	cin >> press_for_course;
	switch (press_for_course) {
	case 1:
		cout << "enter the number of student  finished courses" << endl;
		cin >> num_of_finished_courses;
		for (int i = 0; i < num_of_finished_courses; i++) {
			cout << "add  course " << endl;

			cin >> f__course;
			Admin::add_finished_courses(S_ID,f__course);
			Admin::insert_At_finished_courses(S_ID, f__course);


		}
		cout << "enter the number of student  in progress courses" << endl;
		cin >> num_of_in_progress_courses;
		for (int i = 0; i < num_of_in_progress_courses; i++) {
			cout << "add  course " << endl;

			cin >> in__p_course;

			Admin::add_in_progress_courses(S_ID,in__p_course);

			Admin::insert_At_in_progress_courses(S_ID, in__p_course);


		}
		break;
	case 2:
		cout << "enter the number of student  in progress courses" << endl;
		cin >> num_of_in_progress_courses;
		for (int i = 0; i < num_of_in_progress_courses; i++) {
			cout << "add  course " << endl;

			cin >> in__p_course;

			Admin::add_in_progress_courses(S_ID,in__p_course);
			Admin::insert_At_in_progress_courses(S_ID, in__p_course);

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
	int s_ID;
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
			cout << "enter the id of student" << endl;
			cin >> s_ID;
			cout << "enter student name " << endl;
			cin >> f_name1 >> s_name1 >> th_name1;
			cout << "enter student password " << endl;
			cin >> password1;
			cout << "enter student acadamic_year " << endl;
			cin >> academic_year1;

			Admin::add(s_ID, f_name1, s_name1, th_name1, password1, academic_year1);





		}
		

	}
	else if (press_ == 2) {
		cout << "enter the id of student" << endl;
		cin >> s_ID;
		cout << "enter student name " << endl;
		cin >> f_name1 >> s_name1 >> th_name1;
		cout << "enter student password " << endl;
		cin >> password1;
		cout << "enter student acadamic_year " << endl;
		cin >> academic_year1;

		Admin::add(s_ID, f_name1, s_name1, th_name1, password1, academic_year1);
	

	}



	else {
		cout << "invaled number " << endl;
	}



}



Admin::~Admin(){
	

}


