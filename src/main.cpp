//Meeshaan Shah
//CPSC 350
//Assignment 4
//main driver for assignment 4

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "BST.h"
#include "student.h"
#include "faculty.h"
#include "dlist.h"

using namespace std;


//reads student info from user and returns info as type student
Student readStudent()
{
	int id;
	string name;
	string grade;
	string major;
	double GPA;
	int advId;
	
	cin.ignore();
	
	cout << "Enter student name: " << endl;
	getline (cin, name);
	cout << "Enter student grade level: " << endl;
	getline(cin, grade);
	cout << "Enter student major: " << endl;
	getline (cin, major);
	cout << "Enter student ID: "; cin >> id;
	cout << "Enter student GPA: "; cin >> GPA;
	cout << "Enter student Advisor ID: "; cin >> advId;
	
	Student newStudent(id, name, grade, major, GPA, advId);
	return newStudent; 
}

//reads faculty infor form user and returns info as type faculty
Faculty readFaculty()
{
	int id;
	string name;
	string level;
	string department;
	
	cin.ignore();
	
	cout << "Enter faculty name: " << endl;
	getline (cin, name);
	cout << "Enter faculty level: " << endl;
	getline (cin, level);
	cout << "Enter faculty department: " << endl;
	getline (cin, department);
	cout << "Enter faculty ID: "; cin >> id;
	
	Faculty newFaculty(id, name, level, department);
	return newFaculty;
}

//function displays menu
void displayMenu()
{
	cout << "1.  Print all students and their information (sorted by ascending id #)" << endl;
	cout << "2.  Print all faculty and their information (sorted by ascending id #)" << endl;
	cout << "3.  Find and display student information given the students id" << endl;
	cout << "4.  Find and display faculty information given the faculty id" << endl;
	cout << "5.  Given a student's id, print the name and info of their faculty advisor" << endl;
	cout << "6.  Given a faculty id, print all the names and info of his/her advisees" << endl;
	cout << "7.  Add a new student" << endl;
	cout << "8.  Delete a student given the id" << endl;
	cout << "9.  Add a new faculty member" << endl;
	cout << "10. Delete a faculty member given the id" << endl;
	cout << "11. Change a student's advisor given the student id and the new faculty id" << endl;
	cout << "12. Remove an advisee from a faculty member given the ids" << endl;
	cout << "13. Rollback" << endl;
	cout << "14. Exit" << endl;
}

int main()
{
	//declares structures and input streams to start program
	BST<Student> masterStudent;
	BST<Faculty> masterFaculty;
	ifstream readFac ("facultyTable.txt");
	ifstream readStu("studentTable.txt");
	
	//for use when reading from file
	string line;
	
	//reads from faculty table if it exists and populates tree
	if (readFac.is_open())
	{
   		while (!readFac.eof())
    	{
    		//gets name
    		string name;
    		getline(readFac, name);
    		
    		//gets id
    		getline(readFac, line);
    		int id = atoi(line.c_str());
    		
    		//gets level
    		string level;
    		getline(readFac, level);
    		
    		//gets department
    		string dep;
    		getline(readFac, dep);
    		
    		//creates and adds new faculty to the tree based on file
    		Faculty newFac(id, name, level, dep);
    		masterFaculty.add(newFac);
    		
    		//gets number students faculty has as advisees
    		getline(readFac, line);
    		int numStudent = atoi(line.c_str());
    		
    		//loop through portion based on how many advisees faculty has
    		for (int i = 0; i < numStudent; ++i)
   			{
   				//gets student advisee
   				getline(readFac, line);
   				int student = atoi(line.c_str());
   				masterFaculty.fetch(newFac)->data.addStudent(student);
   			}
   			//used for debugging an error, was reading last empty line in file as another blank object
   			// or the last number object. Here I set what line is so i know what incorrect
   			//object is being added to the tree so I can delete it
   			line = "";
    	}
    	//deletes incorrect faculty member
    	Faculty deleteFac(0);
		masterFaculty.deleteNode(deleteFac);
    	readFac.close();
	}
	
	//reads from student table and populates master student tree
	if (readStu.is_open())
	{
   		while (!readStu.eof())
    	{
    		//gets name
    		string name;
    		getline(readStu, name);
    		
    		//gets id
    		getline(readStu, line);
    		int id = atoi(line.c_str());
    		
    		//gets grade
    		string grade;
    		getline(readStu, grade);
    		
    		//gets major
    		string major;
    		getline(readStu, major);
    		
    		//gets gpa
    		getline(readStu, line);
    		double GPA = atof(line.c_str());
    		
    		//gets fac advisor
    		getline(readStu, line);
    		int facAdvisor = atoi(line.c_str());
    		
    		//creates student based on above info and adds to tree    		
    		Student newStudent(id, name, grade, major, GPA, facAdvisor);
    		masterStudent.add(newStudent);
    		
    		//same issue as explained above when reading from faculty
    		line = "";
    	}
    	//deletes incorrect student from tree
    	Student deleteStu(0);
		masterStudent.deleteNode(deleteStu);
    	readStu.close();
	}
	
	int answer;
	
	displayMenu();
	cout << endl;
	cout << "Enter Choice: "; cin >> answer;
	
	//majority of the program, loop until user exits
	while (answer != 14)
	{
		//switch on the answer
		switch (answer)
		{
			//prints student tree
			case 1:
			{
				//check if student tree is empty, if not display it
				if (!masterStudent.isEmpty())
				{
					masterStudent.printDisplay();
				}
				else
				{
					cout << "No students in database." << endl;
				}
			}
			break;
			
			//prints faculty tree
			case 2:
			{
				//checks if faculty tree is empty, if not display it
				if (!masterFaculty.isEmpty())
				{
					masterFaculty.printDisplay();
				}
				else
				{
					cout << "No faculty in database." << endl;
				}
			}
			break;
			
			//prints student given id
			case 3:
			{
				//gets id from user and create temporary student for BST traversal
				int id;
				cout << "Enter student ID: "; cin >> id;
				Student tempStudent3(id);
				
				//checks if student is in tree, then print student
				if (masterStudent.contains(tempStudent3))
				{
					masterStudent.fetch(tempStudent3)->data.print();
				}
				else
				{
					cout << "Student not in database." << endl;
				}
			}
			break;
			
			//prints faculty given id
			case 4:
			{
				//gets fac id from user and create temp faculty 
				int id;
				cout << "Enter faculty ID: "; cin >> id;
				Faculty tempFaculty4(id);
				
				//if faculty is in tree, print faculty
				if (masterFaculty.contains(tempFaculty4))
				{
					masterFaculty.fetch(tempFaculty4)->data.print();
				}
				else
				{
					cout << "Faculty member not in database." << endl;
				}
			}
			break;
			
			//print faculty advisor given student id
			case 5:
			{
				//gets id from user and creates student
				int id;
				cout << "Enter student ID: "; cin >> id;
				Student tempStudent5(id);
				
				//checks if student is in tree
				if (masterStudent.contains(tempStudent5))
				{
					//creates faculty from fac advisor from student
					Faculty tempFaculty5(masterStudent.fetch(tempStudent5)->data.getFacAdvisor());
					
					//checks if faculty is in tree and print faculty
					if (masterFaculty.contains(tempFaculty5))
					{
						masterFaculty.fetch(tempFaculty5)->data.print();
					}
					else
					{
						cout << "Faculty not in database." << endl;
					}
				}
				else
				{
					cout << "Student not in database." << endl;
				}
			}
			break;
			
			//print student advisees given faculty id
			case 6:
			{
				//gets id from user and creates faculty
				int id;
				cout << "Enter faculty ID: "; cin >> id;
				Faculty tempFaculty6(id);
				
				//checks if faculty is in the tree, and print advisees
				if (masterFaculty.contains(tempFaculty6))
				{
					masterFaculty.fetch(tempFaculty6)->data.printStudentList();
					cout << endl;
				}
				else
				{
					cout << "Faculty not in database." << endl;
				}
			}
			break;
			
			//adds student to the tree based on user input
			case 7:
			{
				//get inputs from user and create a new student
				Student newStudent(readStudent());
				
				//if student is not in the tree
				if (!masterStudent.contains(newStudent))
				{
					//creates faculty based on students advisor input
					Faculty tempFaculty7(newStudent.getFacAdvisor());
					
					//checks if faculty member is in the tree, if yes add student to their list and 
					//add student to student tree
					if (masterFaculty.contains(tempFaculty7))
					{
						masterFaculty.fetch(tempFaculty7)->data.addStudent(newStudent.getStudentID());
						masterStudent.add(newStudent);
					}
					//if advisor is not in tree
					else
					{	
						//get fac info from user and create new faculty
						cout << "Advisor is not in database" << endl;
						Faculty actualFaculty(readFaculty());
						
						//checks if fac id for student is equal fac advisor for faculty, if yes add faculty
						//to tree, add student to their advisee list, add student to student ree
						if (actualFaculty.getFacultyID() == newStudent.getFacAdvisor())
						{
							masterFaculty.add(actualFaculty);
							masterFaculty.fetch(actualFaculty)->data.addStudent(newStudent.getStudentID());
							masterStudent.add(newStudent);
						}
						else
						{
							cout << "Faculty ids do not match" << endl;
						}
					}
				}
				else
				{
					cout << "Student already in database." << endl;
				}
			}
			break;
			
			//delete student from tree given id
			case 8:
			{
				//gets id from user and creates student
				int id;
				cout << "Enter student ID: "; cin >> id;
				Student tempStudent8(id);
				
				//checks if student is in tree
				if (masterStudent.contains(tempStudent8))
				{
					//creates faculty based on advisor from student
					Faculty tempFaculty8(masterStudent.fetch(tempStudent8)->data.getFacAdvisor());
					
					//check if faculty is in tree
					if (masterFaculty.contains(tempFaculty8))
					{
						//check if student is advisee of faculty, if it is remove student from faculty
						//and delete student
						if (masterFaculty.fetch(tempFaculty8)->data.hasStudent(id))
						{
							masterFaculty.fetch(tempFaculty8)->data.removeStudent(id);
							masterStudent.deleteNode(tempStudent8);
						}
						else
						{
							cout << "Is not an advisee" << endl;
						}
					}
					else
					{
						cout << "Faculty not in database." << endl;
					}
				}
				else
				{
					cout << "Student not in database" << endl;
				}
			}
			break;
			
			//adds new faculty to tree based on user input	
			case 9:
			{
				//creates faculty based on user input
				Faculty newFaculty(readFaculty());
				
				//checks if faculty member is not in tree, if not add faculty to tree
				if (!masterFaculty.contains(newFaculty))
				{
					masterFaculty.add(newFaculty);
				}
				else
				{
					cout << "Faculty member already in database." << endl;
				}
			}
			break;
			
			//deletes faculty from tree given ids
			case 10:
			{
				//gets id from user and creates faculty
				int id;
				cout << "Enter faculty ID: "; cin >> id;
				Faculty tempFaculty10(id);
				
				//checks if faculty is in tree
				if (masterFaculty.contains(tempFaculty10))
				{
					//if size of fac tree is 1, delete faculty and empty student tree
					if (masterFaculty.getSize() == 1)
					{
						masterFaculty.deleteNode(tempFaculty10);
						masterStudent.emptyTree();
					}
					//if size of fac tree is greater than 1
					else
					{
						//get id from user for new faculty member and create new faculty
						int newID;
						masterFaculty.printDisplay();
						cout << "Enter id of Faculty to add advisees to: "; cin >> newID;
						Faculty newFac(newID);
						
						//check if new faculty is in tree
						if (masterFaculty.contains(newFac))
						{
							//loop until their faculty to delete advisee's tree is empty
							while (!masterFaculty.fetch(tempFaculty10)->data.isStudentListEmpty())
							{
								//create student based on the root of to delete advisees tree and create student
								int student = masterFaculty.fetch(tempFaculty10)->data.getStudentRoot();
								Student tempStudent10(student);
								
								//do deletion steps if student is tree, change fac id for student to the new fac
								//id, add student to new facs advisee list, remove student from old fac's 
								//advisee's list cre
								if (masterStudent.contains(tempStudent10))
								{
									masterStudent.fetch(tempStudent10)->data.changeFaculty(newID);
									masterFaculty.fetch(newFac)->data.addStudent(student);
									masterFaculty.fetch(tempFaculty10)->data.removeStudent(student);
								}
							}
							//delete fac from tree
							masterFaculty.deleteNode(tempFaculty10);
						}
						else
						{
							cout << "Faculty not in database." << endl;
						}
					}
				}
				else
				{
					cout << "Faculty not in database." << endl;
				}
			}
			break;
			
			//change student advisor given student id and faculty id
			case 11:
			{
				//gets ids from user and creates student and faculty
				int stuID;
				int facID;
				cout << "Enter student ID: "; cin >> stuID;
				cout << "Enter Faculty ID: "; cin >> facID;
				Student tempStudent11(stuID);
				Faculty tempFaculty11(facID);
				
				//checks if student is in tree
				if (masterStudent.contains(tempStudent11))
				{
					//checks if faculty is in tree
					if (masterFaculty.contains(tempFaculty11))
					{
						//create old faculty based on students advisor
						Faculty otherFaculty(masterStudent.fetch(tempStudent11)->data.getFacAdvisor());
						
						//check if old faculty has student in their advisee list
						if (masterFaculty.fetch(otherFaculty)->data.hasStudent(stuID))
						{
							//remove advisee from old fac, add student to new fac advisee list, change students
							//fac advisor
							masterFaculty.fetch(otherFaculty)->data.removeStudent(stuID);
							masterFaculty.fetch(tempFaculty11)->data.addStudent(stuID);
							masterStudent.fetch(tempStudent11)->data.changeFaculty(facID);
						}
						else
						{
							cout << "Student not advisee of previous faculty member." << endl;
						}
					}
					else
					{
						cout << "Faculty not in database." << endl;
					}
				}
				else
				{
					cout << "Student not in database." << endl;
				}
			}
			break;
			
			//removes student as advisee from faculty given ids	
			case 12:
			{
				//gets ids from user and creates fac and student
				int stuID;
				int facID;
				cout << "Enter student ID: "; cin >> stuID;
				cout << "Enter Faculty ID: "; cin >> facID;
				Student tempStudent12(stuID);
				Faculty tempFaculty12(facID);
				
				//check is faculty is in tree
				if (masterFaculty.contains(tempFaculty12))
				{
					//checks if student is in tree
					if (masterStudent.contains(tempStudent12))
					{
						//if fac has student in advisee list, remove student from advisee list and delete 
						//student
						if (masterFaculty.fetch(tempFaculty12)->data.hasStudent(stuID))
						{
							masterFaculty.fetch(tempFaculty12)->data.removeStudent(stuID);
							masterStudent.deleteNode(tempStudent12);
						}
						else
						{
							cout << "Faculty does not have advisee." << endl;
						}
					}
					else
					{
						cout << "Student is not in database" << endl;
					}
				}
				else
				{
					cout << "Faculty member is not in the database." << endl;
				}
			}
			break;
			
			//rollback
			case 13:
			{
				cout << "haha you are very funny." << endl;
			}
			break;
			
			//default
			default:
			{
				cout << "You did not enter correct command." << endl;
			}
			break;
		}//end of switch
		
		//to make output screen cleaner, asks user to hit enter to continue
		cout << endl;
		cout << "Press enter to continue..." << endl;
		cin.ignore();
		cin.ignore();
		
		//clears screen
		system("clear");
		
		//display menu and get answer to loop back into menu, or exit if user wants to exit
		displayMenu();
		cout << endl;
		cout << "Enter Choice: "; cin >> answer;
	}//end of while
	
	//writes trees to respective files
	ofstream outputFac ("facultyTable.txt");
	ofstream outputStu ("studentTable.txt");
	masterStudent.printToFile(outputStu);
	masterFaculty.printToFile(outputFac);
	
	//close output stream
	outputFac.close();
	outputStu.close();
	
	return 0;
}//end of main