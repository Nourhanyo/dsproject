#include <iostream>
#include <stack>
#include"sqlite/sqlite3.h"
using namespace std;
class Course
{
private:
	
	string name;
	string code;
	int max_numstud;
	int hours;
public:
	Course(string, string, int, int);
	~Course();



	string get_Cname() {

		return name;
	}
	int get_max_numstud() {

		return max_numstud;
	
	}string get_code() {

		return code;
	}int get_Chours() {

		return hours;
	}

};

