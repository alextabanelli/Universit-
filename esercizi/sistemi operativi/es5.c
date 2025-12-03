#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* insert_head(int value);{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    head->next = new_node;
    return new_node;
}

void print_list(Node* head);{
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }else printf("%d -> ", head->value);
    print_list(head->next);
}


void free_list(Node* head){
    if (head == NULL) return;
    free_list(head->next);
    free(head);
}


int main () {
    Node* head = NULL;
    head = insert_head(10);
    head = insert_head(20);
    head = insert_head(30);
    print_list(head);
    free_list(head);
    return 0;
}