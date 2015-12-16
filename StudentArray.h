#include "CourseList.h"

#ifndef INCLUDE_STUDENTARRAY
#define INCLUDE_STUDENTARRAY

struct StudentArray
{
	struct Student
	{
		Student(int id, CourseList *course_list);
		int id;
		CourseList *course_list;
		Student *next;
	};
	Student *head;
	StudentArray();
	void addStudent(int id, CourseList *course_list);
	void removeStudent(int id);
	void print();
	void printStudent(int id);
	void addClass(int id, string name, int section, int credits);
	//void dropClass(int id, string name);
};

#endif