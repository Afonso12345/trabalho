#include "Novo.h"

void CriarJob(jobs **ref, int a)
{

    jobs *new= malloc(sizeof(jobs));
    jobs *last = *ref;
    new->job = a;
    new->iniop = NULL;
    new->prox = NULL;

    if(*ref == NULL)
    {
        *ref = new;
        
        return;
    } 
    while(last->prox != NULL)
    {
        last = last->prox;
    }
    last->prox = new;
    return;
    

}
void PrintaOperacoes(jobs **ref)
{
    jobs *nova1 = *ref;
    opera *nova = nova1->iniop;

    while(nova1 != NULL)
    {
        nova = nova1->iniop;
        printf("Numero do job %d\n", nova1->job);
        printf("Operações existentes:\n");
        while(nova != NULL)
        {
            printf("%d\n",nova->num_opera);

            nova = nova->prox;
        }

        nova1 = nova1->prox;
    }
    

}
void eliminarJob(jobs **ref, int a)
{
    jobs *lista = *ref, *ant;
    opera *nova, *eli;
    while(lista != NULL && lista->job == a)
    {
        *ref = lista->prox;
        nova = lista->iniop;
        while(nova != NULL)
        {
            eli = nova->prox;
            free(nova);
            nova = eli;
        }
        free(lista);
        lista = *ref;
    }

}
void PrintaJobs(jobs *ref)
{
    while(ref != NULL)
    {
        printf("Numero: %d\n", ref->job);
        ref = ref->prox;
    }
}
void CriarOperacoes(jobs **ref,int a, int b)
{
    opera *new = malloc(sizeof(opera));
    jobs *ola = *ref;
    struct Ope **c;

    while(ola != NULL)
    {
        if(b == ola->job)
        {
            c = &(ola->iniop);
        }

        ola = ola->prox;
    }

    new->job1 = b;
    new->num_opera = a;
    new->ini_maq = NULL;
    new->prox = NULL;

    opera *last = *c;

    if(*c == NULL)
    {
        *c = new;
        return;
    }


    while(last->prox != NULL)
    {
        last = last->prox;
    }
    last->prox = new;
    return;

    





}
void CriarMaquinas(jobs **ref, int a, int b)
{
    maqs *new = malloc(sizeof(maqs));
    jobs *ola = *ref;






}
void menu(jobs **head)
{
    int opcao, a, job, mach;


    do
    {
        int operacao=0;
        int maquinas = 0;
        printf("\nMenu:\n");
        printf("1-Inserir job.\n");
        printf("2-Remover job.\n");
        printf("3-Inserir operacao.\n");
        printf("4-Remover operacao.\n");
        printf("5-Alterar operacao.\n");
        printf("6-Mostrar a lista de operacoes.\n");
        printf("7-Sair.\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                printf("Numero do job: ");
                scanf("%d", &a);
                CriarJob(head,a);
                break;
            case 2:
                printf("Numero do job a eliminar: ");
                scanf("%d", &a);
                eliminarJob(head, a);
                break;
            case 3:
                printf("Numero do job: ");
                scanf("%d", &job);
                printf("Numero de operacao a criar: ");
                scanf("%d", &mach);

                CriarOperacoes(head,mach,job);
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                PrintaOperacoes(head);
                break;
            case 7:
                PrintaJobs(*head);
                break;
                
        }




    }while(opcao != 8);
}
