#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "./process_list.c"
#include "./list.c"
#include "./tabela.c"

int memoria_fisica_maxsize = -1;
int pagina_maxsize = -1;
int process_maxsize = -1;
int quadro_size = -1;
int *memoria_fisica = NULL;
ListTabela *tabela;
List *lista_memoria_vazia;
ProcessList *processes;

int getRandomValues()
{
    int random;
    random = (rand() % 150 + 1);
    return random;
}

void criarProcesso()
{
    if (process_maxsize > 0)
    {
        if (lista_memoria_vazia->size > 0)
        {
            int process_id = -1;
            int process_size = -1;

            while (process_id < 0)
            {
                printf("DIGITE O ID DO PROCESSO\n");
                scanf("%i", &process_id);
                break;
            }

            while (process_size < 0)
            {
                printf("\nDIGITE O TAMANHO DO PROCESSO\n");
                scanf("%i", &process_size);
                if (process_size > process_maxsize)
                {
                    printf("\nTAMANHO É MAIOR QUE O TAMANHO MAXIMO DO PROCESSO, DIGITE UM TAMANHO MENOR\n");
                    scanf("%i", &process_size);
                }
            }

            int s = process_size / pagina_maxsize;
            int page[s];
            for (size_t i = 0; i < s; i++)
            {
                page[i] = getRandomValues();
            }

            int index_tabela;
            for (int i = 0; i < s; i++)
            {
                if (i == 0)
                {
                    int posicao = getRandom(lista_memoria_vazia);
                    index_tabela = addTabela(i, posicao, tabela);
                    memoria_fisica[posicao] = i;
                }
                else
                {
                    int posicao = getRandom(lista_memoria_vazia);
                    addTabela(i, posicao, tabela);
                    memoria_fisica[posicao] = i;
                }
            }

            process *process = createProcess(process_id, process_size, page, index_tabela);
            addProcess(process, processes);

            displayProcess(processes);
        }else{
            printf("Memoria cheia\n");
        }
    }
    else
    {
        printf("Defina um tamanho maximo do processo");
    }
}

void visualizarTabelaPagina()
{
    printf("TABELA DE PAGINA\n");
    displayTabela(tabela);
}

void visualizarMemoriaFisica()
{
    printf("MEMORIA FISICA\n");
    printf("Tamanho total: %d\n", memoria_fisica_maxsize);
    int tamanho = (lista_memoria_vazia->size * 100) / memoria_fisica_maxsize;
    printf("Tamanho livre: %d%%\n", tamanho);

    for (int i = 0; i < memoria_fisica_maxsize; i++)
    {
        printf("%i - %d\n", i, memoria_fisica[i]);
    }
}

void setTamanhoMemoriaFisica()
{
    int size = -1;
    while (size <= 0)
    {
        printf("\nDigite o tamanho da memoria fisica\n");
        scanf("%d", &size);
        if (size > pagina_maxsize)
        {
            if (size % 2 != 0)
            {
                printf("\nO tamanho precisa ser multiplo de dois");
                setTamanhoMemoriaFisica();
            }
            else
            {
                memoria_fisica_maxsize = size;
            }
        }
        else
        {
            printf("\nTamanho da memoria precisa ser maior que o da pagina");
            setTamanhoMemoriaFisica();
        }
    }
}

void setTamanhoPagina()
{
    int size = -1;
    while (size <= 0)
    {
        printf("\nDigite o tamanho da pagina\n");
        scanf("%d", &size);
        if (size % 2 != 0)
        {
            printf("\nO tamanho precisa ser multiplo de dois");
            setTamanhoPagina();
        }
        else
        {
            pagina_maxsize = size;
            processes->page_size = size;
        }
    }
}

void setTamanhoMaxProcesso()
{
    int size = -1;
    while (size <= 0)
    {
        printf("\nDigite o tamanho maximo do processo\n");
        scanf("%d", &size);
        if (size % 2 != 0)
        {
            printf("\nO tamanho precisa ser multiplo de dois");
            setTamanhoMaxProcesso();
        }
        else
        {
            process_maxsize = size;
        }
    }
}

void createListasMemoriaFisica()
{
    memoria_fisica = malloc(sizeof(int) * memoria_fisica_maxsize);
    for (int i = 0; i < memoria_fisica_maxsize; i++)
    {
        memoria_fisica[i] = 0;
        add(i, lista_memoria_vazia);
    }
}

int main(void)
{
    processes = makeProcesslist();
    tabela = makeListTabela();
    lista_memoria_vazia = makeList();

    int opcao;
    time_t t;
    srand(t);

    while (opcao != 0)
    {
        printf("\nESCOLHA UMA DAS SEGUINTES OPÇÕES\n");
        printf("\n1 - PARA VISUZALIZAR A MEMÓRIA\n");
        printf("\n2 - PARA CRIAR UM NOVO PROCESSO\n");
        printf("\n3 - PARA VISUALIZAR A TABELA DE PÁGINAS\n");
        printf("\n4 - Definir tamanho da memoria fisica\n");
        printf("\n5 - Definir tamanho da página\n");
        printf("\n6 - Definir tamanho maximo de processo\n");
        printf("\n0 - PARA ENCERRAR\n\n");

        scanf("%i", &opcao);

        switch (opcao)
        {
        case 1:
            if (memoria_fisica_maxsize <= 0 || pagina_maxsize <= 0)
            {
                printf("\nConfigure o tamanho da memoria fisica e da pagina");
            }
            else
            {
                visualizarMemoriaFisica();
            }
            break;

        case 2:
            if (memoria_fisica_maxsize <= 0 && pagina_maxsize <= 0)
            {
                printf("\nConfigure o tamanho da memoria fisica e da pagina");
            }
            else
            {
                criarProcesso();
            }
            break;

        case 3:
            if (memoria_fisica_maxsize <= 0 && pagina_maxsize <= 0)
            {
                printf("\nConfigure o tamanho da memoria fisica e da pagina");
            }
            else
            {
                visualizarTabelaPagina();
            }
            break;
        case 4:
            if (pagina_maxsize <= 0)
            {
                printf("\nDefina o tamanho da pagina\n");
            }
            else
            {
                setTamanhoMemoriaFisica();
                printf("%d maxMemoria\n", memoria_fisica_maxsize);
                printf("%d maxPagina\n", pagina_maxsize);
                if (memoria_fisica == NULL)
                {
                    createListasMemoriaFisica();
                }
            }
            break;
        case 5:
            setTamanhoPagina();
            break;
        case 6:
            if (memoria_fisica_maxsize <= 0)
            {
                printf("\nDefina o tamanho da memoria fisica\n");
            }
            else
            {
                setTamanhoMaxProcesso();
            }
            break;
        case 0:
            printf("\nENCERRANDO...\n");
            break;

        default:
            printf("\nOPÇÃO INVÁLIDA\n\n");
        }
    }

    /*  add(1, fisica_tabela);
    add(7, fisica_tabela);
    add(3, fisica_tabela);
    add(8, fisica_tabela);
    Node *teste = getRandom(fisica_tabela);
    printf("%d numero", teste->p);
    printf("------------------------");
    display(fisica_tabela); */
}
