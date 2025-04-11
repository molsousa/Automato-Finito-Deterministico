#include <stdio.h>
#include <stdlib.h>
#include "../header.h"
#include "verificar_palavra.h"

// Estrutura para situacao de estados
struct estados{
    int estado_atual;
    int proximo_estado;
    int estado_final;
};

// Funcao para inserir entrada do usuario
// Pre-condicao: ponteiro para char criado
// Pos-condicao: nenhuma
static char* inserir_entrada();

// Funcao para verificar transicao
// Pre-condicao: verifica se uma transicao eh valida
// Pos-condicao: retorna -1 caso nao seja valida
static int verificar_transicao(int estado_atual, char caractere, Automato automato);

// Funcao para liberar tudo que foi alocado no automato
// Pre-condicao: automato criado
// Pos-condicao: libera as especificacoes de dentro da estrutura
static void liberar_automato(Automato automato);

// Funcao para verificar palavra
// Pre-condicao: arquivo carregado
// Pos-condicao: nenhuma
void verificar_palavra(Automato automato)
{
    printf("Insira a entrada: ");
    char *palavra = inserir_entrada();
    struct estados est;
    register int i;
    register int j;

    est.estado_atual = 0;
    printf("[q%d]%s\n", est.estado_atual, palavra);

    i = 0;
    while(palavra[i] != '\0'){
        est.proximo_estado = verificar_transicao(est.estado_atual, palavra[i], automato);

        if(est.proximo_estado == -1){
            printf("REJEITA\n");
            free(palavra);
            return;
        }
        est.estado_atual = est.proximo_estado;
        i++;

        printf("[q%d]%s\n", est.estado_atual, palavra + i);
    }

    // Verificar se o estado atual eh final
    est.estado_final = 0;
    for(j = 0; automato.estados_finais[j] != -1; j++){
        if(automato.estados_finais[j] == est.estado_atual){
            est.estado_final = 1;
            break;
        }
    }
    if(est.estado_final)
        printf("ACEITA\n");
    else
        printf("REJEITA\n");

    free(palavra);
    liberar_automato(automato);
}

// Funcao para inserir entrada do usuario
// Pre-condicao: ponteiro para char criado
// Pos-condicao: nenhuma
static char* inserir_entrada()
{
    char *entrada = NULL;
    int n = 1;
    char c;

    while((c = getchar()) != '\n' && c != EOF){
        entrada = (char*) realloc(entrada, n * sizeof(char));
        if(entrada == NULL){
            printf("Nao foi possivel alocar memoria!\n");
            exit(1);
        }
        entrada[n-1] = c;
        n++;
    }
    entrada = (char*) realloc(entrada, n * sizeof(char));

    if(entrada == NULL){
        printf("Nao foi possivel alocar memoria!\n");
        exit(1);
    }
    entrada[n-1] = '\0';

    return entrada;
}

// Funcao para verificar transicao
// Pre-condicao: verifica se uma transicao eh valida
// Pos-condicao: retorna -1 caso nao seja valida
static int verificar_transicao(int estado_atual, char caractere, Automato automato)
{
    Elem* aux;

    for(aux = *(automato.transicoes); aux != NULL; aux = aux->prox){
        if(aux->info.estado_atual == estado_atual &&
           aux->info.simbolo_lido == caractere)
            return aux->info.proximo_estado;
    }
    return -1; // Transicao nao encontrada
}

// Funcao para liberar tudo que foi alocado no automato
// Pre-condicao: automato criado
// Pos-condicao: libera as especificacoes de dentro da estrutura
static void liberar_automato(Automato automato)
{
    automato.transicoes = liberar_lista(automato.transicoes);
    free(automato.alfabeto);
    free(automato.estados);
    free(automato.estados_finais);
}
