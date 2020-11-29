#include <stdio.h>
#include <string.h>

typedef struct node
{
    int p;
    struct node *next;

}Node;

typedef struct list
{
    Node *head;
}List;

Node *createnode(int key)
{
    Node *newNode = malloc(sizeof(Node));

    if (!newNode)
    {
        return NULL;
    }

    newNode->p = key;
    newNode->next = NULL;
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
        list->head = createnode(key);
    }
    else
    {
        current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = createnode(key);
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

    return retval;
}