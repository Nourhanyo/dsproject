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
	int press;
    bool flag = true;
	DataBase d;
	d.load_DB();
	Student s;
	Admin ad;
   

    while (flag) {

        cout << "If you want to add student data press 1 " << endl;
        cout << "If you want to add student  finished and in  progress course  press 2 " << endl;
        cin >> press;
        switch (press) {

        case 1:
            ad.add_stud();
            break;
        case 2:
            s.edit_stud_data();
           // ad.add_f_course_in_p_course();
            break;
        case 3:


            flag = false;
            break;
            system("pause");

        default:


            cout << " wrong choice " << endl;
            break;




        }
    }
	
	//ad.ModifyCourses();
	//s.view_available_courses();
	d.update_DB();
	return 0;
}