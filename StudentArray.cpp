#include "StudentArray.h"

StudentArray::Student::Student(int id, CourseList *course_list)
{
	this->id = id;
	this->course_list = course_list;
}

StudentArray::StudentArray()
{
	this->head = nullptr;
}

void StudentArray::addStudent(int id, CourseList *course_list)
{
	Student *ptr = head;

	cout<<"Adding new student to the ";
	
	if(ptr == nullptr) //if this is the first and only item, then make it the head
	{
			cout<<"front."<<endl;
			Student *new_student = new Student(id, course_list);
			new_student->next = nullptr;
			head = new_student;
			return;
	} 
	else
	while(ptr)
	{
		if(ptr->next == nullptr) //or if it needs to be appended at the very end
		{
			cout<<"end."<<endl;
			Student *new_student = new Student(id, course_list);
			ptr->next = new_student;
			new_student->next = nullptr;
			return;
		}
		
		if(id > ptr->id && id <= ptr->next->id) //insert somewhere in the middle, in order
		{
			cout<<"middle."<<endl;
			Student *new_student = new Student(id, course_list);
			new_student->next = ptr->next;
			ptr->next = new_student;
			return;
		}
		
		ptr = ptr->next;
	}
}

void StudentArray::removeStudent(int id)
{
	Student *ptr = head;
	Student *follow = nullptr;
	if(id == ptr->id)
	{
		head = ptr->next;
		ptr->next = nullptr;
		delete ptr;
		return;
	}
	while(ptr->next)
	{
		follow = ptr;
		ptr = ptr->next;
		if(id == ptr->id)
		{
			follow->next = ptr->next;
			ptr->next = nullptr;
			delete ptr;
			return;
		}
	}
}

void StudentArray::print()
{
	Student *ptr = head;
	cout<<"Student data:"<<endl;
	while(ptr)
	{
		cout<<"Student: "<<ptr->id<<endl;
		ptr->course_list->print();
		ptr = ptr->next;
	}
}

void StudentArray::printStudent(int id)
{
	Student *ptr = head;
	cout<<"Student data:"<<endl;
	while(ptr->id != id)
		ptr=ptr->next;
	ptr->course_list->print();
}

void StudentArray::addClass(int id, string name, int section, int credits)
{
	Student *ptr = head;
	while(ptr->id != id)
		ptr=ptr->next;
	ptr->course_list->addCourse(name, section, credits);
}

/*void StudentArray::dropClass(int id, string name)
{
	Student *ptr = head;
	while(ptr->id != id)
		ptr=ptr->next;
	ptr->course_list->dropCourse(name);
}*/