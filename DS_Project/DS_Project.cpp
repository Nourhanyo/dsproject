#include <iostream>
#include"sqlite/sqlite3.h"
#include<string>
#include"Admin.h"
#include "Student.h"
#include"Course.h"
#include "DataBase.h"
#include "Menu.h"
using namespace std;
int main() {
	DataBase d;
	d.load_DB();
	Menu m;
	m.login();
	d.update_DB();
	return 0;
}