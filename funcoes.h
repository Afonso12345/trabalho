#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { F, T } bool;

typedef struct No{
    int opera;
    int mach;
    int vmach;
    struct No* prox;
}lista;

typedef struct Job{
    int job;
    struct No* lista
}jobs;

typedef struct Node{
    int operat;
    float media;
    struct Node* proxx;
}media;

void adicionarMedia(media **ref, int a, float b);
void adicionar(lista** ref, int a, int b, int c);
void fileMem(lista **ref);
void ficheirosLista2(lista **#ref);
void ficheirosLista(lista **ref);
void printList(lista *node);
void eliminar(lista **eli, int value);
void alterar(lista **eli, int operacao);
void calcMax(lista **ref);
void calcMedia(lista **ref, media **nodes);
void calcMin(lista **ref);
void freeNodes(lista **ref);
void freeNodesMedia(media **ref);
int verificarCaracteres();
bool verificarExiste(lista **ref, int operation);
bool verificarExisteMaquina(lista **ref, int maquinas, int operacao);