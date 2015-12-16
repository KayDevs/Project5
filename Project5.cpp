#include "CourseList.h"
#include "StudentArray.h"
#include <iostream>
#include <fstream>


enum commands 
{
	ADDSTUDENT,
	REMOVESTUDENT,
	LOADFILE,
	SAVEFILE,
	ADDCLASS,
	//DROPCLASS,
	DISPLAY,
	DISPLAYSTUDENT,
	HELP,
	QUIT
};
commands hash_commands(string input)
{
	if(input == "addstudent") return ADDSTUDENT;
	if(input == "removestudent") return REMOVESTUDENT;
	if(input == "loadfile") return LOADFILE;
	if(input == "savefile") return SAVEFILE;
	if(input == "addclass") return ADDCLASS;
	//if(input == "dropclass") return DROPCLASS;
	if(input == "display") return DISPLAY;
	if(input == "displaystudent") return DISPLAYSTUDENT;
	if(input == "help") return HELP;
	if(input == "quit") return QUIT;
}


void addSum(CourseList::Course *ptr, int &sum)
{
	if(ptr)
	{
		sum++;
		if(ptr->left)
		{
			addSum(ptr->left, sum);
		}
		if(ptr->right)
		{
			addSum(ptr->right, sum);	
		}
	}
}

void writeATree(CourseList::Course *ptr, fstream &file)
{
		if(ptr)
		{
    	file<<ptr->name<<endl;
    	file<<ptr->section<<endl;
    	file<<ptr->credits<<endl;
			if(ptr->left)
			{
				writeATree(ptr->left, file);
			}
			if(ptr->right)
			{
				writeATree(ptr->right, file);	
			}
		}
}


int main(int argc, char** argv)
{
	StudentArray *student_array = new StudentArray();
	
	ifstream datafile("datafile.txt");
	int id;
	while(datafile>>id)
	{
		CourseList *course_list = new CourseList();
		int counter;
		datafile>>counter;
		//cout<<"Student "<<id<<" has "<<counter<<" classes."<<endl;
		for(int i = 0; i < counter; ++i)
		{
			string name;
			int section;
			int credits;
			
			//get both halves of a course name
			string course, number;
			datafile>>course;
			datafile>>number;
			name=course+" "+number;
			
			datafile>>section;
			datafile>>credits;
			course_list->addCourse(name, section, credits);
			// cout<<name<<endl;
			// cout<<section<<endl;
			// cout<<credits<<endl;
		}
		cout<<"Adding course list to student "<<id<<"."<<endl;
		student_array->addStudent(id, course_list);
	}
	
	datafile.close();
	
	cout<<"Data from file: "<<endl;
	student_array->print();
	
	//enter command loop
	string command;
	cout<<"What would you like to do? (type help for a list of options)"<<endl;
	do
	{
		cout<<">";
		cin>>command;
		cin.ignore();
		cout<<endl;
		
		int id; //reusable
		
		switch(hash_commands(command)) {
		case HELP:
			cout<<"List of available commands:"<<endl;
			cout<<"addstudent     - add a student to the database"<<endl;
			cout<<"removestudent  - removes a student from the database"<<endl;
			cout<<"loadfile       - load a file containing students and course lists"<<endl;
			cout<<"savefile       - save the records to a file"<<endl;
			cout<<"addclass       - add a class to a student's list"<<endl;
			//cout<<"dropclass      - remove a class from a student's list"<<endl;
			cout<<"display        - display information about all students"<<endl;
			cout<<"displaystudent - display information about a single student"<<endl;
			cout<<"help           - show help"<<endl;
			cout<<"quit           - exit the program"<<endl;
			break;
		case DISPLAYSTUDENT:
			cout<<"What is the id of the student you would like to view?"<<endl;
			cin>>id;
			student_array->printStudent(id);
			break;
		case DISPLAY:
			student_array->print();
			break;
		case REMOVESTUDENT:
			cout<<"What is the id of the student you would like to remove?"<<endl;
			cin>>id;
			student_array->removeStudent(id);
			break;
		case ADDSTUDENT:
			{
				cout<<"What is the id of the student you would like to add?"<<endl;
				cin>>id;
				CourseList *new_course_list = new CourseList(); //it's empty yo
				student_array->addStudent(id, new_course_list);
			}
			break;
		case LOADFILE:
			{
				cout<<"What is the name of the file?"<<endl;
				string filename;
				cin>>filename;
				ifstream idatafile(filename);
				int id;
				while(idatafile>>id)
				{
					CourseList *course_list = new CourseList();
					int counter;
					idatafile>>counter;
					//cout<<"Student "<<id<<" has "<<counter<<" classes."<<endl;
					for(int i = 0; i < counter; ++i)
					{
						string name;
						int section;
						int credits;
						
						//get both halves of a course name
						string course, number;
						idatafile>>course;
						idatafile>>number;
						name=course+" "+number;
						
						idatafile>>section;
						idatafile>>credits;
						course_list->addCourse(name, section, credits);
						// cout<<name<<endl;
						// cout<<section<<endl;
						// cout<<credits<<endl;
					}
					cout<<"Adding course list to student "<<id<<"."<<endl;
					student_array->addStudent(id, course_list);
				}
				idatafile.close();
			}
			break;
		case SAVEFILE:
			{
				cout<<"What is the name of the file you want to save to?"<<endl;
				string filename;
				cin>>filename;
				fstream odatafile(filename, ios::out);
				StudentArray::Student *ptr = student_array->head;

				while(ptr)
				{
					int length = 0;
					CourseList::Course *cptr = ptr->course_list->root;
					addSum(cptr, length);
	        odatafile<<ptr->id<<endl;;
	        odatafile<<length<<endl;
	        cptr=ptr->course_list->root;
					writeATree(cptr, odatafile);
	        odatafile<<endl;
					ptr=ptr->next;
				}
				odatafile.close();
			}
			break;
		case ADDCLASS:
			{
				cout<<"What is the id of the student you want to add a class to?"<<endl;
				cin>>id;
				cout<<"Please enter the following information."<<endl;
				string name;
				int section;
				int credits;
				cout<<"Class name:"<<endl;
				cin.ignore(); //forget the newline from the previous statement
				getline(cin, name);
				cout<<"Class section:"<<endl;
				cin>>section;
				cout<<"Credit hours:"<<endl;
				cin>>credits;
				student_array->addClass(id, name, section, credits);
			}
			break;
		/*case DROPCLASS:
			{
				cout<<"What is the id of the student you want to drop from a class?"<<endl;
				cin>>id;
				string name;
				cout<<"What is the name of the class?"<<endl;
				cin.ignore(); //forget the newline from the previous statement
				getline(cin, name);
				student_array->dropClass(id, name);
			}
			break;*/
		}
	
	}
	while (command != "quit");
	
	return 0;
}