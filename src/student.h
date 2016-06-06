//Meeshaan Shah
//CPSC 350
//Assignment 4
//header file for the student class

#ifndef STUDENT_H
#define STUDENT_H

//student class
class Student
{
	public:
		Student();
		Student(int id);
		Student(int id, std::string name, std::string grade, std::string major, double gpa, int advisor);
		virtual ~Student(){}
		int getStudentID();
		std::string getStudentName();
		std::string getStudentGradeLevel();
		std::string getStudentMajor();
		double getStudentGPA();
		int getFacAdvisor();
		void changeFaculty(int facID);
		void print();
		void printToFile(std::ofstream& output);
		void printToFileStudent(std::ofstream& output);
		inline bool operator==(const Student& anotherStudent);
		inline bool operator<(const Student& anotherStudent);
		inline bool operator>(const Student& anotherStudent);
		inline bool operator!=(const Student& anotherStudent);
	
	private:
		int studentId;
		std::string studentName;
		std::string studentGradeLevel;
		std::string studentMajor;
		double studentGPA;
		int facAdvisor;			
};

//default constructor
Student:: Student()
{
	studentId = 0;
	studentName = "";
	studentGradeLevel = "";
	studentMajor = "";
	studentGPA = 0.0;
	facAdvisor = 0;
}

//dummy constructor, used for basic traversal and functions within bst
Student:: Student(int id)
{
	studentId = id;
	studentName = "";
	studentGradeLevel = "";
	studentMajor = "";
	studentGPA = 0.0;
	facAdvisor = 0;
}

//constructor, gets id, name, grade, major gpa, advisor and sets values
Student:: Student(int id, std::string name, std::string grade, std::string major, double gpa, int advisor)
{
	studentId = id;
	studentName = name;
	studentGradeLevel = grade;
	studentMajor = major;
	studentGPA = gpa;
	facAdvisor = advisor;
}

//returns student id as an integer
int Student:: getStudentID()
{
	return studentId;
}

//returns student name as an std::string
std::string Student:: getStudentName()
{
	return studentName;
}

//returns student grade level as a std::string
std::string Student:: getStudentGradeLevel()
{
	return studentGradeLevel;
}

//returns student major as a std::string
std::string Student:: getStudentMajor()
{
	return studentMajor;
}

//returns student GPA as a double
double Student:: getStudentGPA()
{
	return studentGPA;
}

//returns student advisor's id as an int
int Student:: getFacAdvisor()
{
	return facAdvisor;
}

//changes faculty advisor for student
void Student:: changeFaculty(int facID)
{
	facAdvisor = facID;
}

//prints student
void Student:: print()
{
	std::cout << "Name: " << studentName << " | ID: " << studentId << " | Grade: " << studentGradeLevel 
				<< " | Major: " << studentMajor << " | GPA: " << studentGPA << " | Advisor: " 
				<< facAdvisor << std::endl;
}

//prints student to file
void Student:: printToFile(std::ofstream& output)
{
	output << studentName << "\n" << studentId << "\n" << studentGradeLevel << "\n" << studentMajor 
			<< "\n" << studentGPA << "\n" << facAdvisor << std::endl;
}

//does nothing, used for pairity with print to file function in bst so I did not have to 
//implement another function to print to file just for students
void Student:: printToFileStudent(std::ofstream& output)
{
}

//returns true if this students is equal to another student, overloaded operator
inline bool Student:: operator==(const Student& anotherStudent)
{
	return (this->studentId == anotherStudent.studentId);
}

//return true if this student is less than another student, overloaded operator
inline bool Student:: operator<(const Student& anotherStudent)
{
	return (this->studentId < anotherStudent.studentId);
}

//return true if this student is greater than another student, overloaded operator
inline bool Student:: operator>(const Student& anotherStudent)
{
	return (this->studentId > anotherStudent.studentId);
}

//return true if this student is not equal to another student, overlaoded operator
inline bool Student:: operator!=(const Student& anotherStudent)
{
	return (this->studentId != anotherStudent.studentId);
}

#endif