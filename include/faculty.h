//Meeshaan Shah
//CPSC 350
//Assignment 4
//header file for the faculty class

#ifndef FACULTY
#define FACULTY

#include "BST.h"

//faculty class
class Faculty
{
	public:
		Faculty();
		Faculty(int id);
		Faculty(int id, std::string name, std::string level, std::string dep);
		virtual ~Faculty(){}
		int getFacultyID();
		std::string getFacultyName();
		std::string getFacultyLevel();
		std::string getDepartment();
		void addStudent(int student);
		void removeStudent(int student);
		int getStudentRoot();
		bool isStudentListEmpty();
		int getStudentListSize();
		bool hasStudent(int student);
		void print();
		void printStudentList();
		void printToFile(std::ofstream& output);
		void printToFileStudent(std::ofstream& output);
		inline bool operator==(const Faculty& anotherFaculty);
		inline bool operator<(const Faculty& anotherFaculty);
		inline bool operator>(const Faculty& anotherFaculty);
		inline bool operator!=(const Faculty& anotherFaculty);
	
	private:
		int facultyID;
		std::string facultyName;
		std::string facultyLevel;
		std::string facultyDepartment;
		//DList<int> studentList;
		BST<int> studentTree;		
};

//default constructor
Faculty:: Faculty()
{
	facultyID = 0;
	facultyName = "";
	facultyLevel = "";
	facultyDepartment = "";
}

//dummy constructor, used to create temporary objects for use in doing basic functions in BST
Faculty:: Faculty(int id)
{
	facultyID = id;
	facultyName = "";
	facultyLevel = "";
	facultyDepartment = "";
}

//constructor, gets id, name, grade, major gpa, advisor and sets values
Faculty:: Faculty(int id, std::string name, std::string level, std::string dep)
{
	facultyID = id;
	facultyName = name;
	facultyLevel = level;
	facultyDepartment = dep;
}

//returns id of faculty
int Faculty:: getFacultyID()
{
	return facultyID;
}

//returns name of faculty member
std::string Faculty:: getFacultyName()
{
	return facultyName;
}

//return level of faculty member
std::string Faculty:: getFacultyLevel()
{
	return facultyLevel;
}

//return department of faculty member
std::string Faculty:: getDepartment()
{
	return facultyDepartment;
}

//adds student to faculty list
void Faculty:: addStudent(int student)
{
	studentTree.add(student);
}

//removes student from faculty list
void Faculty:: removeStudent(int student)
{
	studentTree.deleteNode(student);
}

//gets the root of the student tree
int Faculty:: getStudentRoot()
{
	return studentTree.getRoot();
}

//checks if student list is empty, returns a boolean
bool Faculty:: isStudentListEmpty()
{
	return studentTree.isEmpty();
}

//gets size of student list
int Faculty:: getStudentListSize()
{
	return studentTree.getSize();
}

//checks student list and see's if student is in list
bool Faculty:: hasStudent(int student)
{
	return studentTree.contains(student);
}

//prints faculty
void Faculty:: print()
{
	std::cout << "Name: " << facultyName << " | ID: " << facultyID << " | Level: " << facultyLevel 
				<< " | Department: " << facultyDepartment << " | Advisees: ";
	studentTree.printSub();
	std::cout << std::endl;
}

//prints list of students tied to faculty
void Faculty:: printStudentList()
{
	studentTree.printSub();
}

//prints faculty member to file
void Faculty:: printToFile(std::ofstream& output)
{
	output << facultyName << "\n" << facultyID << "\n" << facultyLevel 
					<< "\n" << facultyDepartment << "\n" << getStudentListSize() << std::endl;
}

//prints list of students to file
void Faculty:: printToFileStudent(std::ofstream& output)
{
	studentTree.printSubToFile(output);
}

//returns true if this faculty member is equal to another faculty member, overloaded operator
inline bool Faculty:: operator==(const Faculty& anotherFaculty)
{
	return (this->facultyID == anotherFaculty.facultyID);
}

//return true if this fac. member is less than another fac member, overloaded operator
inline bool Faculty:: operator<(const Faculty& anotherFaculty)
{
	return (this->facultyID < anotherFaculty.facultyID);
}

//return true if this fac is greater than another fac, overlaoded operator
inline bool Faculty:: operator>(const Faculty& anotherFaculty)
{
	return (this->facultyID > anotherFaculty.facultyID);
}

//return true if this fac is not equal to another fac, overlaoded operator
inline bool Faculty:: operator!=(const Faculty& anotherFaculty)
{
	return (this->facultyID != anotherFaculty.facultyID);
}
#endif
