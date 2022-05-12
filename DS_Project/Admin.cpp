#include "Admin.h"
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <stack>
#include <string>
#include"sqlite/sqlite3.h"
#include"DataBase.h"
sqlite3* dd;
bool Admin::ADMIN_CHANGED = false;
int Admin::id = 0; /*for static variable (id)*/
Admin::Admin(string Fnam, string lName, string pass) {
	id++;
	get_fname() = Fnam;
	get_lname() = lName;
	password = pass;
}
Admin::Admin() {
}
////////////////////////////////////////////////////////////////////////////
string Admin::get_admin_id()
{
	return to_string(id);
}
string Admin::get_fname()
{
	return  fname;
}
string Admin::get_lname()
{
	return lname;
}
string Admin::get_admin_pass()
{
	return password;
}
////////////////////////////////////////////////////////////////////////////
void Admin::set_admin_id(int idd)
{
	id = idd;
}
void Admin::set_fname(string fnam)
{
	fname = fnam;
}
void Admin::set_lname(string lnam)
{
	lname = lnam;
}
void Admin::set_admin_pass(string pas)
{
	password = pas;
}
Admin::~Admin() {}
//////////////////////////////////////////////////////////////////////////
void Admin::test() {
	DataBase::finished_vector.push_back(make_pair(45, "mohab"));
	cout << DataBase::finished_vector.size();
	for (auto x : DataBase::finished_vector)
		cout << x.second << endl;
}