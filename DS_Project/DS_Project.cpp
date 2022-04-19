#include <iostream>
#include"sqlite/sqlite3.h"
#include<string>
using namespace std;
//void creat_DB();

int main()
{
   /* creat_DB();*/
    cout << "hoba";
    return 0;
}
//void creat_DB() {
//    char* err;
//    sqlite3* db;
//    sqlite3_stmt* stmt;
//    sqlite3_open("myDb.db", &db);
//    int rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS ADMIN(ID INTEGER PRIMARY KEY AUTOINCREMENT,F_NAME varchar(25) NOT NULL, L_NAME varchar(25) NOT NULL, PASSWORD INT NOT NULL);", NULL, NULL, &err);
//    if (rc != SQLITE_OK) {
//        cout << "errroooooorrrrr admin: " << err;
//    }
//    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS STUDENT(ID INTEGER PRIMARY KEY AUTOINCREMENT,F_NAME varchar(25) NOT NULL, S_NAME varchar(25) NOT NULL,TH_NAME varchar(25) NOT NULL, PASSWORD INT NOT NULL, ACADEMIC_YEAR INT NOT NULL);", NULL, NULL, &err);
//    if (rc != SQLITE_OK) {
//        cout << "errroooooorrrrr stud: " << err;
//    }
//    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS COURSE(CODE varchar(25) PRIMARY KEY ,NAME varchar(50) NOT NULL, HOURS INT NOT NULL,MAX_NUM_STUD INT NOT NULL);", NULL, NULL, &err);
//    if (rc != SQLITE_OK) {
//        cout << "errroooooorrrrr course: " << err;
//    }
//    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS COURSE_PREREQUISITE(preq varchar(50) NOT NULL,COURSE_CODE varchar(25), CONSTRAINT fk_COURSE FOREIGN KEY (COURSE_CODE) REFERENCES COURSE(CODE) );", NULL, NULL, &err);
//    if (rc != SQLITE_OK) {
//        cout << "errroooooorrrrr course preeeeeee: " << err;
//    }
//    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS COURSE_FOR_STUD(COURSE_CODE varchar(25),STUD_ID INTEGER, FOREIGN KEY (COURSE_CODE) REFERENCES COURSE(CODE),FOREIGN KEY (STUD_ID) REFERENCES STUDENT(ID) );", NULL, NULL, &err);
//    if (rc != SQLITE_OK) {
//        cout << "errroooooorrrrr course CODE....ID: " << err;
//    }
//    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS COURSE_PROG(STUD_ID INTEGER,COURE_IN_PROGRESS varchar(50) ,FOREIGN KEY (STUD_ID) REFERENCES STUDENT(ID) );", NULL, NULL, &err);
//    if (rc != SQLITE_OK) {
//        cout << "errroooooorrrrr course CODE PROGRESS: " << err;
//    }
//    rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS COURSE_FINSHED(STUD_ID INTEGER,COURE_FINISHED varchar(50) ,FOREIGN KEY (STUD_ID) REFERENCES STUDENT(ID) );", NULL, NULL, &err);
//    if (rc != SQLITE_OK) {
//        cout << "errroooooorrrrr course CODE PROGRESS: " << err;
//    }
// 
//    
//}


/*for insert data 
example:
 char* err;
    sqlite3* db;
    sqlite3_stmt* stmt;
    sqlite3_open("myDb.db", &db);
    string query = "insert into COURSE VALUES('a5','DS',3,300);";
    cout << query << endl;
   int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
    if (rc != SQLITE_OK) {
        cout << "errroooooorrrrr insert: " << err;
    }
*/
