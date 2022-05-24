#include "Novo.h"
bool VerificarJobs(jobs **ref, int job)
{
    jobs *lista = *ref;


    while(lista != NULL)
    {
        if(lista->job == job)
        {
            return T;
        }
        lista = lista->prox;
    }
}

bool VerificarOperações(jobs **ref, int job, int ope)
{
    jobs *lista = *ref;
    opera *nova;
    maqs *nova2;

    while(lista != NULL)
    {
        nova = lista->iniop;
        if(lista->job == job)
        {
            while(nova != NULL)
            {
                if(nova->num_opera == ope)
                {
                    return T;
                }
                nova = nova->prox;
            }
        }

       lista = lista->prox;
    }
}
bool VerificarMaqs(jobs **ref, int job, int ope, int maq)
{

}
void fileMem(jobs **ref)
{
    jobs *head = *ref;
    FILE *open;
    int a,b,c,d;

    open = fopen("Process.txt", "r");

    while(!feof(open))
    {
        fscanf(open, "%d %d %d %d\n" ,&a,&b,&c,&d);
        if(VerificarJobs(ref, a) != T)
        {
            CriarJob(ref,a);
        }
        if(VerificarOperações(ref,a,b) != T)
        {
            CriarOperacoes(ref,b,a);
        }
        CriarMaquinas(ref,b,a,c,d);
    }
    fclose(open);
}


void GuardarFicheiro(jobs **ref)
{
    jobs *n = *ref;
    opera *n1;
    maqs *n2;
    FILE *open;

    open = fopen("Process.txt","a");

    while(n != NULL)
    {

        n1 = n->iniop;
        while(n1 != NULL)
        {
            n2 = n1->ini_maq;
            while(n2 != NULL)
            {
                fprintf(open,"%d %d %d %d\n", n->job, n1->num_opera ,n2->mach, n2->vmach);
                n2 = n2->prox;
            }
            n1 = n1->prox;
        }
        n = n->prox;
    }
    fclose(open);
}
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
    opera *nova;
    maqs *nova2;

    while(nova1 != NULL)
    {
        nova = nova1->iniop;
        printf("Numero do job %d\n", nova1->job);
        printf("Operações existentes:\n");
        while(nova != NULL)
        {
            nova2 = nova->ini_maq;
            printf("%d\n",nova->num_opera);
            while(nova2 != NULL)
            {
                printf("\nNumero de maquina: %d", nova2->mach);
                printf("\nVelocidade da maquina: %d\n", nova2->vmach);
                nova2 = nova2->prox;
            }
            nova = nova->prox;
        }

        nova1 = nova1->prox;
    }
    nova1 = *ref;

}
void eliminarOperacoes(jobs **ref, int job, int ope)
{
    jobs *lista = *ref;
    opera *lista1, *ant;
    maqs *lista2, *prox;

    while(lista != NULL)
    {
        if(lista->job == job)
        {
            lista1 = lista->iniop;
            while(lista1 != NULL && lista1->num_opera == ope)
            {
               lista->iniop = lista1->prox; 
               lista2 = lista1->ini_maq;
               while(lista2 != NULL)
               {
                   prox = lista2->prox;
                   free(lista2);
                   lista2 = prox;
               }
               free(lista1);
               return;
            }
        }
        lista = lista->prox;
    }
    lista = *ref;

    while(lista != NULL)
    {
        if(lista->job == job)
        {
            lista1 = lista->iniop;
            while(lista1 != NULL && lista1->num_opera != ope)
            {
                ant = lista1;
                lista1 = lista1->prox;
            }
            lista1 = lista->iniop;
            while(lista1 != NULL)
            {
                if(lista1->num_opera == ope)
                {
                lista2 = lista1->ini_maq;
                while(lista2 != NULL)
                {   
                    prox = lista2->prox;
                    free(lista2);
                    lista2 = prox;
                }
                }

                if(lista1->num_opera == ope)
                {
                    ant->prox = lista1->prox;
                    free(lista1);
                    lista1 = ant->prox;
                    return;
                }


                lista1 = lista1->prox;
            }
        }
        lista = lista->prox;
    }

}
void eliminarJob(jobs **ref, int a)
{
    jobs *lista = *ref, *ant;
    opera *nova, *eli;
    maqs *nova1, *eli1;
    while(lista != NULL && lista->job == a)
    {
        *ref = lista->prox;
        nova = lista->iniop;
        while(nova != NULL)
        {
            eli = nova->prox;
            nova1 = nova->ini_maq;
            while(nova1 != NULL)
            {
                eli1 = nova1->prox;
                free(nova1);
                nova1 = eli1;
            }
            free(nova);
            nova = eli;
        }
        free(lista);
        lista = *ref;
    }

    while(lista != NULL)
    {
        while(lista != NULL && lista->job != a)
        {
            ant = lista;
            lista = lista->prox;
            nova = ant->prox->iniop;
        }
        nova = ant->prox->iniop;
        while(nova != NULL)
        {
            eli = nova->prox;
            nova1 = nova->ini_maq;
            while(nova1 != NULL)
            {
                eli1 = nova1->prox;
                free(nova1);
                nova1 = eli1;
            }
            free(nova);
            nova = eli;
        }
        if (lista == NULL)
            return;
 
        ant->prox = lista->prox;
 
        free(lista); 
        lista = ant->prox;
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
    opera **c;

    while(ola != NULL)
    {
        if(b == ola->job)
        {
            c = &(ola->iniop);
        }

        ola = ola->prox;
    }

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
void CriarMaquinas(jobs **ref, int a, int b, int maq, int vmaq)
{
    maqs *new = malloc(sizeof(maqs));
    jobs *ola = *ref;
    opera **c;
    maqs **d;

    while(ola != NULL)
    {
        if(b == ola->job)
        {
            c = &(ola->iniop);
        }
        ola = ola->prox;
    }

    ola = *ref;

    opera *e = *c;

    while(ola != NULL)
    {
        while(e != NULL)
        {
            if(a == e->num_opera)
            {
                d = &(e->ini_maq);
            }
            e = e->prox;
        }
        ola = ola->prox;
    }

    new->mach = maq;
    new->vmach = vmaq;
    new->prox = NULL;

    maqs *last = *d;

    if(*d == NULL)
    {
        *d = new;
        return;
    }

    while(last->prox != NULL)
    {
        last = last->prox;
    }
    last->prox = new;
    return;






}
void menu(jobs **head)
{
    int opcao, a, job, ope, maq, vmaq;


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
                scanf("%d", &ope);
                printf("Numero de maquina: ");
                scanf("%d", &maq);
                printf("Velocidade da maquina: ");
                scanf("%d", &vmaq);

                if(VerificarOperações(head,job,ope) != T)
                {
                CriarOperacoes(head,ope,job);
                }

                CriarMaquinas(head,ope,job,maq,vmaq);
                break;
            case 4:
                printf("Numero do job: ");
                scanf("%d", &job);
                printf("Numero de operacao: ");
                scanf("%d", &ope);
                eliminarOperacoes(head,job,ope);
                break;
            case 5:
                GuardarFicheiro(head);
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
