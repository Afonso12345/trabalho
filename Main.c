#include <stdio.h>
#include <stdlib.h>
#include <funcoes.h>

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
                printf("Operacao a alterar:");
                scanf("%d", &operacao);
                alterar(&head, operacao);
                ficheirosLista2(&head);
                break;
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
                printf("Operacao a alterar");
                scanf("%d", &operacao);
                alterar(&head, operacao);
                ficheirosLista2(&head);
                break;
            case 5:
                break;
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
}