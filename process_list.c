#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "./process.c"

typedef struct node
{
    process *p;
    struct node *next;

} Node;

typedef struct list
{
    Node *head;
} ProcessList;

Node *createnode(process * key)
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

ProcessList *makeProcesslist()
{
    ProcessList *list = malloc(sizeof(ProcessList));
    if (!list)
    {
        return NULL;
    }
    list->head = NULL;
    return list;
}

void displayProcess(ProcessList *list)
{
    Node *current = list->head;
    if (list->head == NULL)
        return;

    for (; current != NULL; current = current->next)
    {
        for (size_t i = 0; i <= (sizeof(current->p->pagina)/sizeof(int)); i++)
        {
            printf("%d\n", (current->p)->pagina[i]);
        }        
    }
}

void addProcess(process * key, ProcessList *list)
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

process *popProcess(ProcessList *list)
{
    process *retval;
    Node *next_node = NULL;

    if (list->head == NULL)
    {
        return NULL;
    }

    next_node = list->head->next;
    retval = list->head->p;
    free(list->head);
    list->head = next_node;

    return retval;
}