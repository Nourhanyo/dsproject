#include <iostream>
#include "Admin.h"
#include "database_class.h"
#include"sqlite/sqlite3.h"
#include<string>
using namespace std;
//void creat_DB();
int main()
{
    database_class c;
       c.creat_DB();
 //  const char* dir = "C:\\Users\\Dell\\Downloads\\ds_project\\DS_Project\\myDb.db";
    int press;
    bool flag = true;

    Admin add_student;
    Student stud;
    cout << "If you want to add student data press 1 " << endl;
    cout << "If you want to edit student data press 2 " << endl;
    cout << "If you want to exit press 3 " << endl;
    while (flag) {
       

        cin >> press;
        switch (press) {

        case 1:
            add_student.Add_Student();
            break;
        case 2:
            stud.Edit_Stud_data();

            break;
        case 3:

            flag = false;
            break;

     

        default:


            cout << " wrong choice " << endl;
            break;





        }












    }



    return 0;
}

