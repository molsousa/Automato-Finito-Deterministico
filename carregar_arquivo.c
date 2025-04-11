#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "carregar_arquivo.h"

// Funcao para manipular string
// Pre-condicao: inserir opcao 0, 1 ou 2 para manipular string ou 3 para inteiro
// Pos-condicao: carrega o Automato com informacoes iniciais
static void* manipular_string(char* texto, int op);

// Funcao para carregar arquivo
// Pre-condicao: ponteiro para Automato criado
// Pos-condicao: nenhuma
void carregar_arquivo(Automato* automato)
{
    char entrada[26];
    printf("Insira o arquivo: ");
    scanf("%[^\n]%*c", entrada);

    FILE *arquivo = fopen(entrada, "r");
    char *texto = (char*) malloc(100 * sizeof(char));
    char *aux;
    Lista *l1 = criar_lista();
    Transicoes x;

    if(!arquivo || !texto){
        printf("Erro ao alocar memoria\n");
        exit(1);
    }

    fgets(texto, 100, arquivo); // guardar alfabeto valido
    // printf("%s", texto); // [DEBUG]
    aux = (char*) manipular_string(texto, 0);
    automato->alfabeto = (char*) manipular_string(aux, 1);

    fgets(texto, 100, arquivo); // guardar estados validos
    // printf("%s", texto); // [DEBUG]
    aux = (char*) manipular_string(texto, 0);
    automato->estados = (char*) manipular_string(aux, 2);

    fgets(texto, 100, arquivo); // guardar estados finais
    // printf("%s", texto); // [DEBUG]
    aux = (char*) manipular_string(texto, 0);
    automato->estados_finais = (int*) manipular_string(aux, 3);

    automato->transicoes = criar_lista();
    while(fgets(texto, 100, arquivo) != NULL){
        sscanf(texto, "(q%d,%c) = q%d", &x.estado_atual, &x.simbolo_lido, &x.proximo_estado);
        inserir_transicao(automato->transicoes, x);
    }

    automato->transicoes = inverter_lista(l1, automato->transicoes);
    // imprimir_lista(automato->transicoes); // [DEBUG]

    free(texto);
    texto = NULL;
    aux = NULL;
    fclose(arquivo);
}

// Funcao para imprimir gramatica do automato carregado
// Pre-condicao: arquivo carregado
// Pos-condicao: nenhuma
void imprimir_gramatica(Automato automato)
{
    Elem* aux;
    int estado_atual = -1;
    int producao = 1;
    register int i;
    int flag;

    for(aux = *automato.transicoes; aux != NULL; aux = aux->prox){
        if(estado_atual != aux->info.estado_atual){
            if(!producao)
                printf("\n");

            estado_atual = aux->info.estado_atual;
            printf("%c -> ", estado_atual + 'A');
            producao = 1;
        }
        else if(!producao){
            printf(" | ");
        }

        printf("%c%c", aux->info.simbolo_lido, aux->info.proximo_estado + 'A');
        producao = 0;

        flag = 0;
        for(i = 0; automato.estados_finais[i] != -1; i++){
            if(automato.estados_finais[i] == estado_atual){
                flag = 1;
                break;
            }
        }
        if(flag && (aux->prox == NULL || aux->prox->info.estado_atual != estado_atual)){
            printf(" | @");
        }
    }
    printf("\n");
}

// Funcao para manipular string
// Pre-condicao: inserir opcao 0, 1 ou 2 para manipular string ou 3 para inteiro
// Pos-condicao: carrega o Automato com informacoes iniciais
static void* manipular_string(char* texto, int op)
{
    char* aux;
    int* ptr;
    register int i;

    switch(op){
        // Caso base para guardar infomacoes
        case 0:
            aux = texto;
            while(*aux != '{')
                ++aux;

            aux = strtok(aux, "{");
            aux = strtok(aux, "}");

            // printf("%s\n", aux); // [DEBUG]
            break;

        // Caso 1: coleta alfabeto valido
        case 1:
            aux = (char*) malloc(10 * sizeof(char));
            i = 0;

            while(sscanf(texto, "%c", &aux[i]) != EOF){
                ++texto;
                if(*texto == ',')
                    ++texto;
                ++i;
            }
            aux[i] = 0;

            //printf("%s\n", aux); // [DEBUG]
            break;

        // Caso 2: coleta estados validos
        case 2:
            aux = (char*) malloc(15 * sizeof(char));
            i = 0;
            if(*texto == 'q')
                ++texto;

            while(sscanf(texto, "%c", &aux[i]) != EOF){
                ++texto;
                while(*texto == 'q' || *texto == ',')
                    ++texto;
                ++i;
            }
            aux[i] = 0;

            //printf("%s\n", aux); // [DEBUG]
            break;

        // Caso 3: coleta estados finais
        case 3:
            ptr = (int*) malloc(15 * sizeof(int));
            i = 0;

            if(*texto == 'q')
                ++texto;

            while(sscanf(texto, "%d", &ptr[i]) != EOF){
                ++texto;
                while(*texto == 'q' || *texto == ',')
                    ++texto;
                ++i;
            }
            ptr[i] = -1;

            //for(i = 0; ptr[i] != -1; i++) // [DEBUG]
            //    printf("%d", ptr[i]);

            return ptr;
    }

    return aux;
}
