#pragma once
#include <iostream>
#include <string>
using namespace std;

const int MAXNOTIFICATIONS=50;

class Notification
{
	string className;
	string assignmentName;
public:
	Notification() {}
	Notification(const string& className, const string& assignmentname) :className(className), assignmentName(assignmentname) {}
	string get_class_name() { return className; }
	string get_assignment_name() { return assignmentName; }
};

class NotificationForStudent: public Notification
{
	string deadline;
	
public:
	NotificationForStudent() {}
	NotificationForStudent(const string& className, const string& assignmentname, const string& deadline) :Notification(className, assignmentname),deadline(deadline) {}
	string Get_deadline() { return deadline; }
	void SetDeadLine(string Deadline) { deadline = Deadline; }
};

class NotificationForTeacher : public Notification
{
	string studentName;
public:
	NotificationForTeacher() {}
	NotificationForTeacher(const string& StudentName,const string& className, const string& assignmentname):studentName(StudentName),Notification(className, assignmentname) {}
	string get_studentName() { return studentName; }
};

class NotificationManagementSystem
{
	NotificationForStudent notificationStudent[MAXNOTIFICATIONS];
	NotificationForTeacher notificationTeacher[MAXNOTIFICATIONS];
	int notificationCountStudent;
	int notificationCountTeacher;
public:
	NotificationManagementSystem() :notificationCountStudent(0), notificationCountTeacher(0){}//, notificationCountTeacher(0) {};

	void AddNotificationForStudent(const string& className, const string& assignmentname, const string& deadline)        //student notification function
	{
		if (notificationCountStudent < MAXNOTIFICATIONS)
		{
			notificationStudent[notificationCountStudent++] = NotificationForStudent(className, assignmentname, deadline);
		}

	}
	void AddNotificationForTeacher(const string& StudentName, const string& className, const string& assignmentname)         //Teacher notification function
	{
		if (notificationCountTeacher < MAXNOTIFICATIONS)
		{
			notificationTeacher[notificationCountTeacher++] = NotificationForTeacher(StudentName, className, assignmentname);
		}
	}
	void showNotificationsforStudent(const string& className)
	{
		for (int i = 0; i < notificationCountStudent; ++i)
		{
			if (notificationStudent[i].get_class_name() == className)
			{
				cout << "An assignment named \"" << notificationStudent[i].get_assignment_name() << "\ was uploaded in your class and its deadline is " << notificationStudent[i].Get_deadline() << ". Happy Cooding :D\n";
			}
		}
	}
	void showNotificationsforteacher(const string& className)
	{
		for (int i = 0; i < notificationCountTeacher; ++i)
		{
			if (notificationTeacher[i].get_class_name() == className)
			{
				cout << "A submission has been made by student \"" << notificationTeacher[i].get_studentName() << "\" of class \"" << notificationTeacher[i].get_class_name() << "\" for assignment name \"" << notificationTeacher[i].get_assignment_name() << "\" .Happy Marking :D\n";
			}
		}
	}

};