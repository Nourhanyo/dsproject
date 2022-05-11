#pragma once
#include<iostream>
#include <unordered_map>
#include <string>
#include "Student.h"
#include "Course.h"
#include "Admin.h"
#include <map>
#include <vector>

using namespace std;

class DataBase
{
public:
	map<string, Student> studentss;
	map<string, Course> coursess;
	map<string, Admin> adminss;
	vector<pair<int, string>> finished_vector;
	vector<pair<int, string>> progress_vector;
	vector<pair<int, string>> COURSE_PREREQUISITE;
	void load_DB();
	bool load_students_in_memory(std::map<std::string, Student>& students);
	bool load_courses_in_memory(std::map<std::string, Course>& courses);
	bool load_Admins_in_memory(std::map<std::string, Admin>& admins);
	bool load_FinishedCourse_in_memory(vector<pair<int, string>>& finished_vec);
	bool load_ProgressedCourse_in_memory(vector<pair<int, string>>& prog_vector);
	void update_DB();
	void update_Student();
};

