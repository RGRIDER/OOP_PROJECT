#pragma once
#include"Submission.h"
#include"fstream"
#include"string"
#include<iostream>
using namespace std;
class Grade
{
	char cumulativeGrade;
	int weightageSetting; //Parameter
	int classWeightage;
	int StudentWeightage;
	SubmissionManagementSystem* SmS;
	Submission* allsubmissions;
public:
	void storeGradeDataToFile(const string& filename="GradeData.txt")       // File Handling
	{
		ofstream file(filename);
		if (file.is_open())
		{
			file << cumulativeGrade << '\n';
			file <<weightageSetting  << '\n';
			file <<classWeightage  << '\n';
			file << StudentWeightage << '\n';
		}

	}
	void LoadGradeDataToFile(const string& filename = "GradeData.txt")       // File Handling
	{
		ifstream file(filename);
		if (file.is_open())
		{
			file >> cumulativeGrade;
			file >> weightageSetting;
			file >> classWeightage;
			file >> StudentWeightage;
		}

	}
	void DisplayGradeSystem()
	{
		cout << "Comulative Grade: " << cumulativeGrade << endl;
		cout << "Weightage Setting: " << weightageSetting << endl;
		cout << "Student Weightage: " << StudentWeightage << endl;
		cout << "Class Average Weightage: " << classWeightage << endl;
		
	}
	Grade(SubmissionManagementSystem* SMS,int weigtage=10)	
	{
		weightageSetting = weigtage;
		SmS = SMS;
		allsubmissions = SmS->Get_Submissions();
	};
	int get_classAverage(Submission * ptr)
	{
		int marks = 0,count=0;
		string classNAME = ptr->getClassName();
		string ASSigmentname = ptr->getAssignmentName();

		for (int i = 0; i < SmS->Get_SubmissionCount(); ++i)
		{
			if ((allsubmissions[i].getClassName() == classNAME) && (allsubmissions[i].getAssignmentName()==ASSigmentname))
			{
				++count;
				marks += allsubmissions[i].getscore();
			}
		}
		return marks / count;
	}
	void calculateStudentCumultativeGrade(const string& studentName)
	{
		int classAvg = 0;
		bool checkthatstudentFound = 0;
		int total_marks = 0;
		int obtained_marks = 0;
		const int count= SmS->Get_SubmissionCount();
		for (int i = 0; i <count; ++i)             //loop to see all submissions
		{
			if (studentName == allsubmissions[i].getStudentName())
			{
				checkthatstudentFound = 1;
				classAvg += get_classAverage(&allsubmissions[i]);
				obtained_marks += allsubmissions[i].getscore();
				total_marks += SmS->get_assignmentPointValue(allsubmissions[i].getAssignmentName());					//get total marks of assignment
			}
		}
		if (checkthatstudentFound) {
			classWeightage = ((classAvg * weightageSetting) / total_marks);         // Calculate the Absolute of both student and class
			StudentWeightage = ((obtained_marks * weightageSetting) / total_marks);

			obtained_marks = ((obtained_marks * 100) / total_marks);                                //Assign Grade

			if (obtained_marks <= 50)
				cumulativeGrade = 'F';
			else if (obtained_marks > 50 && obtained_marks <= 60)
				cumulativeGrade = 'D';
			else if (obtained_marks > 60 && obtained_marks <= 70)
				cumulativeGrade = 'C';
			else if (obtained_marks > 70 && obtained_marks <= 80)
				cumulativeGrade = 'B';
			else if (obtained_marks > 80 && obtained_marks <= 100)
				cumulativeGrade = 'A';
		}
		else
			cout << "Student "<< studentName <<" has not done any Submissions yet !\n";
	}

};
