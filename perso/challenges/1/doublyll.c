// WRITTEN BY CHATGPT
// FOLLOWING PROMPT:
// in C a small programm where i define a doubly linked list of heap-allocated strings.   functions to insert, find, and delete items from it.   a simple main where it tests these functions and write to standard output



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Node structure
typedef struct Node {
    char *data;
    struct Node *prev;
    struct Node *next;
} Node;

// Define the Doubly Linked List structure
typedef struct DoublyLinkedList {
    Node *head;
    Node *tail;
} DoublyLinkedList;

// Function to create a new empty Doubly Linked List
DoublyLinkedList* createList() {
    DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

// Function to create a new Node with given data
Node* createNode(const char *data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = strdup(data);  // Allocate and copy string
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a Node at the end of the list
void insert(DoublyLinkedList *list, const char *data) {
    Node* newNode = createNode(data);
    if (list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
}

// Function to find a Node by its data
Node* find(DoublyLinkedList *list, const char *data) {
    Node* current = list->head;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to delete a Node from the list
void deleteNode(DoublyLinkedList *list, const char *data) {
    Node* nodeToDelete = find(list, data);
    if (nodeToDelete == NULL) return;

    if (nodeToDelete->prev != NULL) {
        nodeToDelete->prev->next = nodeToDelete->next;
    } else {
        list->head = nodeToDelete->next;
    }

    if (nodeToDelete->next != NULL) {
        nodeToDelete->next->prev = nodeToDelete->prev;
    } else {
        list->tail = nodeToDelete->prev;
    }

    free(nodeToDelete->data);
    free(nodeToDelete);
}

// Function to free the entire list
void freeList(DoublyLinkedList *list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(list);
}

int main() {
    // Create a new Doubly Linked List
    DoublyLinkedList *list = createList();

    // Insert items into the list
    insert(list, "First");
    insert(list, "Second");
    insert(list, "Third");

    // Find and display a node
    Node* node = find(list, "Second");
    if (node != NULL) {
        printf("Found: %s\n", node->data);
    } else {
        printf("Not Found: Second\n");
    }

    // Delete a node
    deleteNode(list, "Second");
    printf("DELETED SECOND NODE\n");

    // Try to find the deleted node
    node = find(list, "Second");
    if (node != NULL) {
        printf("Found: %s\n", node->data);
    } else {
        printf("Not Found: Second\n");
    }

    // Display remaining items
    printf("Remaining items:\n");
    Node* current = list->head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }

    // Free the list
    freeList(list);

    return 0;
}
