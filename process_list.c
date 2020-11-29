#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "./process.c"

typedef struct nodep
{
    process *p;
    struct nodep *next;

} NodeP;

typedef struct processList
{
    NodeP *head;
    int page_size;

} ProcessList;

NodeP *createnodeprocess(process *key)
{
    NodeP *newNode = malloc(sizeof(NodeP));

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
    NodeP *current = list->head;
    if (list->head == NULL)
        return;
    printf("Identificador  - Tamanho\n");

    for (; current != NULL; current = current->next)
    {
        printf("%d               - %d\n", current->p->id, current->p->tamanho);
        printf("Paginas %d\n", current->p->tamanho);
        for (size_t i = 0; i < (current->p->tamanho/list->page_size); i++)
        {
            printf("%d\n", current->p->pagina[i]);
        }
        
    }
}

void addProcess(process *key, ProcessList *list)
{
    NodeP *current = NULL;
    if (list->head == NULL)
    {
        list->head = createnodeprocess(key);
    }
    else
    {
        current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = createnodeprocess(key);
    }
}

process *popProcess(ProcessList *list)
{
    process *retval;
    NodeP *next_node = NULL;

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