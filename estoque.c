#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

// Função para criar um novo medicamento
Medicamento *CriaMedicamento(char *nome, int codigo, float valor, int data[]) {
    // Aloca memoria para um novo medicamento
    Medicamento *m = (Medicamento *)malloc(sizeof(Medicamento));
    if (m == NULL) {
        printf("Erro: não foi possível alocar memória.\n");
        exit(1);
    }
    // atribuição de variaveis
    strcpy(m->nome, nome);
    m->codigo = codigo;
    m->valor = valor;
    m->data[0] = data[0];
    m->data[1] = data[1];
    m->data[2] = data[2];
    return m;
}

Arvore* CriaArvore(){
    return NULL;
}

Arvore* InsereArvoreMedicamento(Arvore *a, Medicamento *m){
    if (a == NULL)
    {
        a = (Arvore*)malloc(sizeof(Arvore));
        if (a == NULL)
        {
            printf("Erro: não foi possivel alocar memória.\n");
            exit(1);
        }

        a->m = m;
        a->esquerda = NULL;
        a->direita = NULL;
        
    } else if (m->codigo < a->m->codigo){
        a->esquerda = InsereArvoreMedicamento(a->esquerda, m);
    } else {
        a->direita = InsereArvoreMedicamento(a->direita, m);
    }
    
    return a;
}

Arvore* RetiraArvoreMedicamento(Arvore *a,int codigo){
    if (a == NULL)
    {
        printf("Erro: medicamento não encontrado.\n");
        exit(1);
    }

    if (codigo < a->m->codigo)
    {
        a->esquerda = RetiraArvoreMedicamento(a->esquerda,codigo);
    } else if(codigo > a->m->codigo){
        a->direita = RetiraArvoreMedicamento(a->direita, codigo);
    } else {
        if (a->esquerda == NULL && a->direita == NULL) // Nenhum filho
        {
            free(a->m);
            free(a);
            return NULL;
        } else if(a->esquerda == NULL){ // Um filho(direita)
            Arvore *t = a->direita;
            free(a->m);
            free(a);
            return t;
        } else if(a->direita == NULL) { // Um Filho(esquerda)
            Arvore *t = a->esquerda;
            free(a->m);
            free(a);
        } else {
            Arvore *t = a->direita;
            while (t->esquerda != NULL)
            {
                t = t->esquerda;
            }

            Medicamento *temp = a->m;
            a->m = t->m;
            t->m = temp;
            a->direita = RetiraArvoreMedicamento(a->direita, t->m->codigo);
            
        }
        
    }
    
    return a;
}

int VerificaArvoreMedicamento(Arvore *a,int codigo){
    if (a == NULL)
    {
        return 0;
    }

    if (codigo < a->m->codigo)
    {
        return VerificaArvoreMedicamento(a->esquerda, codigo);
    } else if(codigo > a->m->codigo){
        return VerificaArvoreMedicamento(a->direita, codigo);
    } else {
        return 1; // encontrou o medicamento
    }
    
}

int VerificaArvoreValidade(Arvore *a, int data[]){
    if (a == NULL)
    {
        return 0;
    }

    if (a->m->data[2] < data[2] || 
       (a->m->data[2] == data[2] && a->m->data[1] < data[1]) ||
       (a->m->data[2] == data[2] && a->m->data[1] == data[1] && a->m->data[0] < data[0])) {
        return 1;
    }

    return VerificaArvoreValidade(a->esquerda, data) || VerificaArvoreValidade(a->direita, data);
    
}

void ImprimeArvoreMedicamentos(Arvore *a,FILE *fp){
    if (a != NULL)
    {
         ImprimeArvoreMedicamentos(a->esquerda, fp);
        fprintf(fp, "MEDICAMENTO: %s, CODIGO: %d, VALOR: %.2f\n", a->m->nome, a->m->codigo, a->m->valor);
        ImprimeArvoreMedicamentos(a->direita, fp);
    } 
}