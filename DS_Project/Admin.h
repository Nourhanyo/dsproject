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
	void Delete();
	void Edit();
	void Undo(string, string, int, int, string);

public:
	static bool ADMIN_CHANGED;
	static bool PRE_LIST_CHANGED;
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
	///////////////////////////////////////////////////////

	void fill_prerequisite_list();
	void test();

	
	~Admin();
	/////////////////////////////////////////////////////////////
	void Addcourse();
	void ModifyCourses();
	bool check_course_exist(string);
	bool check_cname_exist(string);
	bool check_ccode_exist(string);
	bool check_ccode2_exist(string,string);
	bool check_cname2_exist(string,string);



};
