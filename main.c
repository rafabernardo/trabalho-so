#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "./process_list.c"


ProcessList *processes;
int memoria_fisica_maxsize;
int pagina_maxsize;
int * memoria_fisica;

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
    int process_id;
    int process_size;

    while (process_size != 0 && process_size > memoria_fisica_maxsize)
    {
        printf("\nDIGITE O TAMANHO DO PROCESSO\n");
        scanf("%i", &process_size);
        if (process_size > memoria_fisica_maxsize)
        {
            printf("\nTAMANHO É MAIOR QUE A MEMORIA, DIGITE UM TAMANHO MENOR");
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

    int page [process_size/pagina_maxsize]; 
    for (size_t i = 0; i < process_size/pagina_maxsize; i++)
    {
        page[i] = getRandomValues();
    }

    process *process = createProcess(process_id, process_size, page, 1);
    addProcess(process, processes);

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

void setTamanhoMemoriaFisica()
{
    int size = -1;
    while (size <= 0)
    {
        printf("\nDigite o tamanho da memoria fisica\n");
        scanf("%d", &size);
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
}

void setTamanhoPagina()
{
    int size = -1;
    if (memoria_fisica_maxsize > 0)
    {
        while (size <= 0)
        {
            printf("\nDigite o tamanho da pagina\n");
            scanf("%d", &size);
            if (size < memoria_fisica_maxsize)
            {
                if (size % 2 != 0)
                {
                    printf("\nO tamanho precisa ser multiplo de dois");
                    setTamanhoMemoriaFisica();
                }
                else
                {
                    pagina_maxsize = size;
                }
            }
            else
            {
                printf("\nO tamanho da pagina não pode ser maior que a memoria fisica");
                setTamanhoPagina();
            }
        }
    }
    else
    {
        printf("\nÉ preciso definir o tamanho da memoria fisica \n");
        setTamanhoMemoriaFisica();
    }
}

int main(void)
{
    processes = makeProcesslist();

    memoria_fisica_maxsize = -1;
    pagina_maxsize = -1;
    int opcao;
    time_t t;

    while (opcao != 0)
    {
        printf("\nESCOLHA UMA DAS SEGUINTES OPÇÕES\n");
        printf("\n1 - PARA VISUZALIZAR A MEMÓRIA\n");
        printf("\n2 - PARA CRIAR UM NOVO PROCESSO\n");
        printf("\n3 - PARA VISUALIZAR A TABELA DE PÁGINAS\n");
        printf("\n4 - Definir tamanho da memoria fisica\n");
        printf("\n5 - Definir tamanho da página\n");
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
            setTamanhoMemoriaFisica();
            memoria_fisica[memoria_fisica_maxsize];
            break;
        case 5:
            setTamanhoPagina();
            break;
        case 0:
            printf("\nENCERRANDO...\n");
            break;

        default:
            printf("\nOPÇÃO INVÁLIDA\n\n");
        }
    }

    int x[3] = {2,4,5};
    process * p = createProcess(123, 10, x, 4);
    addProcess(p, processes);
    displayProcess(processes);
}
