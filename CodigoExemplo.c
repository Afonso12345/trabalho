#include "funcoes.h"

/**
 * @brief Verifica se a maquina inserida já existe
 * 
 * @param ref 
 * @param maquinas 
 * @param operacao 
 * @return true 
 * @return false 
 */
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
/**
 * @brief Verifica se a operação inserida já existe
 * 
 * @param ref 
 * @param operation 
 * @return true 
 * @return false 
 */
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
/**
 * @brief Verifica quantos caracteres o ficheiro "Job.txt" tem 
 * 
 * @return int 
 */
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
/**
 * @brief Liberta os nós referentes à lista que contém a média
 * 
 * @param ref 
 */
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
/**
 * @brief liberta os nós referentes a lista que contém os valores minimos e maximos de unidades de tempo
 * 
 * @param ref 
 */
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
/**
 * @brief Função que passa os valores contido no ficheiro para a memória aquando a inicialização do programa
 * 
 * @param ref 
 */
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
/**
 * @brief Cria um novo ficheiro ".txt" caso já exista um, eliminando o mesmo.
 * 
 * @param ref 
 */
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
/**
 * @brief Cria um ficheiro ".txt" com os valores da lista.
 * 
 * @param ref 
 */
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
/**
 * @brief Função que adiciona os valores da media na lista de medias.
 * 
 * @param ref 
 * @param a 
 * @param b 
 */
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
/**
 * @brief Função que calcula a media e escreve na consola esses mesmos.
 * 
 * @param ref 
 * @param nodes 
 */
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
/**
 * @brief Calculo do valor minimo de unidades de tempo para a realização do job.
 * 
 * @param ref 
 */
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
/**
 * @brief Calculo do valor máximo de unidades de tempo para a realização do job.
 * 
 * @param ref 
 */
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
/**
 * @brief Função para alterar valores já existentes na lista(velocidade das máquinas)
 * 
 * @param eli 
 * @param operacao 
 */
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
/**
 * @brief Função que elimina uma operação inserida pelo utilizador.
 * 
 * @param eli 
 * @param value 
 */
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
/**
 * @brief Função que adiciona uma nova operação.
 * 
 * @param ref 
 * @param a 
 * @param b 
 * @param c 
 */
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
/**
 * @brief Função que escreve na consola todas as operações e as maquinas associadas a cada uma.
 * 
 * @param node 
 */
void printList(lista *node)
{
    printf("\nOperações existentes: \n");
    while (node != NULL)
    {
        printf("Operacao->%d | Maquina->%d | Velocidade->%d\n", node->opera, node->mach, node->vmach);
        node = node->prox;
    }
}