#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    int opera;
    int mach;
    int vmach;
    struct No* prox;
}lista;

struct No* head;

void inserirlista(struct No *prev,struct No *head,int *op,int *mach, int *vmach)
{
    struct No* temp = malloc(sizeof(lista));
    temp->opera = *op;
    temp->mach = *mach;
    temp->vmach = *vmach;
    temp->prox = NULL;
    if(head == NULL)
    {
        head = temp;
    }
    else
    {
        prev->prox=temp;
    }
    prev=temp;



    while(temp->prox != NULL)
    {
        printf("\nOperação - %d", temp->opera);
        printf("\nMaquina- %d\n", temp->mach);
        printf("Velocidade- %d\n--------------",temp->vmach);
        printf("%p", temp);
        temp=temp->prox;
    }









}
void printarlista()
{






}
int main(){

    int a,b,c,op;
    struct No* first= malloc(sizeof(lista))
    struct No* prev;

    printf("Numero da operacao: ");
    scanf("%d", &op);
    printf("Quantidade de maquinas que pretende inserir: ");
    scanf("%d", &a);

    for(int i=0;i<a;i++)
    {
        printf("Valores: ");
        scanf("%d %d",&b,&c);
        inserirlista(prev,first,&op,&b,&c);
    }

}