#pragma once
#include"sqlite/sqlite3.h"
#include<string>
#include <iostream>
using namespace std;

class database_class
{
public :
	database_class();
	void creat_DB();
	void insert_At_Student(string, string, string, int, int);
	//void modify();
};

