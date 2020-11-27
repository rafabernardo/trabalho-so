#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int memoria_fisica_maxsize = 20;
int memoria_logica_maxsize = 10;
int pagina_maxsize = 2;
int memoria_fisica[20][2];

typedef struct node
{
    int key;
    int page;
    struct node *next;

} Node;

typedef struct list
{
    Node *head;
    int size;
    int max_size;
    int id;
} List;

Node *createnode(int key)
{
    Node *newNode = malloc(sizeof(Node));

    if (!newNode)
    {
        return NULL;
    }

    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

List *makelist()
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
        printf("%d\n", current->key);
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
    list->size++;
}

int pop(List *list)
{
    int retval = -1;
    Node *next_node = NULL;

    if (list->head == NULL)
    {
        return -1;
    }

    next_node = (list->head)->next;
    retval = (list->head)->key;
    free(list->head);
    list->head = next_node;

    return retval;
}

void visualizarMemoriaFisica();
void criarProcesso();
void visualizarTabelaPagina();

int getRandomValues()
{
    int random;
    random = (rand() % 150 + 1);
    return random;
}

void alocarProcessoNaMemoriaFisica(List *process)
{
    //to do alocar na memora fisica
}

void criarProcesso()
{
    int process_id;
    int process_size;

    while (process_size != 0 && process_size > memoria_fisica_maxsize)
    {
        printf("DIGITE O TAMANHO DO PROCESSO\n");
        scanf("%i", &process_size);
        if (process_size > memoria_fisica_maxsize)
        {
            printf("TAMANHO É MAIOR QUE A MEMORIA, DIGITE UM TAMANHO MENOR");
            scanf("%i", &process_size);
        }
        break;
    }

    while (process_id != 0)
    {
        printf("DIGITE O ID DO PROCESSO\n");
        scanf("%i", &process_id);
        break;
    }

    //int process[process_size][pagina_maxsize];
    List *process = makelist();
    process->id = process_id;
    process->max_size = process_size;
    for (size_t i = 0; i < process_size; i++)
    {
        int page[pagina_maxsize];
        for (size_t t = 0; t < pagina_maxsize; t++)
        {
            page[t] = getRandomValues();
        }
        add(*page, process);
    }

    alocarProcessoNaMemoriaFisica(process);
}

void visualizarTabelaPagina()
{
    printf("executar função visualizar tabeça de paginas\n\n");
}

void visualizarMemoriaFisica()
{
    printf("processo -- quadro \n");
    for (int i = 0; i < memoria_fisica_maxsize; i++)
    {

        printf("%d -- %d \n", i, memoria_fisica[i]);
    }
}

int main(void)
{

    int opcao;
    time_t t;

    while (opcao != 0)
    {
        printf("ESCOLHA UMA DAS SEGUINTES OPÇÕES\n");
        printf("1 - PARA VISUZALIZAR A MEMÓRIA\n");
        printf("2 - PARA CRIAR UM NOVO PROCESSO\n");
        printf("3 - PARA VISUALIZAR A TABELA DE PÁGINAS\n");
        printf("0 - PARA ENCERRAR\n\n");

        scanf("%i", &opcao);

        switch (opcao)
        {
        case 1:
            visualizarMemoriaFisica();
            break;

        case 2:
            criarProcesso();
            break;

        case 3:
            visualizarTabelaPagina();
            break;

        case 0:
            printf("ENCERRANDO...\n");
            break;

        default:
            printf("OPÇÃO INVÁLIDA\n\n");
        }
    }
}
