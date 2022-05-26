#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum { F, T } boolean;

typedef struct Job{
    int job;
    struct Ope* iniop;
    struct Job* prox;
}jobs;

typedef struct Ope{
    int num_opera;
    struct Maq *ini_maq;
    struct Ope *prox;
}opera;

typedef struct Maq{
    int mach;
    int vmach;
    struct Maq* prox;
    bool feito;
}maqs;

void menu(jobs **ref);
void CriarJob(jobs **ref, int a);
void PrintaJobs(jobs *ref);
void CriarOperacoes(jobs **ref, int a, int b);
void PrintaOperacoes(jobs **ref);
void eliminarJob(jobs **ref, int a);
void CriarMaquinas(jobs **ref, int a, int b, int maq, int vmaq);
void eliminarOperacoes(jobs **ref, int job, int ope);
void GuardarFicheiro(jobs **ref);
boolean VerificarMaqs(jobs **ref, int job, int ope, int maq);
boolean VerificarJobs(jobs **ref, int job);
boolean VerificarOperações(jobs **ref, int job, int ope);
int verificarCaracteres();
void fileMem(jobs **ref);
int verificarNumero(jobs **ref, int job);
void MenuOperações(jobs **head, int job, int ope);
void removerMaquinas(jobs **ref, int job, int ope, int maq);
void alterarMaquinas(jobs **ref, int job, int ope, int maq, int novamaq, int novavelo);
void PrintaOperacoesEscolhida(jobs **ref,int job);
