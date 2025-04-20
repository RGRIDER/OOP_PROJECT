#include <iostream>
#include <string>
#include"UserManagement.h"
#include"AssignmentManagementSystem.h"
#include"Notification.h"
using namespace std;

const int MAX_CLASSES = 50;
const int MAX_STUDENTS_PER_CLASS = 20;
const int MAX_ASSIGNMENTSPERCLASS = 5;

class Class {
private:
    string name;
    string subject;
    Teacher* teacher;
    string description;
    Student* enrolledStudents[MAX_STUDENTS_PER_CLASS];
    Assignment* classassignments[MAX_ASSIGNMENTSPERCLASS];
    int studentCount;
    int assignmentCount;
public:
    Class() : name(""), subject(""), teacher(nullptr), description(""), studentCount(0), classassignments{NULL},assignmentCount(0)             // Default Constructor Which intialling the array and all other values by null
    {
        for (int i = 0; i < MAX_STUDENTS_PER_CLASS; ++i) {
            enrolledStudents[i] = nullptr;
        }
    }

    Class(const string& name, const string& subject,Teacher* teacher, const string& description)         // Parameterized constructor
        : name(name), subject(subject), teacher(teacher), description(description), studentCount(0),assignmentCount(0) {}


    bool addAssignment(Assignment *assigmentptr)
    {
        if (assignmentCount < MAX_ASSIGNMENTSPERCLASS)
        {
            classassignments[assignmentCount] = assigmentptr;
            ++assignmentCount;
            return 1;

        }
        else
            cout << "Max number of assigmnets are already added cannot add more.\n";
        return 0;
    }

    void DeleteAssignment(Assignment* assigmentptr)
    {
        for (int i = 0; i < assignmentCount; ++i)
        {
            if (classassignments[i] == assigmentptr)
            {
                cout << "Successfully deleted the assignment.\n";
                if (i == MAX_ASSIGNMENTSPERCLASS - 1)
                {
                    classassignments[i] = NULL;
                    
                    return;
                }
                for (int j = i; j < MAX_ASSIGNMENTSPERCLASS; ++j)
                {
                    classassignments[j] = classassignments[j + 1];
                }
                --assignmentCount;
                return;
            }
        }
        cout << "Count'nt delete. Assignment not found!\n";
       
    }
    string getName() const {
        return name;
    }

    string getSubject() const {
        return subject;
    }

    Teacher* getTeacher() const {
        return teacher;
    }

    string getDescription() const {
        return description;
    }
    int get_studentCount() { return studentCount; }
    void addStudent(Student* student);
    void removeStudent(const string& student);
    void showClassDetails();


};



void Class::addStudent(Student* student) {
    if (studentCount < MAX_STUDENTS_PER_CLASS) {
        enrolledStudents[studentCount] = student;
        studentCount++;
    }
    else {
        cout << "Maximum student limit reached for this class !" << endl;
    }
}

void Class::removeStudent(const string& student) {
    for (int i = 0; i < studentCount; ++i) {
        if (enrolledStudents[i]->getName() == student) {
                                                                        // shift element of the array towards left to remove student
            for (int j = i; j < (studentCount - 1); ++j) {
                enrolledStudents[j] = enrolledStudents[j + 1];
            }
            studentCount--;
            return;
        }
    }
}

void Class::showClassDetails() {
    cout << "Class Name: " << name <<endl;
    cout << "Subject: " << subject <<endl;
    cout << "Teacher: " << teacher->getName() <<endl;
    cout << "Description: " << description <<endl;

    cout << "Enrolled Students: ";
    if (studentCount == 0) {
        cout << "None\0";
    }
    else {
        for (int i = 0; i < studentCount; ++i) {
            cout << enrolledStudents[i]->getName() << ", ";
        }
    }
    cout << endl<<endl;
}

class ClassManagementSystem  {
private:
    Class classes[MAX_CLASSES];
    int classCount;
    NotificationManagementSystem* NMS;                                            // Maximum 5 assignments can be assigned to a class                                  
    UserManagerSystem* UMS;

public:
    ClassManagementSystem(UserManagerSystem* UMS) : classCount(0), UMS(UMS) {   }                          //Aggregation of the user management to access all the users
   
    void setNotificationManagementSystem(NotificationManagementSystem *ptr)          // setter for notification management system
    {
        NMS = ptr;
    }
   
       void addAssignmentToClass(const string& className, Assignment* assignmentptr)
    {
        for (int i = 0; i < classCount; ++i)
        {
            if (classes[i].getName() == className)
            {
                if (classes[i].addAssignment(assignmentptr))                                     // If assignment was added returns true and also uploads notification
                {
                    NMS->AddNotificationForStudent( className, assignmentptr->getTitle(), assignmentptr->getDeadline());
                }
                return;
            }
        }
        cout << "Class name not found.Please recheck it !\n";
    }

    void removeStudentFromClass(const string& className, const string& StudentName)
    {
        for (int i = 0; i < classCount; ++i)
        {
            if (classes[i].getName()==className)
            {
                classes[i].removeStudent(StudentName);
                return;
            }
        }
        cout << "Student in the entered class not found !\n";

    }
    void removeAssignmentFromClass(const string& className, Assignment* assignmentptr)
    {
        for (int i = 0; i < classCount; ++i)
        {
            if (classes[i].getName() == className)
            {
                classes[i].DeleteAssignment(assignmentptr);
                return;
            }
        }
        cout << "Class name not found.Please recheck it !\n";
    }
    void addClassDataToFile(const string& fileName="classdata.txt")                           //  add class adata to file by deafault name "classdata" of the file
    {
        ofstream file(fileName);
        if (file.is_open())
        {
            for (int i = 0; i < classCount; ++i)
            {
                file << classes[i].getName()<<'\n';
                file << classes[i].getTeacher()->getName() << '\n';
                file << classes[i].getDescription() << '\n';
                file << classes[i].get_studentCount() << '\n';
            }
            file.close();
            cout << "Classes Data successfully stored in the file !\n";
        }
        else
            cout << "Classes data could'nt be stored in the file !\n";
    }

    void createClass(const string& name, const string& subject, const string& teacherid, const string& description) {
        
        int refrence = -2;
        Teacher* temp_pointer = UMS->get_teachers();
        for (int i = 0; i < UMS->get_teacherCount(); ++i)                //finds the index of the teacher having the given id 
        {
            if (teacherid == temp_pointer[i].get_uniqueID())
                refrence = i;
        }
        if (refrence == -2)                                        // Checks if the teacher was found or not
        {
            cout << "Teacher ID not found !\n";
            return;
        }
       
        if (classCount < MAX_CLASSES) {
            classes[classCount++] = Class(name, subject, &temp_pointer[refrence], description);       // if teacher is found creates class having the teacher of given id
        }
        else {
            cout << "Maximum class limit reached." << endl;
        }
        }

    void deleteClass(const string& className) {
        for (int i = 0; i < classCount; ++i) {
            if (className==classes[i].getName() ) {
                                                                    //  shift element of the array towards left to remove class
                for (int j = i; j < classCount - 1; ++j) {
                    classes[j] = classes[j + 1];
                }
                classCount--;
                return;
            }
        }
    }
    void add_student(string className,Student* student)
    {
        for (int i = 0; i < classCount; ++i) {
            if (classes[i].getName() == className)
            {
                classes[i].addStudent(student);
                return;
            }
        }
        cout << "--------  Student was not added ! --------------\n--------  Class not Found ! --------------\n";
    }
    void showAllClasses() {
        for (int i = 0; i < classCount; ++i) {
            classes[i].showClassDetails();
        }
    }
};

