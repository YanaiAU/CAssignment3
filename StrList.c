#include "StrList.h"
#include <stdio.h>
#include <string.h>

// Node structure
typedef struct Node {
    char* data;
    struct Node* next;
} Node;

// StrList structure
struct _StrList {
    Node* head;
    size_t size;
};

// Function to allocate a new empty StrList
StrList* StrList_alloc() {
    StrList* list = (StrList*)malloc(sizeof(StrList));
    if (list) {
        list->head = NULL;
        list->size = 0;
    }
    return list;
}

// Function to free memory allocated to StrList
void StrList_free(StrList* list) {
    if (!list) return;

    Node* current = list->head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(list);
}

size_t StrList_size(const StrList* list) {
    if (!list) return 0;
    return list->size;
}

// Function to insert an element at the end of the StrList
void StrList_insertLast(StrList* list, const char* data) {
    if (!list) return;

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return;

    newNode->data = strdup(data);
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

// Function to insert an element at a given index
void StrList_insertAt(StrList* list, const char* data, int index) {
    if (!list || index < 0 || index > list->size) return;

    if (index == list->size) {
        StrList_insertLast(list, data);
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return;

    newNode->data = strdup(data);
    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node* current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    list->size++;
}

// Function to get the first data of the StrList
char* StrList_firstData(const StrList* list) {
    if (!list || list->size == 0) return NULL;
    return list->head->data;
}

// Function to print the StrList to standard output
void StrList_print(const StrList* list) {
    if (!list) return;

    Node* current = list->head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

// Function to print the word at a given index to standard output
void StrList_printAt(const StrList* list, int index) {
    if (!list || index < 0 || index >= list->size) return;

    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    printf("%s\n", current->data);
}

// Function to return the amount of characters in the list
int StrList_printLen(const StrList* list) {
    if (!list) return 0;

    int totalLen = 0;
    Node* current = list->head;
    while (current != NULL) {
        totalLen += strlen(current->data);
        current = current->next;
    }
    return totalLen;
}

// Function to count the number of times a string exists in the list
int StrList_count(StrList* list, const char* data) {
    if (!list) return 0;

    int count = 0;
    Node* current = list->head;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            count++;
        }
        current = current->next;
    }
    return count;
}

// Function to remove all occurrences of a string in the list
void StrList_remove(StrList* list, const char* data) {
    if (!list) return;

    Node* current = list->head;
    Node* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            if (prev == NULL) {
                list->head = current->next;
                free(current->data);
                free(current);
                current = list->head;
            } else {
                prev->next = current->next;
                free(current->data);
                free(current);
                current = prev->next;
            }
            list->size--;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

// Function to remove the string at a given index
void StrList_removeAt(StrList* list, int index) {
    if (!list || index < 0 || index >= list->size) return;

    Node* current = list->head;
    Node* prev = NULL;
    for (int i = 0; i < index; i++) {
        prev = current;
        current = current->next;
    }
    if (prev == NULL) {
        list->head = current->next;
    } else {
        prev->next = current->next;
    }
    free(current->data);
    free(current);
    list->size--;
}

// Function to check if two StrLists have the same elements
int StrList_isEqual(const StrList* list1, const StrList* list2) {
    if (!list1 || !list2 || list1->size != list2->size) return 0;

    Node* current1 = list1->head;
    Node* current2 = list2->head;
    while (current1 != NULL) {
        if (strcmp(current1->data, current2->data) != 0) {
            return 0;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    return 1;
}

// Function to clone a StrList
StrList* StrList_clone(const StrList* list) {
    if (!list) return NULL;

    StrList* newList = StrList_alloc();
    Node* current = list->head;
    while (current != NULL) {
        StrList_insertLast(newList, current->data);
        current = current->next;
    }
    return newList;
}

// Function to reverse a StrList
void StrList_reverse(StrList* list) {
    if (!list || list->size <= 1) return;

    Node *prev = NULL, *current = list->head, *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;


        prev = current;
        current = next;
    }
    list->head = prev;
}

// Function to sort a StrList in lexicographical order
void StrList_sort(StrList* list) {
    if (!list || list->size <= 1) return;

    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = list->head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->data, ptr1->next->data) > 0) {
                char* temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Function to check if a StrList is sorted in lexicographical order
int StrList_isSorted(StrList* list) {
    if (!list || list->size <= 1) return 1;

    Node* current = list->head;
    while (current->next != NULL) {
        if (strcmp(current->data, current->next->data) > 0) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}
