#include "file_management.hpp"
#include <string>
#include <iostream>
#include <utils/clear.hpp>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <utils/terminal_input.hpp>
#include <format>
using std::format;

const std::string NAME = "main.cpp";

using std::vector, std::string, std::cout, std::cin;

double roundPrec(double num, int precision) {
    int temp = num * (std::pow(10,precision));
    return (double)temp / (std::pow(10,precision));
}

//int and double (overload)
double average(const vector<int> &nums, const int& precision = 2) {
    if (nums.empty()) return 0;
    double sum = 0;
    for (double num : nums) sum += num;
    return roundPrec((sum / nums.size()), precision);
}
double average(const vector<double> &nums, const int& precision = 2) {
    if (nums.empty()) return 0;
    double sum = 0;
    for (double num : nums) sum += num;
    return roundPrec((sum / nums.size()), precision);
}

struct Subject {
    string name;
    std::vector<int> grades;
    double average = 0;
};

vector<Subject> loadSubjects() {
    Log::SignatureScope scope(logs, NAME + "/loadSubjects()");
    logs.write("Loading subjects...\n");
    json data = file::loadData();
    if (data == NO_DATA_ERRCODE || data == FAILED_FILE_ERRCODE) {
        logs.write("Fatal error when loading data, check code/paths/permisions.\n", MessageType::Fatal);
        exit(1);
    }

    vector<Subject> subjects;
    logs.write("Loading subjects from json list items\n");
    for (const auto& [key, val] : data.items()) {
        Subject s;
        s.name = key;
        s.grades = val.get<vector<int>>();
        subjects.push_back(s);
    }
    return subjects;
}

void saveSubjects(vector<Subject> ss) {
    Log::SignatureScope scope(logs, NAME + "/saveSubjects()");
    logs.write("Converting subjects into json data...\n");
    json data;
    for (const Subject s : ss) data[s.name] = s.grades;
    logs.write("Saving data...\n");
    file::saveData(data);
}

void printGrades(vector<Subject> ss) {
    Log::SignatureScope scope(logs, NAME + "/printGrades()");
    logs.write("Printing all grades in order of subjects...\n");
    if (ss.empty()) {
        cout << "No subjects or grades yet!\n\n";
        return;
    }
    for(const Subject s : ss) {
        for(const int grade : s.grades) {
            cout << format("Subject: {}", s.name);
            for (int i = 15 - s.name.size(); i > 0; i--) {
                cout << " ";
            }
            cout << format("Grade: {}\n", grade);
        }
        cout << std::endl;
    }
    cout << std::endl;
}

void newSubject(vector<Subject> &subjects) {
    Log::SignatureScope scope(logs, NAME + "/newSubject()");
    logs.write("Creating new subject...\n");
    cout << "Enter new subject name\n";
    Subject n;
    getline(cin, n.name);
    subjects.push_back(n);
}

void addGrade(vector<Subject> &subjects) {
    Log::SignatureScope scope(logs, NAME + "/addGrade()");
    logs.write("Adding a new grade...\n");
    //Choose from subjects
    for (size_t i = 0; i < subjects.size(); i++) {
        cout << format("{}. {}\n", i + 1, subjects.at(i).name);
    } cout << format("{}. New...", subjects.size() + 1);
    int choice = input::getUserInput(1, subjects.size() + 1);
    if (choice == subjects.size() + 1) {
        newSubject(subjects);
    }

    //Get grade
    cout << "Okay. Now input your grade:\n";
    int grade = input::getUserInput(1, 10);
    subjects.at(choice - 1).grades.push_back(grade);
    cout << "Grade successfully added!\n";
    clear::hold();
}

void printAverages(vector<Subject> subjects) {
    if (subjects.empty()) {
        cout << "No subjects/grades yet!\n";
        clear::hold();
        return;
    }
    vector<double> subjectAvgs;
    vector<int> allGrades;
    for (Subject &s : subjects) {
        s.average = average(s.grades);
        subjectAvgs.push_back(s.average);
        for (int grade : s.grades) {
            allGrades.push_back(grade);
        }
    }
    double subjectsAvg = average(subjectAvgs);
    double allGradesAvg = average(allGrades);

    clear::clearScreen();
    cout << "Averages per subject:\n";
    for (const Subject &s : subjects) {
        cout << format("{}:", s.name);
        for (int i = 15 - s.name.size(); i > 0; i--) {
            cout << " ";
        }
        cout << format("{}\n", s.average);
    } cout << std::endl;

    cout << format("Total average based on subjects' averages: {}\
                    \nTotal average based on all grades' average: {}\n\n\n",
                    subjectsAvg, allGradesAvg);
    
}

void removeGrade(vector<Subject> &subjects) {
    if (subjects.empty()) {
        cout << "There are no subjects/grades yet!\n";
        clear::hold();
        return;
    }
    Log::SignatureScope scope(logs, NAME + "/removeGrade");
    logs.write("Removing a grade...\n");
    cout << "Choose subject to remove grade from:\n";
    for (size_t i = 0; i < subjects.size(); i++) {
        cout << format("{}. {}\n", i + 1, subjects.at(i).name);
    }
    int subjectChoice = input::getUserInput(1, subjects.size());
    logs.write(format("Subject chosen: {}\n", subjects.at(subjectChoice - 1).name));
    Subject chosen = subjects.at(subjectChoice - 1);

    clear::clearScreen();
    cout << "Which grade do you want to remove?\n0. Remove whole subject\n";
    for (size_t i = 0; i < chosen.grades.size(); i++) {
        cout << format("{}. {}\n", i + 1, chosen.grades.at(i));
    }
    int gradeChoice = input::getUserInput(0, chosen.grades.size());
    logs.write(format("Chosen grade: {}\n", (gradeChoice == 0) ? "Remove subject" : std::to_string(chosen.grades.at(gradeChoice - 1))));
    if (gradeChoice == 0) {
        subjects.erase(subjects.begin() + (subjectChoice - 1));
        logs.write("Successfully erased subject from vector.\n");
        return;
    }
    chosen.grades.erase(chosen.grades.begin() + (gradeChoice - 1));
    logs.write("Successfully erased grade\n");
}

void printMainMenu() {
    cout <<
    "Choose from one of the options below:\n\
    1.Show all grades by subjects\n\
    2.Add grade\n\
    3.Show averages\n\
    4.Remove grade\n\
    5.Quit\n";
}

int main () {
    platform::setAppName(APPNAME);
    logs.setStream(file::makeLog());
    Log::SignatureScope scope(logs, NAME + "/main()");
    logs.write("Line breaks\n\n\n\n");
    logs.write("Started main function. Starting app...\n");
    clear::clearScreen();
    cout << "Welcome to grade-tracker!\n";
    vector<Subject> subjects = loadSubjects();
    logs.write("Loaded subjects. Starting input loop\n");
    while(true) {
        printMainMenu();
        int input = input::getUserInput(1, 5);
        logs.write(format("Input index chosen: {}\n", input));
        switch(input) {
            case 5: 
            saveSubjects(subjects);
            return 0;
            case 1: 
                clear::clearScreen();
                printGrades(subjects);
                clear::hold();
                break;
            case 2:
                addGrade(subjects); break;
            case 3:
                printAverages(subjects); 
                clear::hold(); 
                break;
            case 4:
                removeGrade(subjects);
                clear::clearScreen();
        }
    }
}