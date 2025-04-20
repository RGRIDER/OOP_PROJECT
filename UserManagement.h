#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_TEACHERS = 20;

string encryptCaesarCipher(const string& input, int shift = 5) {
	string encryptedText;
	for (char c : input) {
		if (isalpha(c)) {
			char base = islower(c) ? 'a' : 'A';
			char encryptedChar = (c - base + shift) % 26 + base;
			encryptedText.push_back(encryptedChar);
		}
		else {
			encryptedText.push_back(c);
		}
	}
	return encryptedText;
}
bool ValidationOfCode(const string& pass)
{
	bool uppercase = 0, lowercase = 0, length = 0;
	for (int i = 0; pass[i] != '\0'; ++i)
	{
		int x = pass[i];
		if (i >= 6)
			length = true;
		if (x > 64 && x < 91)
			uppercase = true;
		if (x > 96 && x < 123)
			lowercase = 1;
	}
	return  (uppercase && lowercase && length);
}

class User
{
protected:
	string name;
	string email;
	string	uniqueID;
	string password;

public:
	static int total_instance;
	User() {};
	User(string name, string email, string password) :         //constructor
		name(name), email(email) {

		this->password=encryptCaesarCipher(password);			//	adding encrypted password
		
		uniqueID =to_string( total_instance);
		++total_instance;
	};
	
	virtual bool authenticate(const string& input_email, const string& input_password) = 0 {}
	//Getters
	string getName() { return name; };
	string get_uniqueID() { return uniqueID; };
	string get_email() { return email; };
	string get_password() { return password; };
	//Setters
	void set_name(const string& newName) { name = newName; }
	void set_uniqueID(const string& newUniqueID) { uniqueID = newUniqueID; }
	void set_email(const string& newEmail) { email = newEmail; }
	void set_password(const string& newPassword) { password = newPassword; }
	
};
int User::total_instance = 0;



class Student :public User
{

private:
	string role;
public:
	Student(): role("Student") {}
	Student(string name, string email, string password) :
		User(name, email, password), role("Student") {};
	bool authenticate(const string& input_email, const string& input_password)
	{
		string str = encryptCaesarCipher(input_password);
		
		bool check = ((password == str) && (email == input_email));
		return  check;
	}
	
};

class Teacher :public User
{
private:
	string role;
public:
	Teacher():role("Teacher") {}
	Teacher(string name, string email, string password) :
		User(name, email, password),role("Teacher") {};
	bool authenticate(const string& input_email, const string& input_password)
	{
		string str = encryptCaesarCipher(input_password);
		
		bool check = ((password == str) && (email == input_email));
		return  check;
	}

};

class UserManagerSystem {
protected:
	Teacher teachers[MAX_TEACHERS];
	Student students[MAX_STUDENTS];
	int teacherCount;
	int studentCount;
public:
	UserManagerSystem() : teacherCount(0), studentCount(0){};
	//friend class ClassManagementSystem;

	void registerUser(const string& name, const string& email, const string& password, bool isStudent) {
		
		if (!ValidationOfCode(password))
		{
			cout << "User \""<<name<<"\" not Registered!\n Password size must be greater than 7 and it must contain both uppercase and lover case Albhabets.\n";
			return;
		}
		if ((!isStudent) && teacherCount < MAX_TEACHERS) {
			teachers[teacherCount] = Teacher(name, email, password);
			++teacherCount;
		}
		else if (isStudent && studentCount < MAX_STUDENTS) {
			students[studentCount] =Student(name, email, password);
			++studentCount;
		}
		else {
			cout << "Maximum user limit reached." << endl;
		}
	}

	Teacher* authenticateTeacher(const string& email, const string& password) {
		for (int i = 0; i < teacherCount; ++i) {
			if (teachers[i].authenticate(email,password)) {
				return &teachers[i];
			}
		}

		cout << "Either email or Password is incorrect";
		return nullptr;
	}

	Student* authenticateStudent(const string& email, const string& password)
	{
		for (int i = 0; i < studentCount; ++i)
		{
			if (students[i].authenticate(email, password)) {
				return &students[i];
			}
		}
		cout << "Either email or Password is incorrect";
		return nullptr;
	}

	void saveStudentsToFile(const string filename = "Student.txt")
	{
		ofstream file(filename);

		if (file.is_open()) {
			for (int i = 0; i < studentCount; ++i) {
				file << students[i].getName() << '\n';
				file << students[i].get_email() << '\n';
				file << students[i].get_password()<< '\n';
				file << students[i].get_uniqueID() << '\n';
			}
			file.close();
			cout << "Students saved to file: " << filename << endl;
		}
		else {
			cout << "Unable to save Students to file." << endl;
		}
	
	}
	void saveTeachersToFile(const string filename = "Teachers.txt")
	{
		ofstream file(filename);

		if (file.is_open()) {
			for (int i = 0; i < teacherCount; ++i) {
				file << teachers[i].getName() << '\n';
				file << teachers[i].get_email() << '\n';
				file << teachers[i].get_password() << '\n';
				file << teachers[i].get_uniqueID() << '\n';
			}
			file.close();
			cout << "Teachers saved to file: " << filename << endl;
		}
		else {
			cout << "Unable to save Teachers to file." << endl;
		}

	}
	void LoadStudentsFromaFile(const string filename = "Student.txt")
	{
		ifstream file(filename);
		string name, email, password, id;


		if (file.is_open()) {
			studentCount = 0;

			while (getline(file, name)) {
				getline(file, email);
				getline(file, password);
				getline(file, id);
				registerUser(name,email,password,true);
				students[studentCount - 1].set_uniqueID(id);
			}
			file.close();
			cout << "Students loaded from file: " << filename << endl;
		}
		else {
			cout << "Students to load assignments from file." << endl;
		}
	}
	void LoadTeachersFromaFile(const string filename = "Teachers.txt")
	{
		ifstream file(filename);
		string name, email, password, id;


		if (file.is_open()) {
		teacherCount = 0;

			while (getline(file, name)) {
				getline(file, email);
				getline(file, password);
				getline(file, id);
				registerUser(name, email, password, false);
				teachers[teacherCount - 1].set_uniqueID(id);
			}
			file.close();
			cout << "Teachers loaded from file: " << filename << endl;
		}
		else {
			cout << "Teachers to load assignments from file." << endl;
		}


	}

	void display()
	{
		
		cout << "\nTeachers:" << endl;
		for (int i = 0; i < teacherCount; ++i) {
			cout<<i+1<<"- " << teachers[i].getName()<<endl;
		
		}
		cout << "\nStudets:" << endl;
		for (int i = 0; i < studentCount; ++i){
			cout<<i + 1 << "- " <<students[i].getName()<<endl;
			
		}
	}
	Teacher* get_teachers()
	{
		return &teachers[0];
	}
	Student* get_students()
	{
		return &students[0];
	}
	int get_teacherCount()
	{
		return teacherCount;
	}
	int get_studentCount()
	{
		return studentCount;
	}

	void displayFullUMS()
	{

		cout << "\nTeachers:" << endl;
		for (int i = 0; i < teacherCount; ++i) {
			cout  << teachers[i].getName() << endl;
			cout << teachers[i].get_email() << endl;
			cout << teachers[i].get_password() << endl;
			cout << teachers[i].get_uniqueID() << endl<<endl;
		}
		cout << "\nStudets:" << endl;
		for (int i = 0; i < studentCount; ++i) {
			cout  << students[i].getName() << endl;
			cout << students[i].get_email() << endl;
			cout << students[i].get_password() << endl;
			cout << students[i].get_uniqueID() << endl<<endl;

		}
	}
};

