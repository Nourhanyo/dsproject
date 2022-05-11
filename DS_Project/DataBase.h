#pragma once
#include<iostream>
#include <unordered_map>
#include <string>
#include "Student.h"
#include "Course.h"
#include "Admin.h"
#include <unordered_map>

using namespace std;

class DataBase
{
public:
	unordered_map<string, Student> studentss;
	unordered_map<string, Course> coursess;
	unordered_map<string, Admin> adminss;
	void load_DB();
	bool load_students_in_memory(std::unordered_map<std::string, Student>& students);
	bool load_courses_in_memory(std::unordered_map<std::string, Course>& courses);
	bool load_Admins_in_memory(std::unordered_map<std::string, Admin>& admins);
	//bool load_FinishedCourse_in_memory(std::unordered_map<std::string, Admin>& admins)
};

