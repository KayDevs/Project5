#include "CourseList.h"

CourseList::Course::Course(string name, int section, int credits)
{
	this->name = name;
	this->section = section;
	this->credits = credits;
}

CourseList::CourseList()
{
	this->root = nullptr; //decapitate it
}

void CourseList::addCourse(string name, int section, int credits)
{
  if(this->root!=NULL)
    addCourse(name, section, credits, this->root);
  else
  {
    root=new Course(name, section, credits);
    root->left=NULL;
    root->right=NULL;
  }
}

void CourseList::addCourse(string name, int section, int credits, Course *leaf)
{
	if(name< leaf->name)
  {
    if(leaf->left!=NULL)
     addCourse(name, section, credits, leaf->left);
    else
    {
      leaf->left=new Course(name, section, credits);
      leaf->left->left=NULL;    //Sets the left child of the child node to null
      leaf->left->right=NULL;   //Sets the right child of the child node to null
    }  
  }
  else if(name>=leaf->name)
  {
    if(leaf->right!=NULL)
      addCourse(name, section, credits, leaf->right);
    else
    {
      leaf->right=new Course(name, section, credits);
      leaf->right->left=NULL;  //Sets the left child of the child node to null
      leaf->right->right=NULL; //Sets the right child of the child node to null
    }
  }
}

/*void CourseList::dropCourse(string name)
{
	Course *ptr = head;
	Course *follow = nullptr;
	if(name == ptr->name)
	{
		head = ptr->next;
		ptr->next = nullptr;
		delete ptr;
		return;
	}
	while(ptr->next)
	{
		//cout<<"name of current: "<<ptr->name<<endl;
		follow = ptr;
		ptr = ptr->next;
		if(name == ptr->name)
		{
			//cout<<"Supposedly deleting."<<endl;
			follow->next = ptr->next;
			//cout<<"repairing."<<endl;
			ptr->next = nullptr;
			delete ptr;
			return;
		}
	}
}*/

//this is annoying
void CourseList::print()
{
	print(this->root);
}
void CourseList::print(Course *ptr)
{
	if(ptr)
	{
		cout<<ptr->name<<endl;
		cout<<ptr->section<<endl;
		cout<<ptr->credits<<endl;
		if(ptr->left)
		{
			print(ptr->left);
		}
		if(ptr->right)
		{
			print(ptr->right);	
		}
	}
}