#include "DataBase.h"
#include"sqlite/sqlite3.h"
#include <string>
#include<iostream>
#include <unordered_map>
#include <map>
using namespace std;

static sqlite3* DB{};
void DataBase::load_DB() {
    sqlite3_open("myDb.db", &DB);
    load_students_in_memory(studentss);
    load_courses_in_memory(coursess);
    load_Admins_in_memory(adminss);
    load_FinishedCourse_in_memory(finished_vector);
    load_ProgressedCourse_in_memory(progress_vector);
    sqlite3_close(DB);
}
/////////////////////////////////////////////////////////////////////////////////////////
bool DataBase::load_students_in_memory(std::map<std::string, Student>& students) // load student Data 
{
  
    sqlite3_stmt* result;
    // construct query
    string sql("SELECT * FROM STUDENT;");
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
        student.set_student_password(string(reinterpret_cast<const char*>(sqlite3_column_text(result, 4)))); // set student password
        student.set_acadamic_year(std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 5)))); // set student academic_year
    
  
        // load student to students hash tables
        students[id] = student;

        printf("Student: %s loaded successfully.\n", sqlite3_column_text(result, 1));
    }
    return true;
}
/////////////////////////////////////////////////////////////////////////////////////////
bool DataBase::load_courses_in_memory(std::map<std::string, Course>& courses) // load course data  
{
    sqlite3_stmt* result;
    // construct query
    string sql("SELECT * FROM COURSE;");
    // execute prepared query
    int exec = sqlite3_prepare_v2(DB, sql.c_str(), -1, &result, NULL);
    // check query status
    if (exec != SQLITE_OK) {
        std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
        return false;
    }

    while ((exec = sqlite3_step(result)) == SQLITE_ROW) {

        std::string code = std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 0)));

        // create course object  
        Course course ;

        course.set_code(code); // set code
        course.set_Course_Name(std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 1))));// set course name
       // course.set_hours(stoi(reinterpret_cast<const char*>(sqlite3_column_text(result, 2))));// set course hours
        //course.set_max_numstud(stoi(reinterpret_cast<const char*>(sqlite3_column_text(result, 3))));// set course max num of student
         
    
  
        // load student to students hash tables
        courses[code] = course;

        printf("Course: %s loaded successfully.\n", sqlite3_column_text(result, 1));
    }
    return true;
}
/////////////////////////////////////////////////////////////////////////////////////////
bool DataBase::load_Admins_in_memory(std::map<std::string, Admin>& admins) // load Admin Data 
{
  
    
    sqlite3_stmt* result;
    // construct query
    string sql("SELECT * FROM Admin;");
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
        Admin admin;

       admin.set_admin_id(stoi(id)); // set  admin id
       admin.set_fname(std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 1))));//set admin first name
       admin.set_lname(std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 2))));//set admin last name
       admin.set_admin_pass(std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 3))));// set admin  password
         
  
        // load student to students hash tables
        admins[id] = admin;

        printf("Admin: %s loaded successfully.\n", sqlite3_column_text(result, 1));
    }
 
    return true;
}
/////////////////////////////////////////////////////////////////////////////////////////
bool DataBase::load_FinishedCourse_in_memory(vector<pair<int, string>>& finished_vec) // load course data  
{
   
 
    sqlite3_stmt* result;
    // construct query
    string sql("SELECT * FROM COURSE_FINSHED ;");
    // execute prepared query
    int exec = sqlite3_prepare_v2(DB, sql.c_str(), -1, &result, NULL);
    // check query status
    if (exec != SQLITE_OK) {
        std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
        return false;
    }

    while ((exec = sqlite3_step(result)) == SQLITE_ROW) {
        int id_stud = stoi(reinterpret_cast<const char*>(sqlite3_column_text(result, 0)));

        string course_name=(std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 1))));
        finished_vec.push_back(make_pair(id_stud, course_name));


        printf("Finished Courses: %s loaded successfully.\n", sqlite3_column_text(result, 1));
    }
  
    return true;
}
/////////////////////////////////////////////////////////////////////////////////////////
bool DataBase::load_ProgressedCourse_in_memory(vector<pair<int, string>>& prog_vector) {
    int exit = 0;
    sqlite3* DB{};
    exit = sqlite3_open("myDb.db", &DB);
    sqlite3_stmt* result;
    // construct query
    string sql("SELECT * FROM COURSE_PROG ;");
    // execute prepared query
    int exec = sqlite3_prepare_v2(DB, sql.c_str(), -1, &result, NULL);
    // check query status
    if (exec != SQLITE_OK) {
        std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
        return false;
    }

    while ((exec = sqlite3_step(result)) == SQLITE_ROW) {
        int id_stud = stoi(reinterpret_cast<const char*>(sqlite3_column_text(result, 0)));

        string course_name = (std::string(reinterpret_cast<const char*>(sqlite3_column_text(result, 1))));
        prog_vector.push_back(make_pair(id_stud, course_name));


        printf("Progressed Courses: %s loaded successfully.\n", sqlite3_column_text(result, 1));
    }
    sqlite3_close(DB);
    return true;






}
/////////////////////////////////////////////////////////////////////////////////////////
 //void DataBase::update_DB(){









 //}
 //void DataBase::update_Student() {

 //   sqlite3_stmt* result;
 //   // construct query
 //   string sql("SELECT * FROM STUDENT;");
 //   // execute prepared query
 //   int exec = sqlite3_prepare_v2(DB, sql.c_str(), -1, &result, NULL);
 //   // check query status
 //   if (exec != SQLITE_OK) {
 //       std::cerr << "Error:  " << sqlite3_errmsg(DB) << std::endl;
 //       
 //   }





 //}