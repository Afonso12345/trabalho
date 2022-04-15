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

typedef struct Nod
{
    struct Nod* prim;
    struct Nod* ultimo;
}links;
void adicionarMedia(media **ref, int a, float b);
int contador(lista* r, int a);
void adicionar(lista** ref, int a, int b, int c);
/*lista *criaA(lista *insert,lista *novo)
{
    novo->prox = insert->prox;
    insert->prox = novo;
}*/
void printi(lista *head)
{
    lista *temp = head;

    while(temp != NULL)
    {
        printf("%d->%d->%d\n", temp->opera,temp->mach,temp->vmach);
        temp = temp->prox;
    }
}

void ficheiros

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
    int velocidade = 0;
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
        /*if(node->vmach > velocidade && node->prox == NULL)
        {
            velocidade = node->vmach;
        }*/
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
        printf("Velocidade: %d", nova2->vmach);


        nova2 = nova2->prox;
    }
}

void calcMax(lista **ref)
{
    int velocidade=0;
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
        /*if(node->vmach > velocidade && node->prox == NULL)
        {
            velocidade = node->vmach;
        }*/
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
        printf("Velocidade: %d", nova->vmach);


        nova = nova->prox;
    }
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
 
int contador(lista *lista, int value)
{
    int contadora=0;
    while(lista != NULL)
    {
        if(lista->opera == value)
        {
            contadora++;
        }
    lista = lista->prox;
    }
    
    return contadora;

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
            break;

            case 2:
                printList(head);
            break;
            case 3:
                printf("Operacao a eliminar: ");
                scanf("%d",&operacaoeli);

                eliminar(&head, operacaoeli);
                printList(head);
                break;
            case 4:
                printf("Operacao a alterar");
                scanf("%d", &operacao);
                alterar(&head, operacao);
            case 5:
                printf("Numero de 1's: %d", contador(head,2));
            case 6:
                calcMax(&head);
                break;
            case 7:
                adicionar(&head, 1, 1, 5);
                adicionar(&head, 1, 3, 4);
                adicionar(&head, 2, 2, 4);
                adicionar(&head, 2, 4, 5);
                adicionar(&head, 3, 3, 5);
                adicionar(&head, 3, 5, 6);
                adicionar(&head, 4, 4, 5);
                adicionar(&head, 4, 5, 5);
                adicionar(&head, 4, 6, 4);
                adicionar(&head, 4, 7, 5);
                adicionar(&head, 4, 8, 9);
                break;
            case 8:
                calcMin(&head);
                break;
            case 9:
                calcMedia(&head, &cabeca);
                break;




        }
    }while(opcao =! 0);

    /*lista *tmp;
    int a,b,c,maquina;

    printf("lista:");
    scanf("%d %d %d", &a,&b,&c);

    
    tmp = cria(a,b,c);
    first = tmp;
    tmp = cria(a,c,b);
    tmp->prox = first;
    first = tmp;
    printf("maquina para encontrar: ");
    scanf("%d", &maquina);
    tmp = find(first, maquina);
    printf("found node is %d e a velocidade é %d\n",tmp->mach, tmp->vmach);
    criaA(first, cria(a,c,b));
    printf("%p", first);
    return 0;*/
    
    





}


