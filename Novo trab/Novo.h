#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { F, T } bool;

typedef struct Job{
    int job;
    struct Ope* iniop;
    struct Job* prox;
}jobs;

typedef struct Ope{
    int job1;
    int num_opera;
    struct Maq *ini_maq;
    struct Ope *prox;
}opera;

typedef struct Maq{
    int operation;
    int mach;
    int vmach;
    struct Maq* prox;
}maqs;
void menu(jobs **ref);
void CriarJob(jobs **ref, int a);
void PrintaJobs(jobs *ref);
void CriarOpera(jobs **ref, int a);
void CriarOperacoes(jobs **ref, int a, int b);
void PrintaOperacoes(jobs **ref);
void eliminarJob(jobs **ref, int a);

