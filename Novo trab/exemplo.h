#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { F, T } bool;


typedef struct Job{
    int job;
    struct jobs *prox;
    struct opera *iniop;
}jobs;

typedef struct Opera{
    int opera;
    int maq;
    int vmac;
    struct opera *prox;
}opera