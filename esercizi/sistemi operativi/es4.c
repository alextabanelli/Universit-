#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* insert_head(Node* head, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = head;  // collega il vecchio head
    return new_node;        // restituisce il nuovo head
}

void print_list(Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    while (head != NULL) {
        printf("%d -> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}

void free_list(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* head = NULL;

    head = insert_head(head, 10);
    head = insert_head(head, 20);
    head = insert_head(head, 30);

    print_list(head);
    free_list(head);
    printf("List memory freed\n");
    printf("End of program\n");

    return 0;
}