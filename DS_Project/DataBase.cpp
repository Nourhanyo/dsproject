#include "DataBase.h"
#include"sqlite/sqlite3.h"
#include <string>
#include<iostream>
#include "Course.h"
#include "Student.h"
#include "Admin.h"
#include <unordered_map>

using namespace std;

unordered_map<string, Student> studentss;
void DataBase:: load_DB() {

	load_students_in_memory(studentss);
	for (auto x : studentss)
		cout << x.first << " " << x.second.get_f_name() << endl;
	cout << "ASad";

}
///////////////////////////////////////////////
bool DataBase::load_students_in_memory(std::unordered_map<std::string, Student>& students)
{
	sqlite3* DB{};
	sqlite3_open("myDb.db", &DB);
	sqlite3_stmt* result;
	// construct query
	std::string sql("SELECT * FROM STUDENT;");
	std::cout << "Query: " << sql << std::endl;
	// execute prepared query
	int exec = sqlite3_prepare_v2(DB, sql.c_str(), -1, &result, NULL);

	// check query status
	if (exec != SQLITE_OK) {
		std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
		return false;
	}

	while ((exec = sqlite3_step(result)) == SQLITE_ROW) {

		std::string id = std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 0)));

		// create student object  
		Student student;

		student.set_student_id(stoi(id)); // set id
		student.set_f_name(std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 1))));
		student.set_s_name(std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 2))));
		student.set_th_name(std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 3))));// set student name
		student.set_student_password(std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 4)))); // set student password
		student.set_acadamic_year(std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 5)))); // set student academic_year
		int s;
		s = sqlite3_column_int(result, 0);
		cout << s << endl;
		//// load courses
		//load_student_courses(id, student.finished_courses, student.courses_in_progress);

		// load student to students hash tables
		students[id] = student;

		printf("Student: %s loaded successfully.\n", sqlite3_column_text(result, 1));
	}
	sqlite3_close(DB);
	return true;
}
///////////////////////////////////////////////
//void DataBase::load_admin()
//{
//	sqlite3* DB{};
//	string sql;
//	sql = ("SELECT * FROM ADMIN");
//	int rc = sqlite3_exec(DB, sql.c_str(), callback_admin, NULL, NULL);
//}
//int DataBase::callback_admin(void* data, int argc, char** argv, char** azColName)
//{
//	for (int i = 0; i < argc; i++) {
//		Admin admin;
//		 admin.set_admin_id(stoi(argv[0])) ;
//		 admin.set_fname(argv[1])  ;
//		 admin.set_lname(argv[2]) ;
//		 admin.set_admin_pass(argv[3])  ;
// 		 admins.push_back(admin); 
//	} 
//	return 0;
//}
/////////////////////////////////////////////////
//void DataBase::load_course()
//{
//	sqlite3* DB{};
//	string sql;
//	sql = ("SELECT * FROM COURSE");
//	int rc = sqlite3_exec(DB, sql.c_str(), callback_course, NULL, NULL);
//}
//int DataBase::callback_course(void* data, int argc, char** argv, char** azColName)
//{
//	for (int i = 0; i < argc; i++) {
//		Course course;
//		course.set_code(argv[0]) ;
//		course.set_Course_Name(argv[1]) ;
//		course.set_hours(stoi(argv[2]));
//		course.set_max_numstud(stoi(argv[3]));
// 		courses.push_back(course);
//	} 
//	return 0;
//}
/////////////////////////////////////////////////
//
//
