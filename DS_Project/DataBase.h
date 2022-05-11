#pragma once
#include<iostream>
#include <unordered_map>
#include <string>
#include "Student.h"

using namespace std;

class DataBase
{
public:
	void load_DB();

	bool load_students_in_memory(std::unordered_map<std::string, Student>& students);
};

