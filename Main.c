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
    else
    {
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
    }while(opcao != 9);
}