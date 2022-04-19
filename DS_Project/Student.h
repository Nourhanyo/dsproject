#include <iostream>
#include"sqlite/sqlite3.h"
using namespace std;
class Student
{
private:
	static int id;
	string f_name;
	string s_name;
	string th_name;
	int password;
	int acadamic_year;
public:
	Student(string, string, string, int, int);
	~Student();

};

