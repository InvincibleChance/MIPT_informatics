#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node* ptr;
};

typedef struct node Node;

int main() {
    Node* node1 = (Node*)malloc(sizeof(Node));
    Node* node2 = (Node*)malloc(sizeof(Node));

    node1->value = 10;
    node1->ptr = node2;

    node2->value = 20;
    node2->ptr = node1;

    printf("Node 1: value = %d, ptr -> value = %d\n", node1->value, node1->ptr->value);
    printf("Node 2: value = %d, ptr -> value = %d\n", node2->value, node2->ptr->value);

    free(node1);
    free(node2);
}
