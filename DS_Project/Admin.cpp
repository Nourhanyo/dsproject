#include "Admin.h"
#include "database_class.h"
#include"sqlite/sqlite3.h"

int Admin::id = 0;/*for static variable (id)*/
Admin::Admin(string nam, string pass) {
	id++;
	name = nam;
	password = pass;
	
}




Admin::Admin()
{
}

void Admin::append(string first_name, string second_name, string third_name, int password, int academic_year)
{
	Student* n = new Student(first_name, second_name, third_name, password, academic_year);

	if (size == 0) {
		
		head = tail = n;

		size++;


	}
	else {
		
		tail->next = n;

		tail = tail->next;
		size++;

	}
}


void Admin::display()

{


	Student* tmp;
	tmp = head;
	while (tmp != NULL)
	{

		cout << tmp->get_f_name() << " " << tmp->get_s_name() << " " << tmp->get_th_name() << endl;
		cout << tmp->get_student_id() << endl;
		cout << tmp->get_acadamic_year() << endl;


		tmp = tmp->next;




	}





}

void Admin::Add_Student()
{
	int press_;
	string f_name1;
	string s_name1;
	string th_name1;
	int password1;
	int acadamic_year1;
	int press;
	database_class insert_stud;
	cout << " if you want to add multiple students press 1 " << endl;
	cout << " if you want to add one students press 2 " << endl;
	cin >> press_;
	if (press_ == 1) {

		int num_of_students;
		cout << " enter the number of stdent you want to add  " << endl;
		cin >> num_of_students;
		for (int i = 0; i < num_of_students; i++) {
			cout << " enter student name " << endl;
			cin >> f_name1 >> s_name1 >> th_name1;
			cout << " enter student password " << endl;
			cin >> password1;
			cout << " enter student acadamic_year " << endl;
			cin >> acadamic_year1;

			Admin::append(f_name1, s_name1, th_name1, password1, acadamic_year1);
			insert_stud.insert_At_Student(f_name1, s_name1, th_name1, password1, acadamic_year1);


		}



	}
	else if (press_ == 2) {

		cout << " enter student name " << endl;
		cin >> f_name1 >> s_name1 >> th_name1;
		cout << " enter student password " << endl;
		cin >> password1;
		cout << " enter student acadamic_year " << endl;
		cin >> acadamic_year1;

		Admin::append(f_name1, s_name1, th_name1, password1, acadamic_year1);

		insert_stud.insert_At_Student(f_name1, s_name1, th_name1, password1, acadamic_year1);




	}
	else {
		cout << " invaled number " << endl;
	}
}
Admin::~Admin() {}

