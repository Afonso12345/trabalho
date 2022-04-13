#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int operacao;
    int nMach;
    int vMach;
    struct Node* prox;
}NodeJ;
struct Node* head;
void Inserir(int* x,int* v,int* o)
{
    struct Node* temp = (NodeJ*)malloc(sizeof(NodeJ));
    temp->operacao = *o;
    temp->nMach = *x;
    temp->vMach = *v;
    temp->prox=head;
    /*printf("%ld",sizeof(temp->operacao));
    printf("%ld",sizeof(temp->nMach));
    printf("%ld",sizeof(temp->vMach));
    printf("%ld",sizeof(temp->prox));
    */
    head=temp;
    printf("%d", *head);
}
void Print(){
    struct Node* Node = head;
    printf("Lista: ");
    while(Node != NULL)
    {
        printf("\nOperação - %d", Node->operacao);
        printf("\nMaquina- %d\n", Node->nMach);
        printf("Velocidade- %d\n--------------",Node->vMach);
        printf("%p", Node);
        Node=Node->prox;
    }
    printf("\n");
}
int find(int findop, NodeJ ray)
{
    struct Node* atual = head;
    int contador = 0;

    while(atual != NULL)
    {
        if(contador == atual->operacao)
        {
            return(atual->nMach);
        }
        contador++;
        atual = atual->prox;
    }
    


}
/*void Printt(NodeJ *p){

    if(p == NULL) return;
    printf("%d",p->nMach);
    printf("%d",p->vMach);
    printf("%d",p->op);
}*/
    
    
int main(){
   int opcao,i,n;
   int x,v,o;
   int findop;
   NodeJ ray;
    do{
        opcao = 0;
        printf("Opcao: ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
            head = NULL;
            printf("Numero de maquinas: ");
            scanf("%d", &n);
            for(i=0;i<n;i++)
            {
                printf("Insira o operação: ");
                scanf("%d",&o);
                printf("Insira o numero de maquina: ");
                scanf("%d",&x);
                printf("Insira o velocidade da maquina: ");
                scanf("%d",&v);
                Inserir(&x,&v,&o);
                Print();
            }
            break;
            case 2:
            printf("Numero que quer encontrar: ");
            scanf("%d", &findop);
            find(findop,ray);
            printf("%d", find(findop,ray));
        }
   

   }while(opcao != 0);
   
}

