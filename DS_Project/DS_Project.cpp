#include <iostream>
#include "Admin.h"
#include"sqlite/sqlite3.h"
#include<string>
using namespace std;
void creat_DB();
int main()
{
   creat_DB();

    int press;
    bool flag = true;

    Admin add_student;
    cout << "If you want to add student data press 1 " << endl;
    cout << "If you want to display student data press 2 " << endl;
    cout << "If you want to edit student data press 3 " << endl;
    cout << "If you want to exit press 4 " << endl;
    while (flag) {
       

        cin >> press;
        switch (press) {

        case 1:
            add_student.Add_Student();
            break;
        case 2:


            add_student.display();
            break;
        case 3:


            break;

        case 4:
            
            flag = false;
            break;

        default:


            cout << " wrong choice " << endl;
            break;





        }












    }



    return 0;
}
void creat_DB() {
char* err;
sqlite3* db;
sqlite3_stmt* stmt;
sqlite3_open("myDb.db", &db);
int rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS ADMIN(ID INTEGER PRIMARY KEY AUTOINCREMENT,F_NAME varchar(25) NOT NULL, L_NAME varchar(25) NOT NULL, PASSWORD INT NOT NULL);", NULL, NULL, &err);
if (rc != SQLITE_OK) {
    cout << "errroooooorrrrr admin: " << err;
}
rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS STUDENT(ID INTEGER PRIMARY KEY AUTOINCREMENT,F_NAME varchar(25) NOT NULL, S_NAME varchar(25) NOT NULL,TH_NAME varchar(25) NOT NULL, PASSWORD INT NOT NULL, ACADEMIC_YEAR INT NOT NULL);", NULL, NULL, &err);
if (rc != SQLITE_OK) {
    cout << "errroooooorrrrr stud: " << err;
}
rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS COURSE(CODE varchar(25) PRIMARY KEY ,NAME varchar(50) NOT NULL, HOURS INT NOT NULL,MAX_NUM_STUD INT NOT NULL);", NULL, NULL, &err);
if (rc != SQLITE_OK) {
    cout << "errroooooorrrrr course: " << err;
}
rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS COURSE_PREREQUISITE(preq varchar(50) NOT NULL,COURSE_CODE varchar(25), CONSTRAINT fk_COURSE FOREIGN KEY (COURSE_CODE) REFERENCES COURSE(CODE) );", NULL, NULL, &err);
if (rc != SQLITE_OK) {
    cout << "errroooooorrrrr course preeeeeee: " << err;
}
rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS COURSE_FOR_STUD(COURSE_CODE varchar(25),STUD_ID INTEGER, FOREIGN KEY (COURSE_CODE) REFERENCES COURSE(CODE),FOREIGN KEY (STUD_ID) REFERENCES STUDENT(ID) );", NULL, NULL, &err);
if (rc != SQLITE_OK) {
    cout << "errroooooorrrrr course CODE....ID: " << err;
}
rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS COURSE_PROG(STUD_ID INTEGER,COURE_IN_PROGRESS varchar(50) ,FOREIGN KEY (STUD_ID) REFERENCES STUDENT(ID) );", NULL, NULL, &err);
if (rc != SQLITE_OK) {
    cout << "errroooooorrrrr course CODE PROGRESS: " << err;
}
rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS COURSE_FINSHED(STUD_ID INTEGER,COURE_FINISHED varchar(50) ,FOREIGN KEY (STUD_ID) REFERENCES STUDENT(ID) );", NULL, NULL, &err);
if (rc != SQLITE_OK) {
    cout << "errroooooorrrrr course CODE PROGRESS: " << err;
}




}

