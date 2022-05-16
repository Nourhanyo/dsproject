#pragma once
#include<iostream>
using namespace std;

class Menu
{
private:
	void adminmenu(string);
	void studmenu(string);
	bool Check_Stud_Data(string id, string password);
	bool Check_Admin_Data(string name, string password);
public:
	void login();
};



 
