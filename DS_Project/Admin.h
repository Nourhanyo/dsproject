#pragma once
#include "Student.h"
#include <iostream>
using namespace std;

class Admin
{
private:
	static int id;
	
	string name;
	string password;
	int size = 0;

	Student* head = NULL;
	Student* tail = NULL;

public:
	Admin();
	void append(string, string, string, int, int);
	void display();
	void Add_Student();
	Admin(string , string);
	~Admin();

};


