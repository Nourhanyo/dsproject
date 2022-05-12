#include "Admin.h"
#include"sqlite/sqlite3.h"
#include <string>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
#include "Menu.h"
#include"DataBase.h"
stack<Course>stck_Edite;
sqlite3* dd;
static int callback(void* data, int argc, char** argv, char** azColName)
{
	string code = argv[0];
	//we use it in first ubdate statment
	int i;
	fprintf(stderr, "%s: ", (const char*)data);
	int rc;
	string sql;
	stack<Course> s;
	Course course;
	course.set_code(argv[0]);

	course.set_Course_Name(argv[1]);

	string sa = argv[2];
	int a = stoi(sa);
	course.set_hours(a);

	string qq = argv[3];
	int aw = stoi(qq);
	course.set_max_numstud(aw);
	s.push(course);
	char* err;
	////////////////////////////////////////////

	cout << "******************************Edite_PAGE************************************\n\n\n";
	string nam = "";
	string cod = "";
	int hour;
	int maxx;
	cout << "Enter Course Name : \n ";
	cin >> nam;
	course.set_Course_Name(nam);
	//transform(course.get_Course_name().begin(), course.get_Course_name().end(), course.get_Course_name().begin(), ::tolower);
	cout << "  \n\n ";
	cout << "Enter Course Code : \n ";
	cin >> cod;
	course.set_code(cod);
	//transform(course.get_code().begin(), course.get_code().end(), course.get_code().begin(), ::tolower);
	cout << "  \n\n ";
	cout << "Enter Course hours : \n ";
	cin >> hour;
	course.set_hours(hour);
	cout << "  \n\n ";
	cout << "Enter max_numstud : \n ";
	cin >> maxx;
	course.set_max_numstud(maxx);
	cout << "  \n\n ";

	sql = "UPDATE COURSE SET(CODE, NAME, HOURS, MAX_NUM_STUD) = ('" + course.get_code() + "', '" + course.get_Course_name() + "', '" + to_string(course.get_hours()) + "', '" + to_string(course.get_max_numstud()) + "') where CODE='" + code + "'; ";
	cout << sql << endl;
	rc = sqlite3_exec(dd, sql.c_str(), callback, NULL, &err);

	cout << endl << endl;
	int choice;
	cout << "if you Want to Undo choose (1) \n" << "if you Want to Exit (2) \n" << "Enter your choice :\n";

	cin >> choice;

	switch (choice)
	{
	case 1:

		sql = " UPDATE COURSE SET(CODE, NAME, HOURS, MAX_NUM_STUD) = ('" + s.top().get_code() + "', '" + s.top().get_Course_name() + "', '" + to_string(s.top().get_hours()) + "', '" + to_string(s.top().get_max_numstud()) + "') where CODE='" + course.get_code() + "'; ";
		cout << sql << endl;
		rc = sqlite3_exec(dd, sql.c_str(), NULL, NULL, &err);
		break;

	default:
		break;
	}

	printf("\n");
	return 0;
}
////////////////////////////////////////////////////////////////////////////
static int callback2(void* data, int argc, char** argv, char** azColName)
{
	fprintf(stderr, "%s \n", (const char*)data);

	for (int i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n\n");
	return 0;
}
////////////////////////////////////////////////////////////////////////////
int Admin::id = 0; /*for static variable (id)*/
bool Admin::ADMIN_CHANGED = false;
Admin::Admin(string Fnam, string lName, string pass) {
	id++;
	get_fname() = Fnam;
	get_lname() = lName;
	password = pass;
}
Admin::Admin() {
}
////////////////////////////////////////////////////////////////////////////
/* we should call fillList inside this */
void Admin::addCourse() {
	system("cls");
	Course course;
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* err;
	cout << "******************************Add Course Page******************************\n\n\n";
	string cod, nam;
	int maaxx, ho;
	cout << "Enter Course Name : \n ";
	cin >> nam;
	course.set_Course_Name(nam);
	cout << "  \n\n ";
	cout << "Enter Course Code : \n ";
	cin >> cod;
	course.set_code(cod);
	cout << "  \n\n ";

	cout << "Enter max_numstud : \n ";
	cin >> maaxx;
	course.set_max_numstud(maaxx);
	cout << "  \n\n ";
	cout << "Enter Course hours : \n ";
	cin >> ho;
	course.set_hours(ho);
	cout << "  \n\n ";

	sqlite3_open("myDb.db", &db);
	string query = "insert into COURSE VALUES('" + course.get_code() + "','" + course.get_Course_name() + "','" + to_string(course.get_hours()) + "','" + to_string(course.get_max_numstud()) + "');";
	cout << query << endl;
	int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
	int choice;
	cout << "if you Wanna go back choose (1) \n\n" << "if you Wanna exist choose (0)\n\n";

	cout << "ENTER YOUR Choice ...\n";

	cin >> choice;

	switch (choice)
	{
	case 1:
		Menu m;
		m.adminmenu();
		break;

	default:
		cout << "See You Soon ";
		break;
	}
}
////////////////////////////////////////////////////////////////////////////
void Admin::update() {
	system("cls");
	cout << "***********************************Update_Page***********************************\n\n\n";
	cout << "1-Edite Course Data \n\n";
	cout << "2- Delete Course    \n\n";
	cout << "3- Go Back    \n\n";
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
		cout << "Enter valid number please ....\n\n";
	then:update();
		break;
	}
}////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void Admin::Edit() {
	system("cls");
	Course course;
	char* zErrMsg = 0;
	int rc;
	string sql;
	string code;
	cout << "******************************Edite_PAGE************************************\n\n\n";
	cout << "Enter Course Code  you want to edite ?: \n ";
	cin >> code;
	const char* data = "************************************";
	rc = sqlite3_open("myDb.db", &dd);
	sql = ("SELECT * FROM COURSE where CODE ='" + code + "' ;");
	rc = sqlite3_exec(dd, sql.c_str(), callback, (void*)data, &zErrMsg);
	sqlite3_close(dd);
	int choice;
	cout << "if you Wanna go back choose (1) \n\n" << "if you Wanna exist choose (0)\n\n";

	cout << "ENTER YOUR Choice ...\n";

	cin >> choice;

	switch (choice)
	{
	case 1:
		update();
		break;

	default:
		cout << "See You Soon ";
		break;
	}
}
////////////////////////////////////////////////////////////////////////////
void Admin::Delete() {
	system("cls");
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	string sql;
	const char* data = "**************************************";
	rc = sqlite3_open("myDb.db", &db);
	string code;
	cout << "*********************************DELETE PAGE *************************************\n\n\n";
	cout << "Enter COURSE code YOU WANT to DELETE ? ....\n";
	cin >> code;
	sql = "DELETE from COURSE where CODE='" + code + "';";
	cout << sql << endl;
	rc = sqlite3_exec(db, sql.c_str(), NULL, (void*)data, &zErrMsg);
	int choice;
	cout << "if you Wanna go back choose (1) \n\n" << "if you Wanna exist choose (0)\n\n";
	cout << "ENTER YOUR Choice ...\n";
	cin >> choice;
	switch (choice)
	{
	case 1:
		update();
		break;

	default:
		cout << "See You Soon ";
		break;
	}

	sqlite3_close(db);
}
////////////////////////////////////////////////////////////////////////////
void Admin::list_student_of_course() {
	system("cls");
	cout << "************Students in specific Course**********\n\n\n";
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("myDb.db", &DB);
	string data("***************************************");
	string sql;
	string name;
	cout << "Enter Course name \n";
	cin >> name;

	sql = ("SELECT  STUDENT.ID ,STUDENT.F_NAME ,STUDENT.L_NAME ,STUDENT.TH_NAME ,STUDENT.ACADEMIC_YEAR  FROM STUDENT,COURSE,COURSE_PROG   WHERE  COURSE_PROG.STUD_ID=STUDENT.ID AND COURSE.NAME=COURSE_PROG.COURE_IN_PROGRESS  AND COURSE.NAME = '" + name + "';");

	int rc = sqlite3_exec(DB, sql.c_str(), callback2, (void*)data.c_str(), NULL);

	int choice;
	cout << "if you Wanna go back choose (1) \n\n" << "if you Wanna exist choose (0)\n\n";

	cout << "ENTER YOUR Choice ...\n";

	cin >> choice;

	switch (choice)
	{
	case 1:
		Menu m;
		m.adminmenu();
		break;

	default:
		cout << "See You Soon ";
		break;
	}
}
////////////////////////////////////////////////////////////////////////////
void Admin::list_Courses_of_Student() {
	system("cls");
	cout << "************Student_Finished_Course**********\n\n\n";
	sqlite3* DB;
	int exit = 0, rc;
	exit = sqlite3_open("myDb.db", &DB);
	string data("CALLBACK FUNCTION");
	string sql;
	string fname, lname, thname;
	cout << "Enter Student ID\n";
	string IID;
	cin >> IID;
	sql = ("SELECT COURE_IN_PROGRESS FROM COURSE_PROG where STUD_ID ='" + IID + "' ;");
	cout << "\nCourses in Progress\n\n";

	rc = sqlite3_exec(DB, sql.c_str(), callback2, (void*)data.c_str(), NULL);
	cout << "*********************************************************\n\n";
	sql = ("SELECT COURE_FINISHED FROM COURSE_FINSHED where STUD_ID ='" + IID + "' ;");
	cout << "\n\nCourses finished\n\n";
	rc = sqlite3_exec(DB, sql.c_str(), callback2, (void*)data.c_str(), NULL);
	sqlite3_close(DB);
	int choice;
	system("pause 0");
	cout << "if you Wanna go back choose (1) \n\n" << "if you Wanna exist choose (0)\n\n";

	cout << "ENTER YOUR Choice ...\n";

	cin >> choice;

	switch (choice)
	{
	case 1:
		Menu m;
		m.adminmenu();
		break;

	default:
		cout << "See You Soon ";
		break;
	}
	system("pause 0");
}
//////////////////////////////////////////////////////////////////////////
//void Admin::insert_At_Student(int stud_id, string  first_name_student, string second_name_student, string third_name_student, string student_password, string stud_academic_year) {
//	/*char* err;
//	sqlite3* db;
//	string s = first_name_student, a = second_name_student, b = third_name_student;
//	string q = student_password, w = stud_academic_year;
//	int d = stud_id;
//
//	sqlite3_stmt* stmt;
//	sqlite3_open("myDb.db", &db);
//	string query = "insert into STUDENT(ID,F_NAME , L_NAME ,TH_NAME , PASSWORD , ACADEMIC_YEAR)VALUES('" + d + "', '" + s + "','" + a + "','" + b + "','" + q + "','" + w + "'); ";
//	cout << query << endl;
//	int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
//	if (rc != SQLITE_OK) {
//		cout << "errroooooorrrrr insert: " << err;
//	}
//
//	else {
//		Admin::add_courses_only();
//	}*/
//}
//////////////////////////////////////////////////////////////////////////////
//void Admin::insert_At_finished_courses(int st_id, string f__courses)
//{
//	char* err;
//	sqlite3* db;
//	string s = f__courses;
//	int  s_id = st_id;
//	sqlite3_stmt* stmt;
//	sqlite3_open("myDb.db", &db);
//	string query = "insert into COURSE_FINSHED(STUD_ID , COURE_FINISHED)VALUES('" + to_string(s_id) + "','" + s + "'); ";
//	cout << query << endl;
//	int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
//	if (rc != SQLITE_OK) {
//		cout << "errroooooorrrrr insert: " << err;
//	}
//}
//////////////////////////////////////////////////////////////////////////////
//void Admin::insert_At_in_progress_courses(int st_id, string in_p__courses)
//{
//	char* err;
//	sqlite3* db;
//	string s = in_p__courses;
//	int q = st_id;
//
//	sqlite3_stmt* stmt;
//	sqlite3_open("myDb.db", &db);
//	string query = "insert into COURSE_PROG(STUD_ID , COURE_IN_PROGRESS)VALUES('" + to_string(q) + "','" + s + "'); ";
//	cout << query << endl;
//	int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
//	if (rc != SQLITE_OK) {
//		cout << "errroooooorrrrr insert: " << err;
//	}
//}
////////////////////////////////////////////////////////////////////////////
//void Admin::add(int student__id, string first_name, string second_name, string third_name, string password, string academic_year)
//{
//	Student* n = new Student(student__id, first_name, second_name, third_name, password, academic_year);
//	if (size == 0) {
//		n->get_student_id() = student__id;
//		n->get_f_name() = first_name;
//		n->get_s_name() = second_name;
//		n->get_th_name() = third_name;
//		n->get_student_password() = password;
//		n->get_acadamic_year() = academic_year;
//
//		head = tail = n;
//
//		size++;
//		Admin::insert_At_Student(student__id, first_name, second_name, third_name, password, academic_year);
//	}
//	else {
//		n->get_student_id() = student__id;
//		n->get_f_name() = first_name;
//		n->get_s_name() = second_name;
//		n->get_th_name() = third_name;
//		n->get_student_password() = password;
//		n->get_acadamic_year() = academic_year;
//
//		tail->next = n;
//
//		tail = tail->next;
//		size++;
//		Admin::insert_At_Student(student__id, first_name, second_name, third_name, password, academic_year);
//	}
//}
//////////////////////////////////////////////////////////////////////////////
//void Admin::add_finished_courses(int Id, string  f_courses)
//{
//	Student* b = new Student();
//
//	if (size1 == 0) {
//		b->get_student_id() = Id;
//
//		b->get_finished_coursese() = f_courses;
//
//		head1 = tail1 = b;
//
//		size1++;
//	}
//	else {
//		b->get_student_id() = Id;
//
//		b->get_finished_coursese() = f_courses;
//
//		tail1->next1 = b;
//
//		tail1 = tail1->next1;
//		size1++;
//	}
//}
//////////////////////////////////////////////////////////////////////////////
//void Admin::add_in_progress_courses(int ID, string  in_p_courses)
//{
//	Student* z = new Student();
//
//	if (size2 == 0) {
//		z->get_student_id() = ID;
//
//		z->get_courses_in_progress() = in_p_courses;
//
//		head2 = tail2 = z;
//
//		size2++;
//	}
//	else {
//		z->get_student_id() = ID;
//
//		z->get_courses_in_progress() = in_p_courses;
//
//		tail2->next2 = z;
//
//		tail2 = tail2->next2;
//		size2++;
//	}
//}
//////////////////////////////////////////////////////////////////////////////
//string f__course;
//string in__p_course;
//void Admin::add_courses_only()
//{
//	cout << "enter stud id again " << endl;
//	int S_ID;
//	cin >> S_ID;
//	int num_of_finished_courses = 0;
//	int num_of_in_progress_courses = 0;
//	int press_for_course;
//
//	cout << "if the student has no finished courses press 2 else press 1  " << endl;
//	cin >> press_for_course;
//	switch (press_for_course) {
//	case 1:
//		cout << "enter the number of student  finished courses" << endl;
//		cin >> num_of_finished_courses;
//		for (int i = 0; i < num_of_finished_courses; i++) {
//			cout << "add  course " << endl;
//
//			cin >> f__course;
//			Admin::add_finished_courses(S_ID, f__course);
//			Admin::insert_At_finished_courses(S_ID, f__course);
//		}
//		cout << "enter the number of student  in progress courses" << endl;
//		cin >> num_of_in_progress_courses;
//		for (int i = 0; i < num_of_in_progress_courses; i++) {
//			cout << "add  course " << endl;
//
//			cin >> in__p_course;
//
//			Admin::add_in_progress_courses(S_ID, in__p_course);
//
//			Admin::insert_At_in_progress_courses(S_ID, in__p_course);
//		}
//		break;
//	case 2:
//		cout << "enter the number of student  in progress courses" << endl;
//		cin >> num_of_in_progress_courses;
//		for (int i = 0; i < num_of_in_progress_courses; i++) {
//			cout << "add  course " << endl;
//
//			cin >> in__p_course;
//
//			Admin::add_in_progress_courses(S_ID, in__p_course);
//			Admin::insert_At_in_progress_courses(S_ID, in__p_course);
//		}
//
//		break;
//	default:
//		cout << "invalid" << endl;
//		break;
//	}
//}
//////////////////////////////////////////////////////////////////////////////
//void Admin::Add_Student()
//{
//	int press_;
//	int s_ID;
//	string f_name1;
//	string s_name1;
//	string th_name1;
//	string password1;
//	string academic_year1;
//
//	cout << "if you want to add multiple students press 1 " << endl;
//	cout << "if you want to add one students press 2 " << endl;
//	cin >> press_;
//	if (press_ == 1) {
//		int num_of_students;
//		cout << "enter the number of stdent you want to add  " << endl;
//		cin >> num_of_students;
//		for (int i = 0; i < num_of_students; i++) {
//			cout << "enter the id of student" << endl;
//			cin >> s_ID;
//			cout << "enter student full name " << endl;
//			cin >> f_name1 >> s_name1 >> th_name1;
//			cout << "enter student password " << endl;
//			cin >> password1;
//			cout << "enter student acadamic_year " << endl;
//			cin >> academic_year1;
//
//			Admin::add(s_ID, f_name1, s_name1, th_name1, password1, academic_year1);
//		}
//	}
//	else if (press_ == 2) {
//		cout << "enter the id of student" << endl;
//		cin >> s_ID;
//		cout << "enter student full name " << endl;
//		cin >> f_name1 >> s_name1 >> th_name1;
//		cout << "enter student password " << endl;
//		cin >> password1;
//		cout << "enter student acadamic_year " << endl;
//		cin >> academic_year1;
//
//		Admin::add(s_ID, f_name1, s_name1, th_name1, password1, academic_year1);
//	}
//
//	else {
//		cout << "invaled number " << endl;
//	}
//}
//////////////////////////////////////////////////////////////////////////
void Admin::fillList()
{
	vector<string> preList_vec;
	int numOfPre;
	string preName;
	string crsCode;
	string cName;
	cout << "Enter course Code :\n";
	cin >> crsCode;
	transform(crsCode.begin(), crsCode.end(), crsCode.begin(), ::tolower);  // to change  string into lowercase

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

		preList_vec.push_back(preName);
	}
	insertData(crsCode, cName, preList_vec);
}
////////////////////////////////////////////////////////////////////////////
void Admin::insertData(string crscode, string cName, vector<string> preList_vec)
{
	char* err;
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("myDb.db", &db);
	for (int i = 0; i < preList_vec.size(); i++) {
		string query = "insert into COURSE_PREREQUISITE VALUES('" + preList_vec[i] + "','" + crscode + "','" + cName + "');";
		//cout << query << "\n";
		int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
		if (rc != SQLITE_OK) {
			cout << "insert error : " << err;
		}
	}

	sqlite3_close(db);
}
/// ////////////////////////////////////////////////////////////////////////
string Admin::get_admin_id()
{
	return to_string(id);
}
string Admin::get_fname()
{
	return  fname;
}
string Admin::get_lname()
{
	return lname;
}
string Admin::get_admin_pass()
{
	return password;
}
void Admin::set_admin_id(int idd)
{
	id = idd;
}
void Admin::set_fname(string fnam)
{
	fname = fnam;
}
void Admin::set_lname(string lnam)
{
	lname = lnam;
}
void Admin::set_admin_pass(string pas)
{
	password = pas;
}
Admin::~Admin() {}
//////////////////////////////////////////////////////////////////////////
void Admin::test() {
	DataBase::finished_vector.push_back(make_pair(45, "mohab"));
	cout << DataBase::finished_vector.size();
	for (auto x : DataBase::finished_vector)
		cout << x.second << endl;
}