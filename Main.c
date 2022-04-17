#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

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
                do{
                    printf("\nNº da operacao: ");
                    scanf("%d", &operacao);
                    if(verificarExiste(&head, operacao) == T)
                    {
                        printf("\nA operação já existe, digite novamente!\n");
                    }
                }while(verificarExiste(&head, operacao) == T);

                printf("Numero de maquinas a inserir: ");
                scanf("%d", &maquinas);
                while(n<maquinas)
                {
                    do{
                        printf("\nNumero de maquina: ");
                        scanf("%d", &b);
                        if(verificarExisteMaquina(&head, b, operacao) == T)
                        {
                            printf("\nMaquina já existe, digite novamente!\n");
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
                calcMedia(&head, &cabeca);
                break;
            case 7:
                printList(head);
                break;
            case 8:
                printf("%d", verificarCaracteres());
                break;
            


        }
    }while(opcao != 9);
}