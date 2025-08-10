#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    string name;
    int roll;
    int marks[5];
    float percentage;
    char grade;
};

char calculateGrade(float percent) {
    if (percent >= 80) return 'A';
    else if (percent >= 60) return 'B';
    else if (percent >= 40) return 'C';
    else return 'F';
}

void addStudent() {
    Student s;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "Enter roll number: ";
    cin >> s.roll;

    int total = 0;
    cout << "Enter marks in 5 subjects: ";
    for (int i = 0; i < 5; i++) {
        cin >> s.marks[i];
        total += s.marks[i];
    }

    s.percentage = total / 5.0;
    s.grade = calculateGrade(s.percentage);

    ofstream file("students.txt", ios::app);
    file << s.name << "," << s.roll << ",";
    for (int i = 0; i < 5; i++) file << s.marks[i] << ",";
    file << s.percentage << "," << s.grade << endl;
    file.close();

    cout << "\nRecord added successfully!\n";
}

void viewAllStudents() {
    ifstream file("students.txt");
    if (!file) {
        cout << "No records found.\n";
        return;
    }
    string line;
    cout << "\n--- Student Records ---\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

void searchStudent() {
    int roll;
    cout << "Enter roll number to search: ";
    cin >> roll;
    ifstream file("students.txt");
    if (!file) {
        cout << "No records found.\n";
        return;
    }
    string name;
    int r, marks[5];
    float percentage;
    char grade;
    bool found = false;
    while (file) {
        file >> ws;
        getline(file, name, ',');
        file >> r;
        file.ignore();
        for (int i = 0; i < 5; i++) {
            file >> marks[i];
            file.ignore();
        }
        file >> percentage;
        file.ignore();
        file >> grade;
        file.ignore();
        if (file && r == roll) {
            found = true;
            cout << "\n--- Student Found ---\n";
            cout << "Name: " << name << "\nRoll: " << r;
            cout << "\nMarks: ";
            for (int i = 0; i < 5; i++) cout << marks[i] << " ";
            cout << "\nPercentage: " << percentage;
            cout << "\nGrade: " << grade << endl;
            break;
        }
    }
    if (!found) cout << "Student not found.\n";
    file.close();
}

int main() {
    int choice;
    do {
        cout << "\n--- Student Record & Marks Manager ---\n";
        cout << "1. Add Student\n2. View All Students\n3. Search Student\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewAllStudents(); break;
            case 3: searchStudent(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);
    return 0;
}
