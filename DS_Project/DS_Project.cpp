#include <iostream>
#include"sqlite/sqlite3.h"
#include<string>
#include"Admin.h"
#include "Student.h"
#include"Course.h"
#include "DataBase.h"

using namespace std;

using namespace std;
int main() {
	DataBase d;
	d.load_DB();
	Student s;
	Admin ad;
	ad.add_stud();
	//ad.ModifyCourses();
	//s.view_available_courses();
	d.update_DB();
	return 0;
}