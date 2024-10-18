#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int value;
    struct node* next;
    struct node* prev;
} Node;


typedef struct list {
    Node* head;
    Node* tail;
    size_t size;
} List;


void init_list(List* plist) {
    plist->head = NULL;
    plist->tail = NULL;
    plist->size = 0;
}


Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void push_back(List* pl, int value);

List init(size_t n) {
    List newList;
    newList.head = NULL;
    newList.tail = NULL;
    newList.size = 0;
    for (size_t i = 0; i < n; i++) {
        push_back(&newList, 0);
    }
    return newList;
}

void print(const List* pl) {
    Node* current = pl->head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void push_back(List* pl, int value) {
    Node* new_node = create_node(value);
    if (pl->tail == NULL) {
        pl->head = pl->tail = new_node;
    }
    else {
        pl->tail->next = new_node;
        new_node->prev = pl->tail;
        pl->tail = new_node;
    }
    pl->size+=1;
}


int pop_back(List* pl) {
    Node* to_remove = pl->tail;
    int value = to_remove->value;
    if (pl->tail == pl->head) {
        pl->tail = pl->head = NULL;
    }
    else {
        pl->tail = pl->tail->prev;
        pl->tail->next = NULL;
    }
    // free(to_remove);
    pl->size--;
    return value;
}


void push_front(List* pl, int value) {
    Node* new_node = create_node(value);
    if (pl->head == NULL) {
        pl->head = pl->tail = new_node;
    }
    else {
        new_node->next = pl->head;
        pl->head->prev = new_node;
        pl->head = new_node;
    }
    pl->size+=1;
}

int pop_front(List* pl) {
    Node* to_remove_show = pl->head;
    int value = to_remove_show->value;
    if (pl->tail==pl->head) {
        pl->tail=pl->head = NULL;
    }
    else {
        pl->head = pl->head->next;
        pl->head->prev = pl->head;
    }
    pl->size-=1;
    return value;

}


Node* erase(List* pl, Node* p) {
    Node* next_node = p->next;
    if (p->next == NULL) {
        return NULL;
    }
    if (p->prev != NULL) {
        p->prev->next = p->next;
    }
    else {
        pl->head = p->next;
    }

    if (p->next != NULL) {
        p->next->prev = p->prev;
    }
    else {
        pl->tail = p->prev;
    }

    pl->size-=1;
    return next_node;
}

void splice(List* plist, Node* p, List* pother) {
    if (pother->size == 0) {
        return; // Список pother пуст, нечего перемещать
    }
    if (p->prev != NULL) {
        p->prev->next = pother->head;
        pother->head->prev = p->prev;
        pother->tail->next = p;
        p->prev = pother->tail;
    }
    plist->size +=(pother->size);
    pother->head = pother->tail = NULL;
    pother->size = 0;
}

void destroy(List* pl) {
    Node* current = pl->head;
    while (current != NULL) {
        Node* next_node = current->next;
        free(current);
        current = next_node;
    }
    pl->head = NULL;
    pl->tail = NULL;
    pl->size = 0;
}


void advance(Node** pp, size_t n) {
    if (*pp == NULL) {
        return;
    }
    for (size_t i = 0; i < n && *pp != NULL; i++) {
        *pp = (*pp)->next;
    }

    if (*pp == NULL) {
        return;
    }
}
