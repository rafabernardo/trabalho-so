#include <stdio.h>
#include <string.h>

typedef struct nodetabela
{
    int p;
    int q;
    struct nodetabela *next;

} NodeTabela;

typedef struct listtabela
{
    NodeTabela *head;
    int size;
} ListTabela;

NodeTabela *createnodetabela(int p, int q, NodeTabela *prev)
{
    NodeTabela *newNode = malloc(sizeof(NodeTabela));

    if (!newNode)
    {
        return NULL;
    }

    newNode->p = p;
    newNode->q = q;
    newNode->next = NULL;
    return newNode;
}

ListTabela *makeListTabela()
{
    ListTabela *list = malloc(sizeof(ListTabela));
    if (!list)
    {
        return NULL;
    }
    list->head = NULL;
    return list;
}

void displayTabela(ListTabela *list)
{
    NodeTabela *current = list->head;
    if (list->head == NULL)
        return;
    printf("Pagina - Quadro\n");
    for (; current != NULL; current = current->next)
    {

        printf("%d - %d\n", current->p, current->q);
    }
}

int addTabela(int p, int q, ListTabela *list)
{
    NodeTabela *current = NULL;
    if (list->head == NULL)
    {
        list->head = createnodetabela(p, q, NULL);
        list->size++;
    }
    else
    {
        current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = createnodetabela(p, q, current);
        list->size++;
    }
    list->size;
}

int popTabela(ListTabela *list)
{
    int retval;
    NodeTabela *next_node = NULL;

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