#include<iostream>
#include "Student.h"
#include "Admin.h"
#include "sqlite/sqlite3.h"
#include<string>
 /*int Student :: callback(void* data, int argc, char** argv, char** azColName)
{
	//int i;
	fprintf(stderr, "%s: ", (const char*)data);

	Student* stud = new Student;

	stud->get_f_name() = argv[0];
	stud->get_s_name() = argv[1];
	stud->get_th_name() = argv[2];
	stud->get_student_password() = argv[3];
	stud->get_acadamic_year() = argv[4];
	stud->get_courses_in_progress() = argv[5];
	stud->get_finished_coursese() = argv[6];
	

	printf("\n");
	return 0;
}
*/
int Student::id = 0;/*for static variable (id)*/
Student::Student(string fnam, string snam, string thnam , int pass, int aca) {
	f_name = fnam;
	s_name = snam;
	th_name = thnam;
	password = pass;
	id++;
	next = NULL;

}



Student::Student()
{
	
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

/*void Student::Edit_Stud_data()
{
	int My_id = 0;
	int My_password;
	cout << "enter id" << endl;
	cin >> My_id;
	cout << "enter new password" << endl;
	cin >> My_password;

	sqlite3* db;
	char* zErrMsg = 0;
	string sql;
	const char* data = "Callback function called";

	/* Open database */
	//sqlite3_open("myDb.db", &db);

	
	/* Create merged SQL statement */
	//sql = "UPDATE STUDENT set PASSWORD = 'My_password' where ID='My_id'   ; " 
	//	"SELECT * from STUDENT";

	/* Execute SQL statement */
	/*int rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);

	if(rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
 else {
 fprintf(stdout, "Operation done successfully\n");
   }
	
}
*/

/*int Student::select_data()
{
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open("myDb.db", &db);
	int My_id = 0;
	int My_password;
	cout << "enter your Id and password  to edit your data" << endl;
	cin >> My_id >> My_password;
	string query1 = "select * from STUDENT where ID =My_id AND PASSWORD =  My_password ";

	int My_id = 0;
	int My_password;
	cout << "enter your Id and password  to edit your data" << endl;
	cin >> My_id;
	/*char* messageError;
	sqlite3* db;
	string sql = "SELECT * FROM STUDENT ;";

	int exist = sqlite3_open(s, &db);

	exist = sqlite3_exec(db, sql.c_str(), callback, NULL, &messageError);

	if (exit != SQLITE_OK) {
		cerr << "Error in selectData function." << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Records selected Successfully!" << endl;

	return 0;
	
}
*/
/*int Student::callback(void* data, int argc, char** argv, char** azColName)
{

		int i;

		fprintf(stderr, "%s: ", (const char*)data);

		for (i = 0; i < argc; i++) {
			printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		}

		printf("\n");
	
	return 0;
}
*/
/*int Student::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++) {
		// column name and value
		cout << azColName[i] << ": " << argv[i] << endl;
	}

	cout << endl;

	return 0;
}

*/

Student ::~Student() {
}

