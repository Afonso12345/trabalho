#include "Novo.h"

/**
 * @brief Função para corrigir numero das operações após a eliminação de uma delas.
 * 
 * @param ref 
 * @param job 
 */
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
/**
 * @brief Função para alterar valores de uma determinada máquina.
 * 
 * @param ref 
 * @param job 
 * @param ope 
 * @param maq 
 * @param novamaq 
 * @param novavelo 
 */
void alterarMaquinas(jobs **ref, int job, int ope, int maq, int novamaq, int novavelo)
{
    jobs *lista = *ref;
    opera *lista1;
    maqs *lista2;
    
    while(lista != NULL)
    {
        if(job == lista->job)
        {
            lista1 = lista->iniop;
            while(lista1 != NULL)
            {
                if(lista1->num_opera == ope)
                {
                    lista2 = lista1->ini_maq;
                    while(lista2 != NULL)
                    {
                        if(lista2->mach == maq)
                        {
                            lista2->mach = novamaq;
                            lista2->vmach = novavelo;
                        }
                        lista2 = lista2->prox;
                    }
                }
                lista1 = lista1->prox;
            }
        }
        lista = lista->prox;
    }
}
/**
 * @brief Função para remover máquinas da lista de máquinas
 * 
 * @param ref 
 * @param job 
 * @param ope 
 * @param maq 
 */
void removerMaquinas(jobs **ref, int job, int ope, int maq)
{
    jobs *lista = *ref;
    opera *lista1, *ant;
    maqs *lista2, *prox, *ant1;

    while(lista != NULL)
    {
        if(lista->job == job)
        {
            lista1 = lista->iniop;
            while(lista1 != NULL)
            {
                if(lista1->num_opera == ope)
                {
                    lista2 = lista1->ini_maq;
                    while(lista2 != NULL && lista2->mach == maq)
                    {
                        lista1->ini_maq = lista2->prox;
                        prox = lista2->prox;
                        free(lista2);
                        return;
                    }
                }
                lista1 = lista1->prox;
            }
        }
        lista = lista->prox;
    }
    lista =*ref;

    while(lista != NULL)
    {
        if(lista->job == job)
        {
            lista1 = lista->iniop;
            while(lista1 != NULL)
            {
                if(lista1->num_opera == ope)
                {
                    lista2 = lista1->ini_maq;
                    while(lista2 != NULL)
                    {
                        while(lista2 != NULL && lista2->mach != maq)
                        {
                            ant1 = lista2;
                            lista2 = lista2->prox;
                        }
                        if(lista2 == NULL)
                        {
                            return;
                        }
                        if(lista2->mach == maq)
                        {
                            ant1->prox = lista2->prox;
                            free(lista2);
                            lista2 = ant1->prox;
                            return;
                        }
                    }
                }
                lista1 = lista1->prox;
            }

        }
        lista = lista->prox;
    }
}
/**
 * @brief Função que verifica o numero das operações existentes na lista.
 * 
 * @param ref 
 * @param job 
 * @return int 
 */
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
/**
 * @brief Função que verifica os carateres de um ficheiro de texto.
 * 
 * @return int 
 */
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
/**
 * @brief Função que verifica se job já existe na lista de jobs.
 * 
 * @param ref 
 * @param job 
 * @return boolean 
 */
boolean VerificarJobs(jobs **ref, int job)
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
/**
 * @brief Função que verifica se operação existe no job escolhido.
 * 
 * @param ref 
 * @param job 
 * @param ope 
 * @return boolean 
 */
boolean VerificarOperacoes(jobs **ref, int job, int ope)
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
/**
 * @brief Função helper para verificar se máquina existe na lista
 * 
 * @param ref 
 * @param job 
 * @param ope 
 * @param maq 
 * @return boolean 
 */
boolean VerificarMaqs(jobs **ref, int job, int ope, int maq)
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
/**
 * @brief Função que guarda dados da memória no ficheiro de texto
 * 
 * @param ref 
 */
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
        if(VerificarOperacoes(ref,a,b) != T)
        {
            CriarOperacoes(ref,b,a);
        }
        CriarMaquinas(ref,b,a,c,d);
    }
    fclose(open);
}
/**
 * @brief Função que guarda no ficheiro de texto
 * 
 * @param ref 
 */
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

/**
 * @brief Função que guarda no ficheiro de texto
 * 
 * @param ref 
 */
void GuardarFicheiro(jobs **ref)
{
    jobs *n = *ref;
    opera *n1;
    maqs *n2;
    FILE *open;

    open = fopen("Process.txt","w");

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
/**
 * @brief Função que cria um job.
 * 
 * @param ref 
 * @param a 
 */
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
/**
 * @brief Função que printa uma só operação escolhida de um determinado job.
 * 
 * @param ref 
 * @param job 
 * @param ope 
 */
void PrintaOperacoesEscolhida1(jobs **ref,int job, int ope)
{
    jobs *nova1 = *ref;
    opera *nova;
    maqs *nova2;

    while(nova1 != NULL)
    {
        nova = nova1->iniop;
        if(job == nova1->job)
        {
             printf("\nJOB---->%d\n", nova1->job);
            while(nova != NULL)
            {
                nova2 = nova->ini_maq;
                if(nova->num_opera == ope)
                {
                printf("\nOperacao %d\n",nova->num_opera);
                printf("----------------------------------\n");
                while(nova2 != NULL)
                {
                    printf("Maquina->%d | Velocidade->%d\n", nova2->mach,nova2->vmach);
                    nova2 = nova2->prox;
                }
                }
                nova = nova->prox;
            }
        }

        nova1 = nova1->prox;
    }
    nova1 = *ref;



}
/**
 * @brief Função que printa as operações do job escolhido.
 * 
 * @param ref 
 * @param job 
 */
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
            printf("\nJOB---->%d\n", nova1->job);
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
        }

        nova1 = nova1->prox;
    }
    nova1 = *ref;



}
/**
 * @brief Função que printa as operações de todos os jobs.
 * 
 * @param ref 
 */
void PrintaOperacoes(jobs **ref)
{
    jobs *nova1 = *ref;
    opera *nova;
    maqs *nova2;

    while(nova1 != NULL)
    {
        nova = nova1->iniop;
        printf("\nJOB---->%d\n", nova1->job);
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
/**
 * @brief Função que elimina a operação escolhida
 * 
 * @param ref 
 * @param job 
 * @param ope 
 */
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
/**
 * @brief Função que elimina job escolhido.
 * 
 * @param ref 
 * @param a 
 */
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
        }
        nova=lista->iniop;
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
        return;
    }

}
/**
 * @brief Função para printar jobs.
 * 
 * @param ref 
 */
void PrintaJobs(jobs *ref)
{

    while(ref != NULL)
    {
        printf("\nJob %d", ref->job);
        ref = ref->prox;
    }
}
/**
 * @brief Cria operações nos jobs escolhidos.
 * 
 * @param ref 
 * @param b 
 */
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
    new->feito = false;

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
/**
 * @brief Cria operações no job escolhido.
 * 
 * @param ref 
 * @param a 
 * @param b 
 */
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
    new->feito = false;

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
/**
 * @brief Cria maquinas nas operações escolhidas
 * 
 * @param ref 
 * @param a 
 * @param b 
 * @param maq 
 * @param vmaq 
 */
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
/**
 * @brief Cria maquinas da lista de escalonamento
 * 
 * @param ref 
 * @param maq 
 */
void criarMaquinasPUso(maqsUso **ref, int maq)
{
    maqsUso* new = malloc(sizeof(maqsUso));
    maqsUso* lista = *ref;

    new->Maquinas = maq;
    new->inicio = NULL;
    new->prox = NULL;
    new->inUse = false;

    if(*ref == NULL)
    {
        *ref = new;
        return;
    }

    while(lista->prox != NULL)
    {
        lista = lista->prox;
    }
    lista->prox = new;
    return;
}
/**
 * @brief Cria a lista de escalonamento.
 * 
 * @param ref 
 * @param maq 
 * @param job 
 * @param ope 
 * @param vtime 
 * @param contador 
 */
void criarEscalonar(maqsUso **ref, int maq, int job, int ope, int vtime, int contador)
{
    scale *new = malloc(sizeof(maqsUso));
    maqsUso *ola = *ref;
    scale **c;

    while(ola != NULL)
    {
        if(maq == ola->Maquinas)
        {
            c = &(ola->inicio);
        }
        ola = ola->prox;
    }
    new->inicio = contador;
    new->job = job;
    new->opera = ope;
    new->tempo = vtime;
    new->prox = NULL;

    scale *last = *c;

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
/**
 * @brief Verifica se a operação já existe na lista de escalonamento
 * 
 * @param ref 
 * @param job 
 * @param opera 
 * @param maq 
 * @return boolean 
 */
boolean verificarExistencia(maqsUso **ref,int job, int opera, int maq)
{
    maqsUso *lista = *ref;
    scale *lista1;

    while(lista != NULL)
    {
        if(maq == lista->Maquinas)
        {
            lista1=lista->inicio;
            while(lista1 != NULL)
            {
                if(job == lista1->job && opera == lista1->opera)
                {
                    return T;
                }
                lista1 = lista1->prox;
            }
        }
        lista = lista->prox;
    }

}
/**
 * @brief Função que verifica se a proxima maquina a adicionar na lista de escalonamento existe na lista ou não
 * 
 * @param ref 
 * @param maq 
 * @return boolean 
 */
boolean verificarMaquinasListamaquinas(maqsUso **ref, int maq)
{
    maqsUso *lista = *ref;

    while(lista != NULL)
    {
        if(lista->Maquinas == maq)
        {
            return T;
        }
        lista = lista->prox;
    }
}
/**
 * @brief Função que cria lista de máquinas para o escalonamento.
 * 
 * @param head 
 * @param head1 
 */
void criarMaquinasHelp(jobs **head, maqsUso **head1)
{
    jobs *lista = *head;
    opera *lista1;
    maqs *lista2;
    int maquina;
    
    while(lista != NULL)
    {
        lista1 = lista->iniop;
        while(lista1 != NULL)
        {
            lista2 = lista1->ini_maq;
            while(lista2 != NULL)
            {
                maquina = lista2->mach;
                if(verificarMaquinasListamaquinas(head1,maquina) != T)
                {
                    criarMaquinasPUso(head1,maquina);
                }
                lista2 = lista2->prox;
            }
            lista1 = lista1->prox;
        }

        lista = lista->prox;
    }
}
/**
 * @brief Função que printa o escalonamento no terminal
 * 
 * @param head 
 */
void Printsss(maqsUso **head)
{
    maqsUso *lista = *head;
    scale *lista1;


    while(lista != NULL)
    {
        lista1 = lista->inicio;
        printf("Maquina: %d\n", lista->Maquinas);
        while(lista1 != NULL)
        {
            printf("\nInicio: %d\n", lista1->inicio);
            printf("Operacao: %d\n", lista1->opera);
            printf("Job: %d\n", lista1->job);
            printf("Velocidade: %d\n", lista1->tempo);
            lista1 = lista1->prox;
        }
        lista = lista->prox;
    }
}
/**
 * @brief Guardar escalonamento em ficheiro de texto.
 * 
 * @param head 
 */
void guardarFicheiroscale(maqsUso **head)
{
    maqsUso *lista = *head;
    scale *lista1;
    FILE* open;

    open = fopen("Escalonamento.txt", "w");

    while(lista != NULL)
    {
        lista1 = lista->inicio;
        fprintf(open,"M:%d", lista->Maquinas);
        while(lista1 != NULL)
        {
            fprintf(open,"  ||  I:%d", lista1->inicio);
            fprintf(open,"  J:%d", lista1->job);
            fprintf(open,"  O:%d", lista1->opera);
            fprintf(open,"  V:%d", lista1->tempo);
            lista1 = lista1->prox;
        }
        fprintf(open,"\n");
        lista = lista->prox;
    }
    fprintf(open,"\n\nLegenda:\nI->Tempo de Inicio\nJ->Job\nO->Operacao\nV->Tempo da Maquina");
    fclose(open);
    
}
/**
 * @brief Função principal para o escalonamento.
 * 
 * @param head 
 * @param head1 
 */
void escalonamento(jobs **head, maqsUso **head1)
{
    maqsUso *lista = *head1;
    jobs *nova = *head;
    opera *nova1;
    maqs *nova2, *maquinaM;
    int count = 0, a = 0;
    int job,opera,maquina;

        while(nova != NULL)
        {
            nova1 = nova->iniop;
            while(nova1 != NULL)
            {
                nova2 = nova1->ini_maq;
                a = 0;
                while(nova2 != NULL)
                {
                    if(nova2->vmach < a || a == 0)
                    {
                        a = nova2->vmach;
                        job = nova->job;
                        opera = nova1->num_opera;
                        maquina = nova2->mach;
                    }
                    if(nova2->prox == NULL && verificarExistencia(head1,job,opera,maquina) != T)
                    {
                        criarEscalonar(head1,maquina,job,opera,a,count);
                        count = count + a;
                    }
                    nova2 = nova2->prox;
                }
                nova1 = nova1->prox;
            }
            nova = nova->prox;
        }
}
/**
 * @brief Menu principal.
 * 
 * @param head 
 * @param head1 
 */
void menu(jobs **head, maqsUso **head1)
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
        printf("7-Escalonamento. \n");
        printf("8-Guardar no ficheiro.\n");
        printf("9-Sair.\n");
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
                break;
            case 4:
            do{
                printf("\nNumero do job: ");
                scanf("%d", &job);
                if(VerificarJobs(head,job) != T)
                {
                    printf("Job nao existe!");
                }
            }while(VerificarJobs(head,job) != T);
            do{
                printf("Numero de operacao: ");
                scanf("%d", &ope);
                if(VerificarOperacoes(head,job,ope) != T)
                {
                    printf("Operacao nao existe!");
                }
            }while(VerificarOperacoes(head,job,ope) != T);
                eliminarOperacoes(head,job,ope);
                corrigirOperacoes(head,job);
                break;
            case 5:
                system("clear");
                printf("\nJobs existentes:\n");
                PrintaJobs(*head);
                do{
                    printf("\n\nJob a alterar:");
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
                    if(VerificarOperacoes(head,job,ope) != T)
                    {
                        printf("Operacao nao existe, escolher uma presente na lista!\n");
                    }
                }while(VerificarOperacoes(head,job,ope) != T);
                system("clear");
                MenuOperacoes(head,job,ope);
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
                criarMaquinasHelp(head, head1);
                escalonamento(head,head1);
                Printsss(head1);
                guardarFicheiroscale(head1);
                break;
            case 8:
                GuardarFicheiro(head);
                break;
            case 9:
                continue;
        }
    }while(opcao != 9);
}
/**
 * @brief Menu de operações.
 * 
 * @param head 
 * @param job 
 * @param ope 
 */
void MenuOperacoes(jobs **head, int job, int ope)
{
    int opcao, maquina, velo,novamaquina,novavelo;
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
                PrintaOperacoesEscolhida1(head,job,ope);
                do{
                    do{
                    
                        printf("\nInsira maquina: ");
                        scanf("%d", &maquina);
                        if(maquina < 0)
                        {
                            printf("Insira valor maior que 0!!\n");
                        }
                    }while(maquina < 0);
                    
                    if(VerificarMaqs(head,job,ope,maquina) == T)
                    {
                        printf("Maquina já existe!\n");
                    }
                }while(VerificarMaqs(head,job,ope,maquina) == T);
                do{
                    printf("\nInsira velocidade da maquina: ");
                    scanf("%d", &velo);
                    if(velo < 0)
                    {
                        printf("Velocidade tem que ser maior que 0! \n");
                    }
                }while(velo < 0);
                CriarMaquinas(head,ope,job,maquina,velo);
                break;
            case 2:
                PrintaOperacoesEscolhida1(head,job,ope);
                do{
                    do{
                    
                        printf("\nInsira maquina a remover: ");
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
                PrintaOperacoesEscolhida1(head,job,ope);
                do{
                    printf("\nInsira numero de maquina a editar: ");
                    scanf("%d", &maquina);
                    if(VerificarMaqs(head,job,ope,maquina) != T)
                    {
                        printf("Maquina não existe!\n");
                    }
                }while(VerificarMaqs(head,job,ope,maquina) != T);
                do{
                    do{
                    
                        printf("\nInsira novo numero: ");
                        scanf("%d", &novamaquina);
                        if(maquina < 0)
                        {
                            printf("Insira valor maior que 0!!\n");
                        }
                    }while(maquina < 0);
                    
                    if(VerificarMaqs(head,job,ope,novamaquina) == T)
                    {
                        printf("Maquina já existe com esse numero!\n");
                    }
                }while(VerificarMaqs(head,job,ope,novamaquina) == T);

                do{
                    printf("\nInsira velocidade da maquina: ");
                    scanf("%d", &novavelo);
                    if(velo < 0)
                    {
                        printf("Velocidade tem que ser maior que 0! \n");
                    }
                }while(velo < 0);

                alterarMaquinas(head,job,ope,maquina,novamaquina,novavelo);
    
                break;
            case 4:
                continue;
        }
    }while(opcao != 4);
}
