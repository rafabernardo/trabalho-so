#include <stdio.h>
#include <string.h>

typedef struct node
{
    int p;
    struct node *next;
    struct node *prev;

} Node;

typedef struct list
{
    Node *head;
    int size;
} List;

Node *createnode(int key, Node *prev)
{
    Node *newNode = malloc(sizeof(Node));

    if (!newNode)
    {
        return NULL;
    }

    newNode->p = key;
    newNode->next = NULL;
    newNode->prev = prev;
    return newNode;
}

List *makeList()
{
    List *list = malloc(sizeof(List));
    if (!list)
    {
        return NULL;
    }
    list->head = NULL;
    return list;
}

void display(List *list)
{
    Node *current = list->head;
    if (list->head == NULL)
        return;

    for (; current != NULL; current = current->next)
    {

        printf("%d\n", current->p);
    }
}

void add(int key, List *list)
{
    Node *current = NULL;
    if (list->head == NULL)
    {
        list->head = createnode(key, NULL);
        list->size++;
    }
    else
    {
        current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = createnode(key, current);
        list->size++;
    }
}

int pop(List *list)
{
    int retval;
    Node *next_node = NULL;

    if (list->head == NULL)
    {
        return -1;
    }

    next_node = list->head->next;
    retval = list->head->p;
    free(list->head);
    list->head = next_node;
    list->size--;

    return retval;
}

Node *getAt(int key, List *list)
{
    Node *current = list->head;
    int count = 1;
    while (current != NULL)
    {
        if (count == key)
        {
            return current;
        }
        count++;
        current = current->next;
    }
    return NULL;
}

int getRandom(List *list)
{
    int key = (rand() % list->size);
    int count = 0;
    Node *current = list->head;
    Node *previous = current;
    while (current != NULL)
    {
        if (count == key)
        {
            previous->next = current->next;
            if (current == list->head)
                list->head = current->next;
            list->size--;
            return current->p;
        }
        previous = current;
        current = current->next;
        count++;
    }
    return -1;
}