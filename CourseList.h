#include <string>
#include <iostream>
using namespace std;

#ifndef INCLUDE_COURSELIST
#define INCLUDE_COURSELIST

struct CourseList
{
	struct Course
	{
		Course(string name, int section, int credits);
		string name;
		int section;
		int credits;	
		Course *left;
		Course *right;
	};
	Course *root;
	CourseList();
	void addCourse(string name, int section, int credits);
	void addCourse(string name, int section, int credits, Course *leaf);
	//void dropCourse(string name, Course *leaf);
	void print();
	void print(Course *ptr);
};

#endif