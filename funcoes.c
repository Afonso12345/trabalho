#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    int opera;
    int mach;
    int vmach;
    struct No* prox;
}lista;

typedef struct Node{
    int operat;
    float media;
    struct Node* proxx;
}media;

void adicionarMedia(media **ref, int a, float b);
void adicionar(lista** ref, int a, int b, int c);
void fileMem(lista **ref);
void ficheirosLista2(lista **ref);
void ficheirosLista(lista **ref);
void printList(lista *node);
void eliminar(lista **eli, int value);
void alterar(lista **eli, int operacao);
void calcMax(lista **ref);
void calcMedia(lista **ref, media **nodes);
void calcMin(lista **ref);
void freeNodes(lista **ref);

void freeNodes(lista **ref)
{
    lista *list = *ref;
    while(list != NULL)
    {
        *ref = list->prox;
        free(list);
        list = *ref;
    }

}
void fileMem(lista **ref)
{
    lista *mem = *ref;
    FILE *open;
    int a,b,c;

    open = fopen("Job.txt", "r");

    while(!feof(open))
    {
        fscanf(open, "%d %d %d\n" ,&a,&b,&c);
        printf("%d %d %d\n", a,b,c);
        adicionar(ref,a,b,c);
    }
    fclose(open);
}
void ficheirosLista2(lista **ref)
{
    lista *nova = *ref;
    FILE *open;

    open = fopen("Job2.txt", "a");
        
        while(nova != NULL)
        {
            fprintf(open, "%d %d %d\n", nova->opera, nova->mach, nova->vmach);

            nova = nova->prox;
        }
    fclose(open);
    remove("Job.txt");
    rename("Job2.txt", "Job.txt");
}
void ficheirosLista(lista **ref)
{
    lista *nova = *ref;
    FILE *open;

    open = fopen("Job.txt", "a");

    
    
        while(nova != NULL)
        {
            fprintf(open, "%d %d %d\n", nova->opera, nova->mach, nova->vmach);

            nova = nova->prox;
            
        }

    fclose(open);
}
void adicionarMedia(media **ref, int a, float b)
{
    media *new= malloc(sizeof(media));
    media *last = *ref;
    new->operat = a;
    new->media = b;
    new->proxx = NULL;

    if(*ref == NULL)
    {
        *ref = new;
        
        return;
    } 
    while(last->proxx != NULL)
    {
        last = last->proxx;
    }
    last->proxx = new;
    return;
}
void calcMedia(lista **ref, media **nodes)
{   
    lista *list = *ref;
    media *node = *nodes;
    int count = 0, soma = 0;
    float avg = 0;

    while(list != NULL)
    {
        if(list->prox != NULL && list->opera == list->prox->opera)
        {
            soma += list->vmach;
            count++;
        }
        if(list->prox == NULL || (list->prox != NULL && list->opera != list->prox->opera))
        {
            count ++;
            soma += list->vmach;
            avg = (float)soma/count;
            adicionarMedia(&node, list->opera, avg);
            avg = 0;
            soma = 0;
            count = 0;
        }

        list = list->prox;
    }
    while(node != NULL)
    {
        printf("Opera:%d  Media:%.2f ", node->operat, node->media);

        node = node->proxx;
    }

}
void calcMin(lista **ref)
{
    int velocidade = 0, soma=0;
    lista *node = *ref;
    lista *nova2 = NULL;
    

    while(node != NULL)
    {
        if(node->prox != NULL && node->vmach < node->prox->vmach && node->opera == node->prox->opera)
        {
            if(velocidade >= node->vmach || velocidade == 0)
            velocidade = node->vmach;
        }
        else if(node->prox != NULL && node->vmach > node->prox->vmach && node->opera == node->prox->opera)
        {

            velocidade = node->prox->vmach;
        }
        if(node->prox == NULL || (node->prox != NULL && node->opera != node->prox->opera))
        {

            if(velocidade > node->vmach)
            {
            velocidade = node->vmach;
            }
            adicionar(&nova2, 1, 1, velocidade);
            velocidade = 0;
        }
       
        node = node->prox;
    }
    while(nova2 != NULL)
    {
        soma += nova2->vmach; 


        nova2 = nova2->prox;
    }
    printf("A velocidade minima possivel para este Job é: %d unidades de tempo", soma);

    freeNodes(&nova2);
}
void calcMax(lista **ref)
{

    int velocidade=0, soma=0;
    lista *node = *ref;
    lista *nova = NULL;
    

    while(node != NULL)
    {
        if(node->prox != NULL && node->vmach > node->prox->vmach && node->opera == node->prox->opera)
        {
            velocidade = node->vmach;
        }
        else if(node->prox != NULL && node->vmach < node->prox->vmach && node->opera == node->prox->opera)
        {
            velocidade = node->prox->vmach;
        }
        if(node->prox == NULL || (node->prox != NULL && node->opera != node->prox->opera))
        {

            if(velocidade < node->vmach)
            {
            velocidade = node->vmach;
            }
            adicionar(&nova, 1, 1, velocidade);
            velocidade = 0;
        }
       
        node = node->prox;
    }
    while(nova != NULL)
    {
        soma += nova->vmach;

        nova = nova->prox;
    }
    printf("A velocidade maxima para este Job é: %d unidades de tempo", soma);

    freeNodes(&nova);
}
void alterar(lista **eli, int operacao)
{
    lista *list = *eli;
    int Amaquina, Avelocidade;

    while(list != NULL)
    {

        if(list->opera == operacao)
        {
            printf("\nMaquina: %d", list->mach);
            printf("\nVelocidade: %d", list->vmach);
        }

        list = list->prox;
    }
    list = *eli;

    printf("\nMaquina a editar: ");
    scanf("%d", &Amaquina);
    printf("\nNova velocidade");
    scanf("%d", &Avelocidade);

    while(list != NULL)
    {
        if(list->opera == operacao)
        {
            if(list->mach == Amaquina)
            {
                list->vmach = Avelocidade;
            }

        }


        list = list->prox;
    }

}
void eliminar(lista **eli, int value)
{
    lista *list = *eli, *ant;
    /*Elimina caso o valor seja o do 1º elemento*/
    while(list != NULL && list->opera == value)
    {
        *eli = list->prox;
        free(list);
        list = *eli;
    }
    /*Elimina os valores inseridos que não o 1º elemento da lista*/
    while (list != NULL)
    {
        
        while (list != NULL && list->opera != value)
        {
            ant = list;
            list = list->prox;
        }
 
        
        if (list == NULL)
            return;
 
        ant->prox = list->prox;
 
        free(list); 
        list = list->prox;
    }
}
void adicionar(lista **ref,int a,int b,int c)
{
    lista *new= malloc(sizeof(lista));
    lista *last = *ref;
    new->opera = a;
    new->mach = b;
    new->vmach = c;
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
void printList(lista *node)
{
  while (node != NULL)
  {
    printf("Operacao->%d | Maquina->%d | Velocidade->%d\n", node->opera, node->mach, node->vmach);
    node = node->prox;
  }
}
int main(){

    lista *head = NULL;
    media *cabeca = NULL;
    int a,b,c,opcao,n,operacaoeli;
    FILE *fp;
    fp = fopen("Job.txt", "r");
    if(fp)
    {
    fileMem(&head);
    fclose(fp);
    }
    else{

    }
    

    do
    {
        int opcao=0;
        int operacao=0;
        int maquinas = 0;
        printf("\nMenu:\n");
        printf("1-Inserir operacao.\n");
        printf("2-Alterar operacao.\n");
        printf("3-Remover operacao.\n");
        printf("4-Tempo maximo do Job\n");
        printf("5-Tempo minimo do Job\n");
        printf("6-Tempo medio do Job\n");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                b=0;c=0;n=0;
                printf("Nº da operacao: ");
                scanf("%d", &operacao);
                printf("Numero de maquinas a inserir: ");
                scanf("%d", &maquinas);
                while(n<maquinas)
                {
                    printf("Valores: ");
                    scanf("%d %d",&b,&c);
                    adicionar(&head, operacao, b, c);
                    printf("\nLista criada!!!\n\n");
                    printList(head);
                    n++;
                }
                FILE * file;
                file = fopen("Job.txt", "r");
                if(file)
                {
                    ficheirosLista2(&head);
                    fclose(file);
                }else{
                    ficheirosLista(&head);
                }
            break;

            case 2:
                printf("Operacao a alterar");
                scanf("%d", &operacao);
                alterar(&head, operacao);
                ficheirosLista2(&head);
                printList(head);
                break;
            case 3:
                printf("Operacao a eliminar: ");
                scanf("%d",&operacaoeli);
                eliminar(&head, operacaoeli);
                ficheirosLista2(&head);
                printList(head);
                break;
            case 4:
                calcMax(&head);
                break;
            case 5:
                calcMin(&head);
                break;
            case 6:
                calcMax(&head);
                break;
            


        }
    }while(opcao =! 0);
}