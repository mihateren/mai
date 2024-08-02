#include <iostream>
#include <fstream>
#include "person.h"

const char* lastNames[] = {"Petrov", "Ivanov", "Sidorov", "Kotov", "Agapov"};
const char* firstNames[] = {"Ivan", "Petr", "Oleg", "Alex", "Lev"};

void strcpy(char* dest, const char* src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}


int randRange(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void generateApplicants(const char* filename, int count) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    for (int i = 0; i < count; ++i) {
        Applicant applicant;
        int lastNameIndex = randRange(0, 4);
        strcpy(applicant.lastName, lastNames[lastNameIndex]);

        int firstNameIndex = randRange(0, 4);
        strcpy(applicant.initials, firstNames[firstNameIndex]);
        applicant.initials[1] = '.';
        applicant.initials[2] = '\0';

        applicant.gender = randRange(0, 1) == 0 ? 'M' : 'F';
        applicant.schoolNumber = randRange(1, 100);
        applicant.medal = randRange(0, 1) == 0;
        applicant.score = randRange(0, 100);
        applicant.pass = applicant.score >= 50;

        file.write(reinterpret_cast<const char*>(&applicant), sizeof(Applicant));
    }

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " filename count" << std::endl;
        return 1;
    }

    const char* filename = argv[1];
    int count = atoi(argv[2]);
    if (count <= 0) {
        std::cerr << "Count must be a positive integer" << std::endl;
        return 1;
    }

    generateApplicants(filename, count);
    std::cout << "Generated " << count << " applicants to " << filename << std::endl;

    return 0;
}