#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // For random scores
#include <memory>
#include <bits/stdc++.h>
using namespace std;

class Student {
protected:
    string name;
    string dob;
    string schoolName;
    string courseName;
    int courseType;

public:
    Student(const string& newName, const string& newDob, const string& newSchool, const string& newCourse, const int& newCourseType)
        : name(newName), dob(newDob), schoolName(newSchool), courseName(newCourse), courseType(newCourseType) {}

    virtual void displayInfo() const {
        cout << "Name: " << name << endl;
        cout << "Date of birth: " << dob << endl;
        cout << "School name: " << schoolName << endl;
        cout << "Course name: " << courseName << endl;
    }

    virtual void DoAssignment() = 0;

    virtual void TakeTest() = 0;

    virtual void TakeExam() = 0;

    virtual int getTotalScore() = 0;

    string getName() const {
        return name;
    }

    int getCourseType() const {
        return courseType;
    }

    virtual ~Student() {}
};

class UniStudent : public Student {
private:
    vector<vector<int>> grades;

public:
    UniStudent(const string& newName, const string& newDob, const string& newSchool, const string& newCourse, const int& newCourseType)
        : Student(newName, newDob, newSchool, newCourse, newCourseType), grades(8, vector<int>(6, 0)) {}

    void displayInfo() const override {
        Student::displayInfo();
        cout << "Grades: " << endl;
        int i = 1;
        for (const auto& semester : grades) {
            cout << "Semester " << i << ": " << endl;
            cout << "Assignments: " << semester[0] << " " << semester[1] << " " << semester[2] << endl;
            cout << "Tests: " << semester[3] << " " << semester[4] << endl;
            cout << "Exam: " << semester[5] << endl;
            i++;
            cout << endl;
        }
    }

    void DoAssignment() override {
        for (auto& semester : grades) {
            semester[0] += rand() % 101;
            semester[1] += rand() % 101;
            semester[2] += rand() % 101;
        }
    }

    void TakeTest() override {
        for (auto& semester : grades) {
            semester[3] += rand() % 101;
            semester[4] += rand() % 101;
        }
    }

    void TakeExam() override {
        for (auto& semester : grades) {
            semester[5] += rand() % 101;
        }
    }

    int getTotalScore() override {
        int total = 0;
        for (const auto& semester : grades) {
            for (const auto& score : semester) {
                total += score;
            }
        }
        return total;
    }
};

class CollegeStudent : public Student {
private:
    vector<vector<int>> grades;

public:
    CollegeStudent(const string& newName, const string& newDob, const string& newSchool, const string& newCourse, const int& newCourseType)
        : Student(newName, newDob, newSchool, newCourse, newCourseType), grades(4, vector<int>(3, 0)) {}

    void displayInfo() const override {
        Student::displayInfo();
        cout << "Grades:" << endl;
        int i = 1;
        for (const auto& semester : grades) {
            cout << "Semester " << i << ": " << endl;
            cout << "Assignment: " << semester[0] << endl;
            cout << "Test: " << semester[1] << endl;
            cout << "Exam: " << semester[2] << endl;
            i++;
            cout << endl;
        }
    }

    void DoAssignment() override {
        for (auto& semester : grades) {
            semester[0] += rand() % 101;
        }
    }

    void TakeTest() override {
        for (auto& semester : grades) {
            semester[1] += rand() % 101;
        }
    }

    void TakeExam() override {
        for (auto& semester : grades) {
            semester[2] += rand() % 101;
        }
    }

    int getTotalScore() override {
        int total = 0;
        for (const auto& semester : grades) {
            for (const auto& score : semester) {
                total += score;
            }
        }
        return total;
    }
};

class StudentFactory { // Upgrade using the Factory design pattern
public:
    static unique_ptr<Student> createStudent(const string& name, const string& dob, const string& school, const string& course, const int& courseType) {
        if (courseType == 1) { // if University
            return make_unique<UniStudent>(name, dob, school, course, courseType);
        } else if (courseType == 2) { // if College
            return make_unique<CollegeStudent>(name, dob, school, course, courseType);
        } else {
            return nullptr;
        }
    }
};

void addStudent(vector<unique_ptr<Student>>& students) {
    string name, dob, schoolName, courseName;
    int courseType;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter date of birth: ";
    cin >> dob;
    cout << "Enter school name: ";
    cin >> schoolName;
    cout << "Enter course name: ";
    cin >> courseName;
    cout << "Enter course type (1 for University, 2 for College): ";
    cin >> courseType;
    auto newStudent = StudentFactory::createStudent(name, dob, schoolName, courseName, courseType);
    if (newStudent) {
        newStudent->DoAssignment();
        newStudent->TakeTest();
        newStudent->TakeExam();
        students.push_back(move(newStudent));
        cout << "Student added successfully." << endl;
    } else {
        cout << "Invalid choice." << endl;
    }
}

void removeStudent(vector<unique_ptr<Student>>& students) {
    string name;
    cout << "Enter a student to remove: ";
    cin >> name;
    auto it = find_if(students.begin(), students.end(), [&name](const unique_ptr<Student>& student) {
        return student->getName() == name;
    });
    if (it != students.end()) {
        students.erase(it);
        cout << "Student removed successfully." << endl;
    } else {
        cout << "Student not found." << endl;
    }
}

void displayStudents(const vector<unique_ptr<Student>>& students) {
    cout << "LIST OF STUDENTS" << endl;
    for (const auto& student : students) {
        student->displayInfo();
        cout << endl;
    }
}

void displayBestStudents(const vector<unique_ptr<Student>>& students) {
    int maxUni = 0;
    int maxCollege = 0;
    cout << "BEST STUDENT(S) AND THEIR SCORE(S)" << endl;
    cout << "----------------------------------" << endl;
    for (const auto& student : students) {
        if (student->getCourseType() == 2 && student->getTotalScore() > maxCollege)
            maxCollege = student->getTotalScore();
        else if (student->getCourseType() == 1 && student->getTotalScore() > maxUni)
            maxUni = student->getTotalScore();
    }
    cout << "UNIVERSITY" << endl;
    for (const auto& student : students) {
        if (student->getCourseType() == 1 && student->getTotalScore() == maxUni) {
            student->displayInfo();
        }
    }
    cout << "COLLEGE" << endl;
    for (const auto& student : students) {
        if (student->getCourseType() == 2 && student->getTotalScore() == maxCollege) {
            student->displayInfo();
        }
    }
}

int main() {
    vector<unique_ptr<Student>> students;

    int n;
    while (true) {
        cout << "1. Add a new student\n";
        cout << "2. Display all students\n";
        cout << "3. Display the best student(s)\n";
        cout << "4. Remove a student\n";
        cout << "5. Exit\n";
        cin >> n;

        switch (n) {
            case 1:
                addStudent(students);
                break;
            case 2:
                displayStudents(students);
                break;
            case 3:
                displayBestStudents(students);
                break;
            case 4:
                removeStudent(students);
                break;
            case 5:
                cout << "Exiting program.";
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}