#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "./process_list.c"
#include "./list.c"

int memoria_fisica_maxsize;
int pagina_maxsize;
int process_maxsize;
int quadro_size;
int *memoria_fisica;
List *fisica_tabela;
List *lista_memoria_vazia;
ProcessList *processes;

int getRandomValues()
{
    int random;
    random = (rand() % 150 + 1);
    return random;
}

void alocarProcessoNaMemoriaFisica()
{
    //to do alocar na memora fisica
}

void criarProcesso()
{
    if(process_maxsize > 0 ){
        int process_id;
        int process_size;

        while (process_size != 0)
        {
            printf("\nDIGITE O TAMANHO DO PROCESSO\n");
            scanf("%i", &process_size);
            if (process_size > process_maxsize)
            {
                printf("\nTAMANHO É MAIOR QUE O TAMANHO MAXIMO DO PROCESSO, DIGITE UM TAMANHO MENOR\n");
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

        int s = process_size * pagina_maxsize;
        int page[s];
        printf("%d page tamanho \n", s);
        for (size_t i = 0; i < s; i++)
        {
            page[i] = getRandomValues();
            printf("%d\n", page[i]);
        }

        int posicao = pop(fisica_tabela);
        process *process = createProcess(process_id, process_size, page, posicao);
        addProcess(process, processes);

        displayProcess(processes);

        alocarProcessoNaMemoriaFisica(process);
    } else{
        printf("Defina um tamanho maximo do processo");
    }
}

void visualizarTabelaPagina()
{
    printf("executar função visualizar tabeça de paginas\n\n");
}

void visualizarMemoriaFisica()
{
    printf("Exibir memória física\n");
    printf("Lista mem tabela: \n");
    display(fisica_tabela);
    printf("Lista mem tabela: \n");
    display(lista_memoria_vazia);
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
    int tam_lista_tabela;
    int tam_lista_vazia;
    if ((quadro_size % 2) != 0)
    {
        tam_lista_vazia = quadro_size / 2;
        tam_lista_tabela = (quadro_size / 2) + 1;
    }
    else
    {
        tam_lista_vazia = quadro_size / 2;
        tam_lista_tabela = quadro_size / 2;
    }

    for (int i = 0; i < tam_lista_tabela; i++)
    {
        add(i, lista_memoria_vazia);
    }
    for (int j = tam_lista_tabela; j < (tam_lista_tabela + tam_lista_vazia); j++)
    {
        add(j, fisica_tabela);
    }
}

int main(void)
{
    processes = makeProcesslist();
    fisica_tabela = makeList();
    lista_memoria_vazia = makeList();

    memoria_fisica_maxsize = -1;
    pagina_maxsize = -1;
    process_maxsize = -1;

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
                    quadro_size = memoria_fisica_maxsize / pagina_maxsize;
                    createListasMemoriaFisica(quadro_size);
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
}
