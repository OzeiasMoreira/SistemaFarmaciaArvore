#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estoque.h"

void lerArquivo(FILE *entrada, FILE *saida, Arvore *a) {
    char arquivo[20];
    
    while (fscanf(entrada, "%s", arquivo) != EOF) {

        if (strcmp(arquivo, "MEDICAMENTO") == 0) {
            char nome[20];
            int codigo, data[3];
            float valor;

            fscanf(entrada, "%s %d %f %d %d %d", nome, &codigo, &valor, &data[0], &data[1], &data[2]);

            Medicamento *m = CriaMedicamento(nome, codigo, valor, data);
            
            a = InsereArvoreMedicamento(a, m);

            fprintf(saida, "MEDICAMENTO %s %d ADICIONADO\n", nome, codigo);
        
        } else if (strcmp(arquivo, "RETIRA") == 0) {
            int codigo;
            fscanf(entrada, "%d", &codigo);
            a = RetiraArvoreMedicamento(a, codigo);  
            fprintf(saida, "MEDICAMENTO %d RETIRADO\n", codigo);
        
        } else if (strcmp(arquivo, "IMPRIME_ARVORE") == 0) {
            ImprimeArvoreMedicamentos(a,saida);
        
        } else if (strcmp(arquivo, "ATUALIZA_PRECO") == 0) {
            int codigo;
            float novo;
            fscanf(entrada, "%d %f", &codigo, &novo);
            
            if (VerificaArvoreMedicamento(a, codigo)) {
                Arvore *aux = a;
                while (aux != NULL && aux->m->codigo != codigo) {
                    if (codigo < aux->m->codigo) {
                        aux = aux->esquerda;
                    } else {
                        aux = aux->direita;
                    }
                }
                if (aux != NULL) {
                    aux->m->valor = novo;
                    fprintf(saida, "PRECO ATUALIZADO %s %d %.2f\n", aux->m->nome, codigo, aux->m->valor);
                }
            } else {
                fprintf(saida, "MEDICAMENTO NAO ENCONTRADO NA ARVORE\n");
            }

        
        } else if (strcmp(arquivo, "VERIFICA_VALIDADE") == 0) {
            int data[3];
            fscanf(entrada, "%d %d %d", &data[0], &data[1], &data[2]);
            if (VerificaArvoreValidade(a, data)) {
                fprintf(saida, "MEDICAMENTO VENCIDO ENCONTRADO NA ARVORE\n");
            } else {
                fprintf(saida, "MEDICAMENTO VENCIDO NAO ENCONTRADO NA ARVORE\n");
            }
       
        } else if (strcmp(arquivo, "VERIFICA_ARVORE") == 0) {
            int codigo;
            fscanf(entrada, "%d", &codigo);
            if (VerificaArvoreMedicamento(a, codigo)) {
                fprintf(saida, "MEDICAMENTO %d ENCONTRADO NA ARVORE\n", codigo);
            } else {
                fprintf(saida, "MEDICAMENTO %d NAO ENCONTRADO NA ARVORE\n", codigo);
            }

        } else if (strcmp(arquivo, "FIM") == 0) {
            break;
        }
    }
}

int main() {
    FILE *entrada = fopen("entrada.txt", "r");
    if (!entrada) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    FILE *saida = fopen("saida.txt", "w");
    if (!saida) {
        printf("Erro ao abrir o arquivo de saída.\n");
        fclose(entrada);
        return 1;
    }

    Arvore *arv = CriaArvore(); 

    lerArquivo(entrada, saida, arv);

    fclose(entrada);
    fclose(saida);

    return 0;
}
