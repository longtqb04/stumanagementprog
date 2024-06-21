#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // For random scores
using namespace std;

class Student {
private:
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
        cout << "Grades:" << endl;
        for (size_t i = 0; i < 8; i++) {
            cout << "Semester " << i + 1 << ":" << endl;
            cout << "Assignments: " << grades[i][0] << " " << grades[i][1] << " " << grades[i][2] << endl;
            cout << "Tests: " << grades[i][3] << " " << grades[i][4] << endl;
            cout << "Exam: " << grades[i][5] << endl;
        }
    }

    void DoAssignment() override {
        for (size_t i = 0; i < 8; i++) {
            for (size_t j = 0; j < 3; j++) {
                grades[i][j] += rand() % 101;
            }
        }
    }

    void TakeTest() override {
        for (size_t i = 0; i < 8; ++i) {
            for (size_t j = 3; j < 5; ++j) {
                grades[i][j] += rand() % 101;
            }
        }
    }

    void TakeExam() override {
        for (size_t i = 0; i < 8; ++i) {
            grades[i][5] += rand() % 101;
        }
    }

    int getTotalScore() override {
        int total = 0;
        for (size_t i = 0; i < 8; ++i) {
            for (size_t j = 0; j < 6; ++j) {
                total += grades[i][j];
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
        for (size_t i = 0; i < grades.size(); i++) {
            cout << "Semester " << i + 1 << ":" << endl;
            cout << "Assignment: " << grades[i][0] << endl;
            cout << "Test: " << grades[i][1] << endl;
            cout << "Exam: " << grades[i][2] << endl;
        }
    }

    void DoAssignment() override {
        for (int i = 0; i < 4; i++) {
            grades[i][0] += rand() % 101;
        }
    }

    void TakeTest() override {
        for (int i = 0; i < 4; i++) {
            grades[i][1] += rand() % 101;
        }
    }

    void TakeExam() override {
        for (size_t i = 0; i < 4; i++) {
            grades[i][2] += rand() % 101;
        }
    }

    int getTotalScore() override {
        int total = 0;
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                total += grades[i][j];
            }
        }
        return total;
    }
};

void addStudent(Student**& students, int& numStudents) {
    string name;
    string dob;
    string schoolName;
    string courseName;
    int courseType;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter date of birth: ";
    cin >> dob;
    cout << "Enter name of school: ";
    cin >> schoolName;
    cout << "Enter name of course: ";
    cin >> courseName;
    cout << "Enter course type (1 for University, 2 for College): ";
    cin >> courseType;

    if (courseType == 1) { // If university student
        Student* newStudent = new UniStudent(name, dob, schoolName, courseName, courseType);
        Student** newStudents = new Student*[numStudents + 1];

        for (int i = 0; i < numStudents; i++) {
            newStudents[i] = students[i];
        }
        newStudents[numStudents] = newStudent;
        newStudents[numStudents]->DoAssignment();
        newStudents[numStudents]->TakeTest();
        newStudents[numStudents]->TakeExam();
        delete [] students;
        students = newStudents;
        numStudents++;
    }
    else if (courseType == 2) { // If college student
        Student* newStudent = new CollegeStudent(name, dob, schoolName, courseName, courseType);
        Student** newStudents = new Student*[numStudents + 1];

        for (int i = 0; i < numStudents; i++) {
            newStudents[i] = students[i];
        }
        newStudents[numStudents] = newStudent;
        newStudents[numStudents]->DoAssignment();
        newStudents[numStudents]->TakeTest();
        newStudents[numStudents]->TakeExam();
        delete [] students;
        students = newStudents;
        numStudents++;
    }
    else {
        cout << "Invalid choice." << endl;
        return;
    }

    cout << "Student added successfully." << endl;
}

void removeStudent(Student**& students, int& numStudents) {
    string name;
    cout << "Enter a student to remove: ";
    cin >> name;
    for (int i = 0; i < numStudents; i++) {
        if (students[i]->getName() == name) {
            delete students[i];
            for (int j = i; j < numStudents; j++) {
                students[j] = students[j + 1];
            }
            numStudents--;
            cout << "Student removed successfully." << endl;
            return;
        }
    }
    cout << "Student not found." << endl;
}

void displayStudents(Student** students, int numStudents) {
    cout << "LIST OF STUDENTS" << endl;
    for (int i = 0; i < numStudents; i++) {
        students[i]->displayInfo();
        cout << endl;
    }
}

void displayBestStudents(Student** students, int numStudents) {
    int maxUni = 0;
    int maxCollege = 0;

    cout << "BEST STUDENT(S) AND THEIR SCORE(S)" << endl;
    cout << "----------------------------------" << endl;
    for (int i = 0; i < numStudents; i++) {
        if (students[i]->getCourseType() == 2 && students[i]->getTotalScore() > maxCollege)
            maxCollege = students[i]->getTotalScore();
        else if (students[i]->getCourseType() == 1 && students[i]->getTotalScore() > maxUni)
            maxUni = students[i]->getTotalScore();
    }
    cout << "UNIVERSITY" << endl;
    for (int i = 0; i < numStudents; i++) {
        if (students[i]->getCourseType() == 1 && students[i]->getTotalScore() == maxUni) {
            students[i]->displayInfo();
        }
    }
    cout << "COLLEGE" << endl;
    for (int i = 0; i < numStudents; i++) {
        if (students[i]->getCourseType() == 2 && students[i]->getTotalScore() == maxCollege) {
            students[i]->displayInfo();
        }
    }
}

int main() {
    Student** students = nullptr;
    int numStudents = 0;

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
                addStudent(students, numStudents);
                break;
            case 2:
                displayStudents(students, numStudents);
                break;
            case 3:
                displayBestStudents(students, numStudents);
                break;
            case 4:
                removeStudent(students, numStudents);
                break;
            case 5:
                cout << "Exiting program.";
                for (int i = 0; i < numStudents; ++i) {
                    delete students[i];
                }
                delete [] students;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
