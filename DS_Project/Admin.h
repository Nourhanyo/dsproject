#pragma once
#include "Student.h"
#include<vector>
#include <iostream>
#include"Course.h"

using namespace std;

class Admin
{
private:
	static int id;
	string fname;
	string lname;
	string password;
public:
	Admin();
	Admin(string Fnam, string lName, string pass);
	string get_admin_id();
	string get_fname();
	string get_lname();
	string get_admin_pass();
	/////////////////////////////////////////////////////////////
	void set_admin_id(int);
	void set_fname(string);
	void set_lname(string);
	void set_admin_pass(string);
	static bool ADMIN_CHANGED;
	void test();
	~Admin();
};
