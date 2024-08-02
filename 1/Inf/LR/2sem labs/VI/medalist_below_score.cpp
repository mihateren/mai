#include <iostream>
#include <fstream>
#include "person.h"
#include <iomanip>


using namespace std;

int atoi(const char* str) {
    int res = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] < '0' || str[i] > '9') {
            return -1;
        }
        res = res * 10 + str[i] - '0';
    }
    return res;
}

void printMedalistBelowScore(const char* filename, int score) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file" << endl;
        return;
    }

    Applicant applicant;
    while (file.read(reinterpret_cast<char*>(&applicant), sizeof(Applicant))) {
        if (applicant.medal && applicant.score < score) {
            cout << applicant.lastName << " " << applicant.initials << endl;
        }
    }

    file.close();
}

void printApplicants(const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file" << endl;
        return;
    }

    Applicant applicant;
    cout << left << setw(15) << "Last Name"
         << setw(15) << "Initials"
         << setw(10) << "Gender"
         << setw(15) << "School Number"
         << setw(10) << "Medal"
         << setw(10) << "Score"
         << setw(10) << "Pass" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;

    while (file.read(reinterpret_cast<char*>(&applicant), sizeof(Applicant))) {
        cout << left << setw(15) << applicant.lastName
             << setw(15) << applicant.initials
             << setw(10) << applicant.gender
             << setw(15) << applicant.schoolNumber
             << setw(10) << (applicant.medal ? "Yes" : "No")
             << setw(10) << applicant.score
             << setw(10) << (applicant.pass ? "Yes" : "No") << endl;
    }

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        cerr << "Usage: " << argv[0] << " filename [score]" << endl;
        return 1;
    }

    const char* filename = argv[1];

    if (argc == 2) {
        printApplicants(filename);
    } else if (argc == 3) {
        int score = atoi(argv[2]);
        if (score < 0 || score > 100) {
            cerr << "Score must be between 0 and 100" << endl;
            return 1;
        }
        printMedalistBelowScore(filename, score);
    }

    return 0;
}