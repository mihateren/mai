#include <iostream>

using namespace std;

struct Record {
    int key;
    const char* text;
};

int compareStrings(const char* a, const char* b) {
    while (*a && (*a == *b)) {
        ++a;
        ++b;
    }
    return *(const unsigned char*)a - *(const unsigned char*)b;
}

void shellSort(Record table[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Record temp = table[i];
            int j;
            for (j = i; j >= gap && compareStrings(table[j - gap].text, temp.text) > 0; j -= gap) {
                table[j] = table[j - gap];
            }
            table[j] = temp;
        }
    }
}

int binarySearch(Record table[], char key, int n) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (table[mid].text[0] == key) {
            return mid;
        }
        if (table[mid].text[0] < key) {
            left = mid + 1; 
        } else {
            right = mid - 1; 
        }
    }
    return -1; 
}

void printTable(Record table[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "Key: " << table[i].key << ", Text: " << table[i].text << endl;
    }
}

int main() {
    const char* poem[] = {
        "Two roads diverged in a yellow wood,",
        "And sorry I could not travel both",
        "And be one traveler, long I stood",
        "And looked down one as far as I could",
        "To where it bent in the undergrowth;",
        "Then took the other, as just as fair,",
        "And having perhaps the better claim,",
        "Because it was grassy and wanted wear;",
        "Though as for that the passing there",
        "Had worn them really about the same,",
        "And both that morning equally lay"
    };

    const int n = sizeof(poem) / sizeof(poem[0]);
    Record table[n];

    for (int i = 0; i < n; i++) {
        table[i].key = i;
        table[i].text = poem[i];
    }

    shellSort(table, n);

    cout << "Sorted table by the first letter of each line:" << endl;
    printTable(table, n);

    char keyToFind = 'T'; // Пример ключа для поиска (первая буква первой строки)
    int index = binarySearch(table, keyToFind, n);
    if (index != -1) {
        cout << "Record found: Key: " << keyToFind << ", Text: " << table[index].text << endl;
    } else {
        cout << "Record with key " << keyToFind << " not found." << endl;
    }

    return 0;
}