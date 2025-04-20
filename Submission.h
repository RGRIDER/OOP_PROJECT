#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include"AssignmentManagementSystem.h"
#include"Notification.h"
using namespace std;
const int MAX_SUBMISSIONS = 100;
class Submission 
{
	
	string timestamp;
	string attachedfile;
	bool evaluation_status;
	int score;
	string feedback;
	string className;
	string studentName;
	string assignmentName;

public:
	

	Submission(string student="", string className="", string assignmentName="") :studentName(student), className(className), assignmentName(assignmentName),evaluation_status(0)
	{
		timestamp = "";
		time_t currentTime = time(nullptr);
		tm localTimeInfo;
		localtime_s(&localTimeInfo, &currentTime);
																				// Extract the day, month, and year
		int current_day = localTimeInfo.tm_mday;
		int current_month = localTimeInfo.tm_mon + 1;								// tm_mon is zero-indexed, so we add 1
		int current_year = localTimeInfo.tm_year + 1900;							// tm_year is years since 1900, so added 1900
		timestamp += to_string(current_day);
		timestamp += "-";
		timestamp += to_string(current_month);
		timestamp += "-";
		timestamp += to_string(current_year);
	}
	
	void score_Evaluation(const string& feedback, const int& score)  
	{
		evaluation_status = true;
		this->feedback = feedback;
		this->score = score;
	}
	
	void file_upload(string fileName)               // File Upload
	{
		ifstream file(fileName);
		if (file.is_open())
		{
			string temp;
			while (file >> temp)
			{
				attachedfile += temp;
				attachedfile += " ";
			}
		}
		else
			cout << "Error occured while opening the File !\n";
	}
	void textUpload()            //Text Upload
	{
		string temp;
		cout << "Enter the text for submission. \n";
		getline(cin, attachedfile);
	}
	
	// Getters
	std::string getTimestamp() const {
		return timestamp;
	}

	std::string getAttachedFile() const {
		return attachedfile;
	}

	bool getEvaluationStatus() const {
		return evaluation_status;
	}

	int getscore() const {
		return score;
	}

	std::string getFeedback() const {
		return feedback;
	}

	std::string getClassName() const {
		return className;
	}

	std::string getStudentName() const {
		return studentName;
	}

	std::string getAssignmentName() const {
		return assignmentName;
	}

	// Setters
	void setTimestamp(const std::string& newTimestamp) {
		timestamp = newTimestamp;
	}

	void setAttachedFile(const std::string& newAttachedFile) {
		attachedfile = newAttachedFile;
	}

	void setEvaluationStatus(bool newEvaluationStatus) {
		evaluation_status = newEvaluationStatus;
	}

	void setscore(int newscore) {
		score = newscore;
	}

	void setFeedback(const std::string& newFeedback) {
		feedback = newFeedback;
	}

	void setClassName(const std::string& newClassName) {
		className = newClassName;
	}

	void setStudentName(const std::string& newStudentName) {
		studentName = newStudentName;
	}

	void setAssignmentName(const std::string& newAssignmentName) {
		assignmentName = newAssignmentName;
	}
};

class SubmissionManagementSystem
{
	Submission submissions[MAX_SUBMISSIONS];
	AssignmentManagementSystem* AMS;
	NotificationManagementSystem* NMS;
	int SubmissionCount;
public:
	void set_NotificationManagementSystem(NotificationManagementSystem* nms) { NMS = nms; }
	SubmissionManagementSystem(AssignmentManagementSystem* ams):SubmissionCount(0),AMS(ams) {};
	Submission* Get_Submissions() { return submissions; }
	int Get_SubmissionCount() { return SubmissionCount; }
	int get_assignmentPointValue(const string& AssignmentName)
	{
		for (int i = 0; i < AMS->getAssignmentCount(); ++i)
		{
			return stoi(AMS->get_assignment(AssignmentName)->getPointValue());
		}
	}
	void addTextSubmission(const string& student,const string& className,const string& assignmentName) // Text Submission
	{
		if (!isPastDeadline(AMS->get_assignment(assignmentName)->getDeadline()))
		{
			if (SubmissionCount < MAX_SUBMISSIONS) {
				submissions[SubmissionCount] = Submission(student, className, assignmentName);
				submissions[SubmissionCount].textUpload();
				++SubmissionCount;
				NMS->AddNotificationForTeacher(student, className, assignmentName);
			}
			else
				cout << "Maxium Submissions have already been made !\n";
		}
		else
			cout << "Cannot create Submission with Past Deadline !\n";
		
	}
	void displayStudentSubmission(const string& studentNAme, const string& AssignmenNAme)
	{
		for (int i = 0; i < SubmissionCount; ++i)
		{
			if ((submissions[i].getStudentName() == studentNAme) && (submissions[i].getAssignmentName() == AssignmenNAme)){
			cout<<"Student: " << submissions[i].getStudentName()<<endl;
			cout<<"Class: " << submissions[i].getClassName() << endl;
			cout<<"Assignment Name: " << submissions[i].getAssignmentName() << endl;
			cout << "Submission Data: " << submissions[i].getAttachedFile() << endl;
			cout<<"Scores: " << submissions[i].getscore() << endl;
			cout <<"FeedBack: " << submissions[i].getFeedback() << endl;
			cout << endl;
			}
		}
	}
	void addFileSubmission(const string& student, const string& className, const string& assignmentName,const string & fileName) // Submission if File name is provided.
	{
		if (!isPastDeadline(AMS->get_assignment(assignmentName)->getDeadline()))
		{
			if (SubmissionCount < MAX_SUBMISSIONS) {
				submissions[SubmissionCount] = Submission(student, className, assignmentName);
				submissions[SubmissionCount].file_upload(fileName);
				++SubmissionCount;
				NMS->AddNotificationForTeacher(student, className, assignmentName);
			}
			else
				cout << "Maxium Submissions have already been made !\n";
		}
		else
			cout << "Cannot create Submission with Past Deadline !\n";

	}
	void scoreSubmission(const string& student, const string& assignment, const string& feedback, const int& score)
	{
		for (int i = 0; i < SubmissionCount; ++i)
		{
			if ((submissions[i].getStudentName() == student) && (submissions[i].getAssignmentName() == assignment))
			{
				submissions[i].score_Evaluation(feedback, score);
			}
		}
	}
	void saveSubmissionsToFile(const string& filename="Submissions.txt") {

		ofstream file(filename);

		if (file.is_open()) {
			for (int i = 0; i < SubmissionCount; ++i) {
				file << submissions[i].getStudentName() << '\n';
				file << submissions[i].getAssignmentName() << '\n';
				file << submissions[i].getFeedback() << '\n';
				file << submissions[i].getscore() << '\n';
				
			}
			file.close();
			cout << "Assignments saved to file: " << filename << endl;
		}
		else {
			cout << "Unable to save assignments to file." << endl;
		}
	}
	bool isPastDeadline(const string& deadline) const {
		time_t currentTime = time(nullptr);
		tm localTimeInfo;
		localtime_s(&localTimeInfo, &currentTime);
		// Extract the day, month, and year
		int current_day = localTimeInfo.tm_mday;
		int current_month = localTimeInfo.tm_mon + 1;								// tm_mon is zero-indexed, so we add 1
		int current_year = localTimeInfo.tm_year + 1900;							// tm_year is years since 1900, so added 1900


		int day;
		int month;
		int year;
		day = (deadline[0] - '0') * 10 + (deadline[1] - '0');
		month = (deadline[3] - '0') * 10 + (deadline[4] - '0');
		year = (deadline[6] - '0') * 1000 + (deadline[7] - '0') * 100 + (deadline[8] - '0') * 10 + (deadline[9] - '0');

		if (current_year > year)
			return 1;
		else if (current_year < year)
			return 0;
		else if (current_month > month)
			return 1;
		else if (current_month < month)
			return 0;
		else if (current_day > day)
			return 1;

		return 0;

	}

};