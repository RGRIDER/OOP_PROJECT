#include <iostream>
#include <string>
#include"UserManagement.h"
#include"Submission.h"
#include"GradeBook.h"
#include"ClassManagement.h"
#include"AssignmentManagementSystem.h"
#include <limits>
using namespace std;

int main()
{
	
	cout << " ______________________________________________________________________"<<endl;
	cout << "|                                                                      |" << endl;
	cout << "|                     FINAL PROJECT CS SUMMER 2023                     |" << endl;
	cout << "|                            HAIDER ZIA                                |" << endl;
	cout << "|                             22I-1196                                 |" << endl;
	cout << "|                               CS-C                                   |" << endl;
	cout << "|                                                                      |" << endl;
	cout << "|______________________________________________________________________|" << endl;
	
	cout << "\n-------------User Management System-------------------------" << endl;
	UserManagerSystem ums;

	ums.registerUser("Imran Khan", "imrankhan@example.com", "Imran123", 0);
	ums.registerUser("Saba Qamar", "sabaqamar@example.com", "Saba456", 0);
	ums.registerUser("Fawad Khan", "fawadkhan@example.com", "Fawad789", 1);
	ums.registerUser("Mahira Khan", "mahirakhan@example.com", "Mahira321", 1);
	ums.registerUser("Shoaib Malik", "shoaibmalik@example.com", "Malik654", 1);
	ums.registerUser("Sania Mirza", "saniamirza@example.com", "Sania123", 1);
	ums.registerUser("Wasim Akram", "wasimakram@example.com", "Wasim456", 1);
	ums.registerUser("Sajal Aly", "sajalaly@example.com", "Sajal789", 1);
	ums.registerUser("Babar Azam", "babarazam@example.com", "Babar321", 1);
	ums.registerUser("Mehwish Hayat", "mehwishhayat@example.com", "Mehwish654", 1);

	//ums.display();
	//ums.displayFullUMS();
	
	string str1 = "", str2 = "", str3 = "",str4="";
	/*bool check = 0;

	cout <<"\n**************** Now Lets add a User! ****************\n";
	cout << "Enter user name: ";
	getline(cin, str1);
	cout << "Enter email id: ";
	cin >> str2;
	cout << "Enter user password: ";
	cin >> str3;
	cout << "Enter are you teacher (press '0' if yes press '1' if not)?";
	cin >> check;*/

	//ums.registerUser(str1, str2, str3, check);

	////ums.display();
//	ums.displayFullUMS();

	//ums.saveStudentsToFile();
	//ums.saveTeachersToFile();
	
	////ums.LoadStudentsFromaFile();
	
	cout << "\n-------------ClasssRoom Management System-------------------------" << endl;
	ClassManagementSystem cms(&ums);


	cms.createClass("Math101", "Mathematics", "0", "Introductory Math");
	cms.add_student("Math101", ums.authenticateStudent("fawadkhan@example.com", "Fawad789"));
	cms.add_student("Math101", ums.authenticateStudent("mahirakhan@example.com", "Mahira321"));
	cms.add_student("Math101", ums.authenticateStudent("shoaibmalik@example.com", "Malik654"));
	//cms.add_student("Math101", ums.authenticateStudent(str2,str3));
	
	cms.createClass("Physics101", "Physics", "1", "Classical Mechanics");
	cms.add_student("Physics101", ums.authenticateStudent("saniamirza@example.com", "Sania123"));
	cms.add_student("Physics101", ums.authenticateStudent("wasimakram@example.com", "Wasim456"));
	cms.add_student("Physics101", ums.authenticateStudent("sajalaly@example.com", "Sajal789"));

	//cms.addClassDataToFile();
	//cms.showAllClasses();

	//string classname1;
	//cout << "Enter the name of class you want to delete .";
	//cin >> classname1;
	//cms.deleteClass(classname1);
	//cms.showAllClasses();            //after deleting
	//cms.addClassDataToFile();           //file handling updated

	//cout << "****** Lets Check delete Student from the class function !******\n";
	//cin.ignore();
	//cout << "Enter Student Name: ";
	//getline(cin, str1);
	//cout << "Enter Class Name: ";
	//cin >> str2;
	//cms.removeStudentFromClass(str2,str1);
	//cms.showAllClasses();
	cout << "\n-------------Assignment Management System-------------------------" << endl;
	
	AssignmentManagementSystem ams;
	NotificationManagementSystem nms;
	cms.setNotificationManagementSystem(&nms);
	
	
	// Create some assignments
	ams.createAssignment("Assignment 1", "Complete Chapter 1 exercises", "10-08-2023", "100");

	ams.createAssignment("Assignment 2", "Write a report on Topic XYZ", "15-08-2023", "100");

	ams.createAssignment("Assignment 3", "Research and prepare a presentation", "20-09-2023", "100");

	cms.addAssignmentToClass("Physics101", ams.get_assignment("Assignment 1"));
	cms.addAssignmentToClass("Physics101", ams.get_assignment("Assignment 2"));

	////cin.ignore();
	//cout << "Lets check create Assignment Function:\n";
	//cout << "Enter name of assignment: ";
	//getline(cin, str1);

	//cin.ignore();

	//cout << "Enter details of assignment: ";
	//getline(cin, str2);
	//
	//
	//cin.ignore();
	//cout << "Enter Deadline of assignment: ";
	//cin >> str3;
	//cout << "Enter Total Marks  of assignment: ";
	//cin >> str4;
	//
	//ams.createAssignment(str1,str2,str3,str4);               //Late assignment would not be added
	//ams.saveAssignmentsToFile();

	//cin.ignore();
	//cout << "Now lets delete an assignment:\n";
	//cout << "Enter Assignment Title:";
	//	getline(cin, str1);                                         // Checking Delete Assignment functionality
	//	ams.deleteAssignmentFromSystem(str1);
	//	cout << endl;
	//	ams.saveAssignmentsToFile();

	SubmissionManagementSystem sms(&ams);
	sms.set_NotificationManagementSystem(&nms);
	cout << "\n-------------Submission Management System-------------------------" << endl;

	//sms.addTextSubmission("Wasim Akram","Physics101", "Assignment 1");        //          text submission
	sms.addFileSubmission("Sania Mirza", "Physics101", "Assignment 1", "submission.txt");
	sms.addFileSubmission("Sajal Aly", "Physics101", "Assignment 1", "submission.txt");
	                                                                                           //Scoring the assignments                                               
	sms.scoreSubmission("Wasim Akram", "Assignment 1", "Keep it Up !", 100);
	sms.scoreSubmission("Sania Mirza", "Assignment 1", "You need improvement.", 80);
	sms.scoreSubmission("Sajal Aly", "Assignment 1", "Just as expected !", 60);

	//sms.displayStudentSubmission("Wasim Akram", "Assignment 1");                  //displaying submitted data

	sms.saveSubmissionsToFile();

		cout << "\n-------------Grade Management System-------------------------" << endl;
		
		Grade gms(&sms);   // weightage is set 10 by  default hower it can be changed later or can also be entered in the parameter
//
	gms.calculateStudentCumultativeGrade("Sajal Aly");                      //calculates student grades 
//		gms.DisplayGradeSystem();	                                         //Displays Student grades
//	gms.calculateStudentCumultativeGrade("Wasim Akram");
	

	gms.storeGradeDataToFile();
	
	cin.ignore();
	cout << "\n-------------Notificatiion Management System-------------------------" << endl;
	cout << "For Teachers :"<<endl;
	cout << "Enter Your class Name:";
		getline(cin, str1);
		nms.showNotificationsforteacher(str1);
		cout<<endl << "For Students :" << endl;
		cin.ignore();
		cout << "Enter Your class Name:";
		getline(cin, str1);
		nms.showNotificationsforStudent(str1);

	return 0;
}

		
