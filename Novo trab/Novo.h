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
    bool feito;
}opera;

typedef struct Maq{
    int mach;
    int vmach;
    struct Maq* prox;
}maqs;

typedef struct MaquinasUso{
    int Maquinas;
    bool inUse;
    struct Escalonar *inicio;
    struct MaquinasUso *prox;
}maqsUso;

typedef struct Escalonar{
    int inicio;
    int job;
    int opera;
    int tempo;
    struct Escalonar * prox;
}scale;


void menu(jobs **ref, maqsUso **ref1);
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
boolean VerificarOperacoes(jobs **ref, int job, int ope);
int verificarCaracteres();
void fileMem(jobs **ref);
int verificarNumero(jobs **ref, int job);
void MenuOperacoes(jobs **head, int job, int ope);
void removerMaquinas(jobs **ref, int job, int ope, int maq);
void alterarMaquinas(jobs **ref, int job, int ope, int maq, int novamaq, int novavelo);
void PrintaOperacoesEscolhida(jobs **ref,int job);
void PercorrerOperacoes(jobs **head, int ope);
void criarMaquinasHelp(jobs **head, maqsUso **head1);
boolean verificarMaquinasListamaquinas(maqsUso **ref, int maq);
void criarMaquinasPUso(maqsUso **ref, int maq);
void criarEscalonar(maqsUso **ref, int maq, int job, int ope, int vtime, int contador);
void guardarFicheiroscale(maqsUso **head);
void escalonamento(jobs **head, maqsUso **head1);
void Printsss(maqsUso **head);
boolean verificarExistencia(maqsUso **ref,int job, int opera, int maq);
