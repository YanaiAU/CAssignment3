#include <stdio.h>
#include <string.h>
#include "StrList.h"  // Include the header file for the StrList library

void printMenu() {
    printf("\nMenu:\n");
    printf("1. Insert strings into the list\n");
    printf("2. Insert a string at a certain index\n");
    printf("3. Print the list\n");
    printf("4. Print the length of the list\n");
    printf("5. Print a string at a certain index\n");
    printf("6. Print the total number of characters in the list\n");
    printf("7. Print how many times a string appears in the list\n");
    printf("8. Delete all occurrences of a string from the list\n");
    printf("9. Delete a string at a certain index\n");
    printf("10. Reverse the list\n");
    printf("11. Delete the entire list\n");
    printf("12. Sort the list in lexicographical order\n");
    printf("13. Check if the list is arranged in lexicographical order\n");
    printf("0. Exit the program\n");
}

int main() {
    StrList* list = StrList_alloc(); // Initialize an empty list
    int choice;

    do {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear the newline character from the input buffer

        switch (choice) {
            case 1:
                // Insert strings into the list
                printf("Enter the number of words: ");
                int numWords;
                scanf("%d", &numWords);
                getchar(); // Clear the newline character from the input buffer
                printf("Enter %d words separated by space:\n", numWords);
                char input[100];
                fgets(input, sizeof(input), stdin);
                char* token = strtok(input, " ");
                while (token != NULL) {
                    StrList_insertLast(list, token);
                    token = strtok(NULL, " ");
                }
                break;
            case 2:
                // Insert a string at a certain index
                printf("Enter the index: ");
                int index;
                scanf("%d", &index);
                getchar(); // Clear the newline character from the input buffer
                printf("Enter the string to insert: ");
                fgets(input, sizeof(input), stdin);
                StrList_insertAt(list, input, index);
                break;
            case 3:
                // Print the list
                printf("List:\n");
                StrList_print(list);
                break;
            case 4:
                // Print the length of the list
                printf("Length of the list: %zu\n", StrList_size(list));
                break;
            case 5:
                // Print a string at a certain index
                printf("Enter the index: ");
                scanf("%d", &index);
                getchar(); // Clear the newline character from the input buffer
                printf("String at index %d: ", index);
                StrList_printAt(list, index);
                break;
            case 6:
                // Print the total number of characters in the list
                printf("Total number of characters in the list: %d\n", StrList_printLen(list));
                break;
            case 7:
                // Print how many times a string appears in the list
                printf("Enter the string to search for: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';  // Remove the newline character
                printf("Number of times '%s' appears in the list: %d\n", input, StrList_count(list, input));
                break;
            case 8:
                // Delete all occurrences of a string from the list
                printf("Enter the string to delete: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';  // Remove the newline character
                StrList_remove(list, input);
                break;
            case 9:
                // Delete a string at a certain index
                printf("Enter the index of the string to delete: ");
                scanf("%d", &index);
                getchar(); // Clear the newline character from the input buffer
                StrList_removeAt(list, index);
                break;
            case 10:
                // Reverse the list
                StrList_reverse(list);
                printf("List reversed.\n");
                break;
            case 11:
                // Delete the entire list
                StrList_free(list);
                list = StrList_alloc();
                printf("List deleted.\n");
                break;
            case 12:
                // Sort the list in lexicographical order
                StrList_sort(list);
                printf("List sorted in lexicographical order.\n");
                break;
            case 13:
                // Check if the list is arranged in lexicographical order
                if (StrList_isSorted(list)) {
                    printf("The list is arranged in lexicographical order.\n");
                } else {
                    printf("The list is not arranged in lexicographical order.\n");
                }
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);

    // Free memory allocated for the list
    StrList_free(list);

    return 0;
}