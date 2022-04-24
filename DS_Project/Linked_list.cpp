#include "Linked_list.h"
#include "Student.h"
#include"sqlite/sqlite3.h"

Linked_list::Linked_list()
{
}

Linked_list::Linked_list()
{
	head = NULL;
	tail = NULL;
	size = 0;


}

void Linked_list::append(string first_name, string second_name, string third_name, int password, int academic_year)
{
	Student* n = new Student(first_name, second_name, third_name, password, academic_year);

	if (size == 0) {
		/*	n->get_f_name() = first_name;
			n->get_s_name() = second_name;
			n->get_th_name() = third_name;
			n->get_student_password() = password;
			n->get_acadamic_year() = academic_year;
			*/
		head = tail = n;

		size++;


	}
	else {
		/*	n->get_f_name() = first_name;
			n->get_s_name() = second_name;
			n->get_th_name() = third_name;
			n->get_student_password() = password;
			n->get_acadamic_year() = academic_year;

			*/
		tail->next = n;

		tail = tail->next;
		size++;

	}
}


void Linked_list::display()

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

Linked_list::~Linked_list()
{
}