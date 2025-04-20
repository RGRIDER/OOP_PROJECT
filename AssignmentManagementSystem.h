#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;
const int MAX_ASSIGNMENTS = 20;

class Assignment {
private:
    string title;
    string description;
    string deadline;
    string pointValue;
public:
    Assignment()                                                                                             //Default Constructor
        : title(""), description(""), deadline(""), pointValue("") {}
    Assignment(const string& title, const string& description, const string& deadline, const string& pointValue)      //Parameterized Constructor
        : title(title), description(description), deadline(deadline), pointValue(pointValue) {}

    string getTitle() const {
        return title;
    }

    string getDescription() const {
        return description;
    }

    string getDeadline() const {
        return deadline;
    }

    string getPointValue() const {
        return pointValue;
    }


};

class AssignmentManagementSystem {
private:
    Assignment assignments[MAX_ASSIGNMENTS];
    int assignmentCount;

   
public:
    int getAssignmentCount() { return assignmentCount; }
    AssignmentManagementSystem() : assignmentCount(0) {}
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
    void createAssignment(const string& title, const string& description, const string& deadline, string pointValue) {           //Creating assignment
        if (!isPastDeadline(deadline)) {
            if (assignmentCount < MAX_ASSIGNMENTS) {
                assignments[assignmentCount] = Assignment(title, description, deadline, pointValue);
                assignmentCount++;
            }
            else {
                cout << "Maximum assignment limit reached." << endl;
            }
        }
        else {
            cout << "Cannot create assignment with a past deadline." << endl;
        }
    }

    void deleteAssignmentFromSystem(const string& assignmentTitle) {
        for (int i = 0; i < assignmentCount; ++i) {
            if (assignments[i].getTitle() == assignmentTitle) {
                                                     // Shift the elements to remove the assignment from the array
                for (int j = i; j < MAX_ASSIGNMENTS-1; ++j) {
                    assignments[j] = assignments[j + 1];
                }
                cout << "Assignment \""<<assignmentTitle<<"\" has been removed.";
                assignmentCount--;
                return;
            }
        }
    }

    void saveAssignmentsToFile(const string& filename="assignments.txt") {
        
         ofstream file(filename);

        if (file.is_open()) {
            for (int i = 0; i < assignmentCount; ++i) {
                file << assignments[i].getTitle() << '\n';
                file << assignments[i].getDescription() << '\n';
                file << assignments[i].getDeadline() << '\n';
                file << assignments[i].getPointValue() << '\n';
            }
            file.close();
            cout << "Assignments saved to file: " << filename << endl;
        }
        else {
            cout << "Unable to save assignments to file." << endl;
        }
    }

    void loadAssignmentsFromFile(const string& filename) {
      
        ifstream file(filename);
        string title, description, deadline, pointValue;
       

        if (file.is_open()) {
            // Clear the existing assignments
            assignmentCount = 0;

            while (getline(file,title)) {
                getline(file, description);
                getline(file, deadline);
                getline(file, pointValue);
                createAssignment(title, description, deadline, pointValue);
            }
            file.close();
            cout << "Assignments loaded from file: " << filename << endl;
        }
        else {
            cout << "Unable to load assignments from file." << endl;
        }
    }
    Assignment* get_assignment(const string& name)
    {                                                           //function to get assigmnet object address for the Classroom class
        for (int i = 0; i < assignmentCount; ++i)
        {
            if (assignments[i].getTitle() == name)
            {
                {
                    return &assignments[i];

                }
            }
           
        }
        cout << "Assignment was not found please recheck its name !\n";
    }

};

