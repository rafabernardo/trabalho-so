typedef struct Process
{
    int id;
    int tamanho;
    int *pagina;
    int pos_tabela;
} process;

process *createProcess(int id, int tamanho, int *pagina, int pos_tabela){
    process *newProcess = malloc(sizeof(process));
    newProcess->id = id;
    newProcess->pagina = malloc(sizeof(pagina));
    newProcess->pagina = pagina;
    newProcess->pos_tabela = pos_tabela;
    newProcess->tamanho = tamanho;
    return newProcess;    
}