#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { F, T } bool;

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
void freeNodesMedia(media **ref);
int verificarCaracteres();
bool verificarExiste(lista **ref, int operation);
bool verificarExisteMaquina(lista **ref, int maquinas, int operacao);


bool verificarExisteMaquina(lista **ref, int maquinas, int operacao)
{
    lista *node = *ref;

    while(node != NULL)
    {
      if(operacao == node->opera)
      {  
        if(maquinas == node->mach)
        {
            return T;
        }
      }
    node = node->prox;
    }

}
bool verificarExiste(lista **ref, int operation)
{
    lista *node = *ref;

    while(node != NULL)
    {
        
        if(operation == node->opera)
        {   
            return T;
        }




    node = node->prox;

    }

}

int verificarCaracteres()
{
    FILE* fp;
    int count=0;
    char c;
    
    fp = fopen("Job.txt", "r");

    if(fp == NULL)
    {
        return 1;

    }
    else
    {
        for (c = getc(fp); c != EOF; c = getc(fp))
            {
            count = count + 1;
            }
        return count;      
        
    }
    fclose(fp);
}
void freeNodesMedia(media **ref)
{
    media *list = *ref;
    while(list != NULL)
    {
        *ref = list->proxx;
        free(list);
        list = *ref;
    }

}
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
        printf("Operação:%d  Media:%.2f ", node->operat, node->media);

        node = node->proxx;
    }
    freeNodesMedia(&node);

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

            if(velocidade > node->vmach || velocidade == 0)
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

    printf("Maquinas existentes:\n");

    while(list != NULL)
    {   

        if(list->opera == operacao)
        {
            printf("\n\nMaquina-> %d | Velocidade->%d ", list->mach, list->vmach);
        }

        list = list->prox;
    }
    list = *eli;

    printf("\n\nMaquina a editar: ");
    do{
        scanf("%d", &Amaquina);
        if(verificarExisteMaquina(*&eli, Amaquina, operacao) != T)
        {
            printf("\nMaquina não existe!Introduza novamente: ");
        }
    }while(verificarExisteMaquina(*&eli, Amaquina, operacao) != T);
    printf("\nNova velocidade: ");
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
    printf("\nOperações existentes: \n");
    while (node != NULL)
    {
        printf("Operacao->%d | Maquina->%d | Velocidade->%d\n", node->opera, node->mach, node->vmach);
        node = node->prox;
    }
}
int main()
{

    lista *head = NULL;
    media *cabeca = NULL;
    int a,b,c,opcao,n,operacaoeli;
    FILE *fp;
    fp = fopen("Job.txt", "r");
    if(fp && verificarCaracteres() != 0)
    {
        fileMem(&head);
        fclose(fp);
    }
    else
    {
        fclose(fp);
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
        printf("4-Tempo maximo do Job.\n");
        printf("5-Tempo minimo do Job.\n");
        printf("6-Tempo medio do Job.\n");
        printf("7-Mostrar a lista de operações.\n");
        printf("8-Sair.\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                b=0;c=0;n=0;
                printf("\nNº da operacao: ");
                do{
                    scanf("%d", &operacao);
                    if(verificarExiste(&head, operacao) == T)
                    {
                        printf("\n\nA operação já existe!Introduz novamente: ");
                    }
                }while(verificarExiste(&head, operacao) == T);
                printf("Numero de maquinas a inserir: ");
                scanf("%d", &maquinas);
                while(n<maquinas)
                {
                    printf("\nNumero de maquina: ");
                    do{
                        scanf("%d", &b);
                        if(verificarExisteMaquina(&head, b, operacao) == T)
                    {
                        printf("\n\nA maquina já existe!Introduz novamente: ");
                    }
                    }while(verificarExisteMaquina(&head, b, operacao) == T);
                    printf("\nVelocidade da maquina: ");
                    scanf("%d",&c);
                    adicionar(&head, operacao, b, c);
                    printf("\n\n");
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
                printf("\nOperacao a alterar: ");
                do{
                    scanf("%d", &operacao);
                    if(verificarExiste(&head, operacao) == F)
                    {
                        printf("Operação não existe!\nInsira novamente: ");
                    }
                    
                }while(verificarExiste(&head, operacao) == F);
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
                calcMedia(&head, &cabeca);
                break;
            case 7:
                printList(head);
                break;

        }
    }while(opcao != 8);
}