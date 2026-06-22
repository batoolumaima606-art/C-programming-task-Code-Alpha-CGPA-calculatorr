#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Course ki maloomat ke liye structure
struct Course {
    string name;
    double gradePoints;
    double creditHours;
    string gradeLetter;
};

// Semester ki maloomat ke liye structure
struct Semester {
    int semesterNumber;
    vector<Course> courses;
    double semesterGPA;
};

// Grade letters ko points mein convert karne ka function
double convertGradeToPoints(string grade) {
    if (grade == "A" || grade == "a") return 4.0;
    if (grade == "B" || grade == "b") return 3.0;
    if (grade == "C" || grade == "c") return 2.0;
    if (grade == "D" || grade == "d") return 1.0;
    return -1.0; // Invalid Grade
}

int main() {
    int numSemesters;
    cout << "-------------------------------------------\n";
    cout << "          CODEALPHA CGPA CALCULATOR        \n";
    cout << "-------------------------------------------\n";

    // Semesters input validation
    while (true) {
        cout << "Enter the number of semesters: ";
        if (cin >> numSemesters && numSemesters > 0) {
            break;
        } else {
            cout << "Invalid input. Please enter a positive integer.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    vector<Semester> semesters;
    double totalAllSemestersCredits = 0.0;
    double totalAllSemestersGradePoints = 0.0;

    for (int i = 0; i < numSemesters; ++i) {
        Semester sem;
        sem.semesterNumber = i + 1;
        
        cout << "\n-------------------------------------------";
        cout << "\nConfiguring Semester " << sem.semesterNumber << "\n";
        cout << "-------------------------------------------\n";

        int numCourses;
        // Courses input validation
        while (true) {
            cout << "Enter the number of courses in this semester: ";
            if (cin >> numCourses && numCourses > 0) {
                break;
            } else {
                cout << "Invalid input. Please enter a positive integer.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }

        double semTotalCredits = 0.0;
        double semTotalGradePoints = 0.0;

        for (int j = 0; j < numCourses; ++j) {
            Course course;
            cout << "\nEnter details for Course " << (j + 1) << ":\n";
            
            cout << "Course Name/Code: ";
            
            // Buffer ko sirf pehli iteration par clear karein taake loop skip na ho
            if (j == 0) {
                cin.ignore(10000, '\n');
            }
            
            getline(cin, course.name);

            // Agar enter press hone se name khali reh jaye to dubara lein
            while (course.name.empty()) {
                getline(cin, course.name);
            }

            // Credit Hours Input Validation
            while (true) {
                cout << "Enter Credit Hours: ";
                if (cin >> course.creditHours && course.creditHours > 0) {
                    break;
                } else {
                    cout << "Invalid input. Credit hours must be greater than 0.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }

            // Grade Input Validation
            while (true) {
                cout << "Enter Grade (A, B, C, D, F): ";
                cin >> course.gradeLetter;
                course.gradePoints = convertGradeToPoints(course.gradeLetter);

                if (course.gradeLetter == "F" || course.gradeLetter == "f") {
                    course.gradePoints = 0.0;
                    break;
                }
                if (course.gradePoints != -1.0) {
                    break;
                }
                cout << "Invalid grade! Please enter a valid letter grade (A, B, C, D, F).\n";
            }

            semTotalCredits += course.creditHours;
            semTotalGradePoints += (course.gradePoints * course.creditHours); 
            sem.courses.push_back(course);
        }

        // Semester GPA Calculation
        sem.semesterGPA = semTotalGradePoints / semTotalCredits;
        
        // Grand Totals update
        totalAllSemestersCredits += semTotalCredits;
        totalAllSemestersGradePoints += semTotalGradePoints;

        semesters.push_back(sem);
    }

    // ----------------- DISPLAY REPORT -----------------
    cout << "\n=============================================";
    cout << "\n               ACADEMIC REPORT               ";
    cout << "\n=============================================\n";

    for (size_t i = 0; i < semesters.size(); ++i) {
        cout << "\nSemester " << semesters[i].semesterNumber << " Details:\n";
        cout << "-------------------------------------------------------\n";
        cout << left << setw(15) << "Course" 
             << setw(15) << "Credit Hours" 
             << setw(15) << "Grade Letter" 
             << setw(15) << "Grade Points" << "\n";
        cout << "-------------------------------------------------------\n";

        for (size_t j = 0; j < semesters[i].courses.size(); ++j) {
            cout << left << setw(15) << semesters[i].courses[j].name
                 << setw(15) << semesters[i].courses[j].creditHours
                 << setw(15) << semesters[i].courses[j].gradeLetter
                 << fixed << setprecision(2) << setw(15) << semesters[i].courses[j].gradePoints << "\n";
        }
        cout << "-------------------------------------------------------\n";
        cout << "Semester GPA: " << fixed << setprecision(2) << semesters[i].semesterGPA << "\n";
    }

    // Final CGPA Calculation
    double finalCGPA = totalAllSemestersGradePoints / totalAllSemestersCredits;

    cout << "\n=============================================";
    cout << "\n               FINAL OVERALL SUMMARY         ";
    cout << "\n=============================================\n";
    cout << "Total Accumulated Credits: " << totalAllSemestersCredits << "\n";
    cout << "Final Cumulative CGPA    : " << fixed << setprecision(2) << finalCGPA << "\n";
    cout << "=============================================\n";

    return 0;
}