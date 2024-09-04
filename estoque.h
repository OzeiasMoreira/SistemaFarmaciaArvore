#ifndef ESTOQUE_H
#define ESTOQUE_H

#include <stdio.h>

typedef struct {
    char nome[20];
    int codigo;
    float valor;
    int data[3];
}Medicamento;

typedef struct {
    Medicamento *m;
    struct Arvore *esquerda;
    struct Arvore *direita;    
}Arvore;

Medicamento* CriaMedicamento(char *nome,int codigo, float valor, int data[]);

Arvore* CriaArvore();

Arvore * InsereArvoreMedicamento ( Arvore * a , Medicamento * m);

Arvore * RetiraArvoreMedicamento ( Arvore * a , int codigo );

int VerificaArvoreMedicamento ( Arvore * a , int codigo );

int VerificaArvoreValidade ( Arvore * a , int * data );

void ImprimeArvoreMedicamentos ( Arvore * a ,FILE *fp);

#endif