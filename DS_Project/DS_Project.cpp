#include <iostream>
#include"sqlite/sqlite3.h"
#include<string>
#include"Admin.h"
#include "Student.h"
#include <iostream>
#include "Menu.h"
#include "DataBase.h"
using namespace std; 


using namespace std;
int main() {

	DataBase a;
	a.load_DB();
	for (auto x : a.studentss)
		cout << x.first << " " << x.second.get_f_name() << endl;
	for (auto x : a.coursess)
		cout << x.first << " " << x.second.get_Course_name() << endl;
	for (auto x : a.adminss)
		cout << x.first << " " << x.second.get_fname() << endl;
}