#pragma once
#include<iostream>
using namespace std;

class Menu
{
private:
	
	bool Check_Stud_Data(string password);
	bool Check_Admin_Data(string password);
public:
	static string name;
	static string name2;
	static string name3;
	static int id;
	void login();
	void adminmenu(string);
	void studmenu(string);
};



 
