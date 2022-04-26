#include "Admin.h"
#include"sqlite/sqlite3.h"
#include<string>


int Admin::id = 0;/*for static variable (id)*/
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
	string s = first_name_student, a = second_name_student , b = third_name_student;
	int q = student_password  , w = stud_academic_year;
	
	sqlite3_stmt* stmt;
	sqlite3_open("myDb.db", &db);
	string query = "insert into STUDENT(F_NAME , L_NAME ,TH_NAME , PASSWORD , ACADEMIC_YEAR)VALUES('" + s + "','" + a + "','" + b + "','" + to_string(q) + "','" + to_string(w) + "'); ";
	cout << query << endl;
	int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
	if (rc != SQLITE_OK) {
		cout << "errroooooorrrrr insert: " << err;
	}
}

void Admin::insert_At_finished_courses( int id , string f__courses)
{
	char* err;
	sqlite3* db;
	string s = f__courses;
	int  s_id = id;
	sqlite3_stmt* stmt;
	sqlite3_open("myDb.db", &db);
	string query = "insert into COURSE_FINSHED(STUD_ID , COURE_FINISHED)VALUES('" + to_string(s_id) + "','" + s  + "'); ";
	cout << query << endl;
	int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
	if (rc != SQLITE_OK) {
		cout << "errroooooorrrrr insert: " << err;
	}
}

void Admin::insert_At_in_progress_courses(int id, string in_p__courses )
{
	char* err;
	sqlite3* db;
	string s = in_p__courses;
	int q = id;

	sqlite3_stmt* stmt;
	sqlite3_open("myDb.db", &db);
	string query = "insert into COURSE_PROG(STUD_ID , COURE_IN_PROGRESS)VALUES('" + to_string(q) + "','" + s +  "'); ";
	cout << query << endl;
	int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
	if (rc != SQLITE_OK) {
		cout << "errroooooorrrrr insert: " << err;
	}
}

void Admin::add(string first_name, string second_name, string third_name,  int password, int academic_year)
{
	Student* n = new Student(first_name, second_name, third_name, password, academic_year);

	if (size == 0) {
		
		head = tail = n;

		size++;


	}
	else {
		
		tail->next = n;

		tail = tail->next;
		size++;

	}
}

void Admin::add_finished_courses()
{
	string  f_courses;
	cout << "enter your finished courses" << endl;
	cin >> f_courses;
	Student* b = new Student();

	if (size1 == 0) {
		b->get_finished_coursese() = f_courses;
		
		head1 = tail1 = b; 

		size1++;


	}
	else {
		b->get_finished_coursese() = f_courses;

		tail1->next1 = b;

		tail1 = tail1->next1; 
		size1++;

	}
}



void Admin::display()

{


	Student* tmp;
	tmp = head;
	while (tmp != NULL)
	{

		cout << tmp->get_f_name() << " " << tmp->get_s_name() << " " << tmp->get_th_name() << endl;
		cout << tmp->get_student_id() << endl;
		cout << tmp->get_acadamic_year() << endl;


		tmp = tmp->next;




	}





}

void Admin::Add_Student()
{
	int press_;
	string f_name1;
	string s_name1;
	string th_name1;
	int password1;
	int acadamic_year1;
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
			cin >> acadamic_year1;

			Admin::add(f_name1, s_name1, th_name1, password1, acadamic_year1);
			Admin :: insert_At_Student(f_name1, s_name1, th_name1, password1, acadamic_year1);

		}



	}
	else if (press_ == 2) {

		cout << "enter student name " << endl;
		cin >> f_name1 >> s_name1 >> th_name1;
		cout << "enter student password " << endl;
		cin >> password1;
		cout << "enter student acadamic_year " << endl;
		cin >> acadamic_year1;

		Admin::add(f_name1, s_name1, th_name1, password1, acadamic_year1);

		Admin :: insert_At_Student(f_name1, s_name1, th_name1, password1, acadamic_year1);




	}
	else {
		cout << "invaled number " << endl;
	}
}
Admin::~Admin() {}

