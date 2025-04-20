
# 📚 Google Classroom Inspired System - OOP Project in C++

## 👨‍💻 Project Info

This project is a **C++ console-based application** inspired by **Google Classroom**, developed using core **Object-Oriented Programming (OOP)** concepts. It simulates a classroom management system that allows teachers and students to interact through classes, assignments, submissions, grading, and notifications.

---

## 👨‍🏫 Developed By

- **Name:** Haider Zia  
- **Roll Number:** 22I-1196  
- **Section:** CS-C  
- **Semester:** Summer 2023

---

## 🧠 OOP Concepts Used

- **Encapsulation:** Data members are encapsulated within their respective classes.
- **Abstraction:** Functionalities like grading, submission, and class management are abstracted into separate classes.
- **Inheritance:** Common behaviors shared among users (students and teachers).
- **Polymorphism:** Overloaded functions for submission types and other features.
- **Modularity:** Code is separated into multiple files for better organization (`UserManagement.h`, `Submission.h`, etc.).

---

## 💡 Features

1. **User Management System**
   - Register and authenticate students and teachers.
   - Manage user information and persistence.

2. **Class Management**
   - Create and manage virtual classes.
   - Add or remove students.
   - Assign assignments to classes.

3. **Assignment Management**
   - Teachers can create and delete assignments.
   - Assignments include title, description, deadline, and marks.

4. **Submission System**
   - Students can submit assignments as text or file.
   - Teachers can grade submissions with marks and comments.

5. **Gradebook**
   - Calculate and store cumulative grades for each student.

6. **Notification System**
   - Students and teachers receive notifications about assignments and grades.

---

## 🗃️ File Structure

- `main.cpp` - Driver code to simulate the entire system.
- `UserManagement.h` - Handles registration and login logic.
- `ClassManagement.h` - Manages classroom creation and student enrollment.
- `AssignmentManagementSystem.h` - Handles assignment creation and storage.
- `Submission.h` - Handles assignment submissions and grading.
- `GradeBook.h` - Calculates cumulative grades.
- `NotificationSystem.h` - Sends notifications to students and teachers.

---

## ⚙️ How to Run

1. Clone or download the repository.
2. Compile using any C++ compiler (e.g., g++, Code::Blocks).
3. Run the executable.

```bash
g++ main.cpp -o classroomApp
./classroomApp
```
---

## 💬 Final Notes

This project showcases a strong understanding of OOP principles and simulates real-world classroom operations within a console-based application. It can be further extended to include GUI support or file-based authentication.

---

> 🎓 *"Code is like humor. When you have to explain it, it’s bad." – Cory House*

---
