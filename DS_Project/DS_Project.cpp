#include <iostream>
#include"sqlite/sqlite3.h"
#include<string>
#include"Admin.h"
#include "Student.h"
#include <iostream>
#include "Course.h"
#include "Menu.h"
#include "DataBase.h"
using namespace std; 


using namespace std;
int main() {

	DataBase a;
	a.load_DB();


}
	//map< string, vector<string> > Employees;
	//vector <string> myVec;
	//string val1, val2, val3;
	//val1 = "sohyb";
	//val2 = "valor2";
	//val3 = "valor3";



	//// 4) Assignment using member function insert() and "make_pair()"
	//myVec.push_back("mohab");
	//myVec.push_back(val1);
	//myVec.push_back("hoba");
	//Employees.insert(std::make_pair("mohamed5555 Q.", myVec));
	//myVec.clear();
	//myVec.push_back("aa");
	//myVec.push_back(val1);
	//myVec.push_back("hobssa");
	//Employees.insert(std::make_pair("mohamed5555 Q.", myVec));

	//cout << "Map size: " << Employees.size() << endl;
	//for (auto ii = Employees.begin(); ii != Employees.end(); ++ii) {
	//	cout << (*ii).first << ": ";
	//	vector <string> inVect = (*ii).second;
	//	for (unsigned j = 0; j < inVect.size(); j++) {
	//		cout << inVect[j] << " ";
	//	}
	//	cout << endl;
	//}
