#include "Finished__course.h"

int  Finished__course::get_student_id_() {
	return   stud_id;
}

Finished__course::Finished__course() {
	stud_id = 0;
	finished_course = "";
}
Finished__course::Finished__course(int id , string finished_course_ ) {
	stud_id = id; 
	finished_course = finished_course_; 
}

string Finished__course::get_finished_course()
{
	return finished_course;
}

void  Finished__course::set_student_id_( int id )
{
	stud_id = id;
}

void Finished__course::set_finished_course(string f_course)
{
	finished_course = f_course;

}
