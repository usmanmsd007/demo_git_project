#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

// Student class to store student information and results
class Student {
private:
    int rollNumber;
    string name;
    vector<int> marks;
    int totalMarks;
    float percentage;
    string grade;

public:
    // Constructor
    Student(int roll, string n, vector<int> m) {
        rollNumber = roll;
        name = n;
        marks = m;
        calculateResults();
    }

    // Calculate total marks, percentage, and grade
    void calculateResults() {
        totalMarks = 0;
        for (int mark : marks) {
            totalMarks += mark;
        }
        percentage = (float)totalMarks / marks.size();
        
        // Assign grade based on percentage
        if (percentage >= 90) grade = "A+";
        else if (percentage >= 80) grade = "A";
        else if (percentage >= 70) grade = "B";
        else if (percentage >= 60) grade = "C";
        else if (percentage >= 50) grade = "D";
        else grade = "F";
    }

    // Getters
    int getRollNumber() const { return rollNumber; }
    string getName() const { return name; }
    int getTotalMarks() const { return totalMarks; }
    float getPercentage() const { return percentage; }
    string getGrade() const { return grade; }
    vector<int> getMarks() const { return marks; }

    // Display student result
    void displayResult() const {
        cout << "\n========================================\n";
        cout << "STUDENT RESULT CARD\n";
        cout << "========================================\n";
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Name: " << name << endl;
        cout << "----------------------------------------\n";
        cout << "Subject-wise Marks:\n";
        for (size_t i = 0; i < marks.size(); i++) {
            cout << "  Subject " << (i + 1) << ": " << marks[i] << endl;
        }
        cout << "----------------------------------------\n";
        cout << "Total Marks: " << totalMarks << "/" << (marks.size() * 100) << endl;
        cout << fixed << setprecision(2);
        cout << "Percentage: " << percentage << "%" << endl;
        cout << "Grade: " << grade << endl;
        cout << "========================================\n";
    }
};

// StudentManagement class to manage multiple students
class StudentManagement {
private:
    vector<Student> students;
    int numSubjects;

public:
    StudentManagement(int subjects) : numSubjects(subjects) {}

    // Add a new student
    void addStudent() {
        int roll;
        string name;
        vector<int> marks;

        cout << "\n--- Add New Student ---\n";
        cout << "Enter Roll Number: ";
        cin >> roll;
        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, name);

        cout << "Enter marks for " << numSubjects << " subjects:\n";
        for (int i = 0; i < numSubjects; i++) {
            int mark;
            do {
                cout << "  Subject " << (i + 1) << " (0-100): ";
                cin >> mark;
                if (mark < 0 || mark > 100) {
                    cout << "  Invalid! Enter marks between 0-100.\n";
                }
            } while (mark < 0 || mark > 100);
            marks.push_back(mark);
        }

        students.push_back(Student(roll, name, marks));
        cout << "\nStudent added successfully!\n";
    }

    // Display all students
    void displayAllStudents() const {
        if (students.empty()) {
            cout << "\nNo students found!\n";
            return;
        }

        cout << "\n========================================\n";
        cout << "ALL STUDENTS RESULTS\n";
        cout << "========================================\n";
        cout << left << setw(10) << "Roll No" 
             << setw(20) << "Name" 
             << setw(12) << "Total" 
             << setw(12) << "Percentage" 
             << setw(8) << "Grade" << endl;
        cout << "----------------------------------------\n";

        for (const auto& student : students) {
            cout << left << setw(10) << student.getRollNumber()
                 << setw(20) << student.getName()
                 << setw(12) << student.getTotalMarks()
                 << fixed << setprecision(2) << setw(12) << student.getPercentage() << "%"
                 << setw(8) << student.getGrade() << endl;
        }
        cout << "========================================\n";
    }

    // Search student by roll number
    void searchStudent() const {
        if (students.empty()) {
            cout << "\nNo students found!\n";
            return;
        }

        int roll;
        cout << "\nEnter Roll Number to search: ";
        cin >> roll;

        auto it = find_if(students.begin(), students.end(),
                         [roll](const Student& s) { return s.getRollNumber() == roll; });

        if (it != students.end()) {
            it->displayResult();
        } else {
            cout << "\nStudent with Roll Number " << roll << " not found!\n";
        }
    }

    // Display top performers
    void displayTopPerformers() const {
        if (students.empty()) {
            cout << "\nNo students found!\n";
            return;
        }

        vector<Student> sortedStudents = students;
        sort(sortedStudents.begin(), sortedStudents.end(),
             [](const Student& a, const Student& b) {
                 return a.getPercentage() > b.getPercentage();
             });

        cout << "\n========================================\n";
        cout << "TOP PERFORMERS\n";
        cout << "========================================\n";
        
        int count = min(5, (int)sortedStudents.size());
        for (int i = 0; i < count; i++) {
            cout << "\n" << (i + 1) << ". " << sortedStudents[i].getName()
                 << " (Roll: " << sortedStudents[i].getRollNumber() << ")"
                 << " - " << fixed << setprecision(2) 
                 << sortedStudents[i].getPercentage() << "% - Grade: "
                 << sortedStudents[i].getGrade() << endl;
        }
        cout << "========================================\n";
    }

    // Get class statistics
    void displayStatistics() const {
        if (students.empty()) {
            cout << "\nNo students found!\n";
            return;
        }

        float totalPercentage = 0;
        int passCount = 0;
        int failCount = 0;

        for (const auto& student : students) {
            totalPercentage += student.getPercentage();
            if (student.getPercentage() >= 50) {
                passCount++;
            } else {
                failCount++;
            }
        }

        float avgPercentage = totalPercentage / students.size();

        cout << "\n========================================\n";
        cout << "CLASS STATISTICS\n";
        cout << "========================================\n";
        cout << "Total Students: " << students.size() << endl;
        cout << "Passed: " << passCount << endl;
        cout << "Failed: " << failCount << endl;
        cout << fixed << setprecision(2);
        cout << "Class Average: " << avgPercentage << "%" << endl;
        cout << "Pass Percentage: " << (passCount * 100.0 / students.size()) << "%" << endl;
        cout << "========================================\n";
    }
};

// Main function
int main() {
    int numSubjects;
    
    cout << "========================================\n";
    cout << "STUDENT RESULTS MANAGEMENT SYSTEM\n";
    cout << "========================================\n";
    cout << "Enter number of subjects: ";
    cin >> numSubjects;

    StudentManagement sm(numSubjects);
    int choice;

    do {
        cout << "\n========================================\n";
        cout << "MAIN MENU\n";
        cout << "========================================\n";
        cout << "1. Add New Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by Roll Number\n";
        cout << "4. Display Top Performers\n";
        cout << "5. Display Class Statistics\n";
        cout << "0. Exit\n";
        cout << "========================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                sm.addStudent();
                break;
            case 2:
                sm.displayAllStudents();
                break;
            case 3:
                sm.searchStudent();
                break;
            case 4:
                sm.displayTopPerformers();
                break;
            case 5:
                sm.displayStatistics();
                break;
            case 0:
                cout << "\nThank you for using Student Results Management System!\n";
                break;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
