#include "Novo.h"
void corrigirOperacoes(jobs **ref, int job)
{
    jobs *lista = *ref;
    opera *lista1;
    maqs *lista2;
    int a = 0;


    while(lista != NULL)
    {
        
        if(job == lista->job)
        {
        lista1 = lista->iniop;
        while(lista1 != NULL)
        {
            if((a+1) == lista1->num_opera)
            {
                a = lista1->num_opera;
            }
            else
            {
                lista1->num_opera--;
            }
            lista1 = lista1->prox;
        }
        }
        lista = lista->prox;
    }
}
void removerMaquinas(jobs **ref, int job, int ope, int maq)
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
               lista2 = lista1->ini_maq;
               while(lista2 != NULL && lista2->mach == maq)
               {
                   lista1->ini_maq = lista2->prox;
                   prox = lista2->prox;
                   free(lista2);
                   return;
               }
               lista1 = lista1->prox;
            }
        }
        lista = lista->prox;
    }

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
int verificarNumero(jobs **ref, int job)
{
    jobs *lista = *ref;
    opera *lista1;
    maqs *lista2;
    int a = 0;


    while(lista != NULL)
    {
        if(job == lista->job)
        {
            lista1 = lista->iniop;
            while(lista1 != NULL)
            {   
                a = lista1->num_opera;
                lista1 = lista1->prox;
            }
        }
        lista = lista->prox;
    }


    return a+1;
}
int verificarCaracteres()
{
    FILE* fp;
    int count=0;
    char c;
    
    fp = fopen("Process.txt", "r");

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
                nova2 = nova->ini_maq;
                if(nova->num_opera == ope)
                {
                    while(nova2 != NULL)
                    {
                        if(nova2->mach == maq)
                        {
                            return T;
                        }
                        nova2 = nova2->prox;
                    }

                }
                nova = nova->prox;
            }
        }
        lista = lista->prox;
    }

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
void GuardarFicheiro2(jobs **ref)
{
    jobs *n = *ref;
    opera *n1;
    maqs *n2;
    FILE *open;

    open = fopen("Process2.txt","a");

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
    remove("Process.txt"),
    rename("Process2.txt", "Process.txt");
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
void PrintaOperacoesEscolhida(jobs **ref,int job)
{
    jobs *nova1 = *ref;
    opera *nova;
    maqs *nova2;

    while(nova1 != NULL)
    {
        nova = nova1->iniop;
        if(job == nova1->job)
        {
        printf("Job %d\n", nova1->job);
            while(nova != NULL)
            {
                nova2 = nova->ini_maq;
                printf("\nOperação %d\n",nova->num_opera);
                while(nova2 != NULL)
                {
                    printf("Maquina->%d | Velocidade->%d\n", nova2->mach,nova2->vmach);
                    nova2 = nova2->prox;
                }
                nova = nova->prox;
            }
        }

        nova1 = nova1->prox;
    }
    nova1 = *ref;



}
void PrintaOperacoes(jobs **ref)
{
    jobs *nova1 = *ref;
    opera *nova;
    maqs *nova2;

    while(nova1 != NULL)
    {
        nova = nova1->iniop;
        printf("\nJob %d\n", nova1->job);
        while(nova != NULL)
        {
            nova2 = nova->ini_maq;
            printf("\nOperacao %d\n",nova->num_opera);
            printf("----------------------------------\n");
            while(nova2 != NULL)
            {
                printf("Maquina->%d | Velocidade->%d\n", nova2->mach,nova2->vmach);
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
        return;
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
    printf("Jobs existentes\n");
    printf("---------------------");
    while(ref != NULL)
    {
        printf("\nJob %d", ref->job);
        ref = ref->prox;
    }
}
void CriarOperacoes2(jobs **ref, int b)
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

    new->num_opera = verificarNumero(ref,b);
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
    int opcao, a, job, ope, maq, vmaq, velo;
    char c, d;
    FILE *fp;



    if((fp = fopen("Process.txt", "r")) != NULL && verificarCaracteres() != 0)
    {
        fileMem(head);
        fclose(fp);
    }
    else
    {

    }


    do
    {
        system("clear");
        job = 0;
        int operacao=0;
        int maquinas = 0;
        printf("\nMenu:\n");
        printf("1-Inserir job.\n");
        printf("2-Remover job.\n");
        printf("3-Inserir operacao.\n");
        printf("4-Remover operacao.\n");
        printf("5-Alterar operacao.\n");
        printf("6-Mostrar Jobs e Operações.\n");
        printf("7-Sair.\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                do{
                    printf("\nNumero do job: ");
                    scanf("%d", &job);
                    if(VerificarJobs(head,job) == T && job != 0)
                    {
                        printf("Erro, inserir novamente!");
                    }

                }while(VerificarJobs(head,job) == T);
                CriarJob(head,job);
                GuardarFicheiro(head);
                break;
            case 2:
                system("clear");
                PrintaJobs(*head);
                do{
                    printf("\n\nNumero do job a eliminar: ");
                    scanf("%d", &job);
                    if(VerificarJobs(head,job) != T)
                    {
                        printf("\nJob não existe!\n");
                    }
                }while(VerificarJobs(head,job) != T);
                eliminarJob(head, job);
                GuardarFicheiro2(head);
                break;
            case 3:
            do{
                printf("\nNumero do job: ");
                scanf("%d", &job);
                if(VerificarJobs(head,job) != T)
                {
                    printf("Job não existe!");
                }
            }while(VerificarJobs(head,job) != T);

                CriarOperacoes2(head, job);
                ope = (verificarNumero(head, job)) - 1;
                do{
                    do{
                        printf("\nNumero da maquina: ");
                        scanf("%d", &maq);
                        if(VerificarMaqs(head,job,ope,maq) == T)
                        {
                            printf("\nErro, inserir novamente!\n");
                        }
                    }while(VerificarMaqs(head,job,ope,maq) == T);
                    printf("Velocidade da maquina:  ");
                    scanf("%d", &velo);
                    CriarMaquinas(head, ope, job, maq, velo);
                    printf("Inserir mais maquinas?(S/N)");
                    scanf(" %c", &c);
                }while(c == 's' || c == 'S');
                if((fp = fopen("Process.txt", "r")) != NULL)
                {
                    GuardarFicheiro2(head);
                    fclose(fp);
                }
                else
                {
                    GuardarFicheiro(head);
                }
                break;
            case 4:
                printf("Numero do job: ");
                scanf("%d", &job);
                printf("Numero de operacao: ");
                scanf("%d", &ope);
                eliminarOperacoes(head,job,ope);
                corrigirOperacoes(head,job);
                GuardarFicheiro2(head);
                break;
            case 5:
                system("clear");
                printf("\nJobs existentes:\n");
                PrintaJobs(*head);
                do{
                    printf("\nJob:");
                    scanf("%d", &job);
                    if(VerificarJobs(head,job) != T)
                    {
                        printf("Job não existe, escolher um presente na lista!\n");
                    }
                }while(VerificarJobs(head,job) != T);
                system("clear");
                PrintaOperacoesEscolhida(head,job);
                do{
                    printf("\nOperação a modificar: ");
                    scanf("%d", &ope);
                    if(VerificarOperações(head,job,ope) != T)
                    {
                        printf("Operacao nao existe, escolher uma presente na lista!\n");
                    }
                }while(VerificarOperações(head,job,ope) != T);
                system("clear");
                MenuOperações(head,job,ope);
                break;
            case 6:
                system("clear");
                do{
                PrintaOperacoes(head);
                printf("\nInsira S/s para avançar ");
                scanf(" %c", &d);
                }while(d != 's' && d != 'S');
                break; 
            case 7:
                continue;
        }
    }while(opcao != 7);
}

void MenuOperações(jobs **head, int job, int ope)
{
    int opcao, maquina, velo;
    char c;

    do{
        maquina = 0;
        printf("\nMenu Operações:\n");
        printf("1-Inserir maquina em operação.\n");
        printf("2-Remover Maquinas.\n");
        printf("3-Alterar Maquinas.\n");
        printf("4-Sair.\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                do{
                    do{
                    
                        printf("Insira maquina: \n");
                        scanf("%d", &maquina);
                        if(maquina < 0)
                        {
                            printf("Insira valor maior que 0!!\n");
                        }
                    }while(maquina < 0);
                    
                    if(VerificarMaqs(head,job,ope,maquina) != T)
                    {
                        printf("Maquina não existe!\n");
                    }
                }while(VerificarMaqs(head,job,ope,maquina) != T);
                CriarMaquinas(head,ope,job,maquina,velo);
                GuardarFicheiro2(head);
                break;
            case 2:
                do{
                    do{
                    
                        printf("Insira maquina a remover: \n");
                        scanf("%d", &maquina);
                        if(maquina < 0)
                        {
                            printf("Insira valor maior que 0!!\n");
                        }
                    }while(maquina < 0);
                    
                    if(VerificarMaqs(head,job,ope,maquina) != T)
                    {
                        printf("Maquina não existe!\n");
                    }
                }while(VerificarMaqs(head,job,ope,maquina) != T);
                removerMaquinas(head,job,ope,maquina);
                break;
            case 3:

                break;
            case 4:
                continue;





        }














    }while(opcao != 4);



}
