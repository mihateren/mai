#include <iostream>

using namespace std;

typedef int data_type;

typedef int key_type;

struct Node {
    data_type data;
    Node* next;
};

struct List {
    Node* head;
    Node* tail;
    int size;
};

List* list_create() {
    List* list = new List;
    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
    return list;
}

bool list_is_empty(const List* list) {
    return list->size == 0;
}

void list_push_front(List* list, const data_type& value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = list->head;
    list->head = newNode;
    if (list->tail == nullptr) {
        list->tail = newNode;
    }
    list->size++;
}

void list_push_back(List* list, const data_type& value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    if (list->tail != nullptr) {
        list->tail->next = newNode;
    } else {
        list->head = newNode;
    }
    list->tail = newNode;
    list->size++;
}

void list_pop_front(List* list) {
    if (!list_is_empty(list)) {
        Node* temp = list->head;
        list->head = list->head->next;
        delete temp;
        list->size--;
        if (list->head == nullptr) {
            list->tail = nullptr;
        }
    }
}

void list_pop_back(List* list) {
    if (!list_is_empty(list)) {
        if (list->head == list->tail) {
            delete list->head;
            list->head = list->tail = nullptr;
        } else {
            Node* current = list->head;
            while (current->next != list->tail) {
                current = current->next;
            }
            delete list->tail;
            list->tail = current;
            list->tail->next = nullptr;
        }
        list->size--;
    }
}

void list_print(const List* list) {
    Node* current = list->head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

int list_size(const List* list) {
    return list->size;
}

void list_insert(List* list, const data_type& value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    if (list->head == nullptr) {
        list->head = list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->size++;
}

void list_erase(List* list, const key_type& key) {
    if (!list_is_empty(list)) {
        Node* current = list->head;
        Node* prev = nullptr;
        while (current != nullptr) {
            if (current->data == key) {
                if (prev != nullptr) {
                    prev->next = current->next;
                } else {
                    list->head = current->next;
                }
                delete current;
                list->size--;
                return;
            }
            prev = current;
            current = current->next;
        }
    }
}

void task(List* list) {
    if (list->head == nullptr || list->head == list->tail) {
        return;
    }

    Node* prev = list->head;
    Node* current = list->head->next;

    while (current != nullptr) {
        if (current->data < prev->data) {
            prev->next = current->next;
            if (current == list->tail) {
                list->tail = prev;
            }
            current->next = list->head;
            list->head = current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

int main() {
    List* myList = list_create();
    list_insert(myList, 5);
    list_insert(myList, 2);
    list_insert(myList, 7);
    list_insert(myList, 1);
    list_insert(myList, 9);

    cout << "Original list: ";
    list_print(myList);

    task(myList);

    cout << "List after moving smaller element to front: ";
    list_print(myList);

    // Освобождаем память
    while (!list_is_empty(myList)) {
        list_pop_front(myList);
    }
    delete myList;

    return 0;
}