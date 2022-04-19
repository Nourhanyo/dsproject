#include "Student.h"
#include"sqlite/sqlite3.h"
int Student::id = 0;/*for static variable (id)*/
Student::Student(string fnam, string snam, string thnam, int pass, int aca) {
	f_name = fnam;
	s_name = snam;
	th_name = thnam;
	password = pass;
	acadamic_year = aca;
	id++;
}
/////////////////////////////////

////////////////////////////////
Student ::~Student() {}