#pragma once
#include "student.h"
#include <iostream>
using namespace std;

class Linked_list
{
private:

	int size;
	Student* head;
	Student* tail;

public:
	Linked_list();

	void append(string, string, string, int, int);
	void display();
	~Linked_list();

};


