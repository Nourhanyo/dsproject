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
	a.update_DB();
	return 0;
}