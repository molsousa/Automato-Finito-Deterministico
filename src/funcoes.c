#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "AFD/carregar_arquivo.h"
#include "AFD/verificar_palavra.h"

// Funcao para inserir elemento na lista
static Elem* inserir_elemento(Elem* l, Transicoes x);
// Funcao para liberar a lista
static void liberar(Elem *l);
// Funcao para inverter a lista
static void inverter(Lista* l, Elem* copia);

// Funcao para criar lista
// Pre-condicao: ponteiro criado
// Pos-condicao: nenhuma
Lista* criar_lista()
{
    Lista* novo;

    novo = (Lista*) malloc(sizeof(Lista));
    if(!novo){
        printf("Nao foi possivel alocar memoria\n");
        exit(1);
    }

    *novo = NULL;

    return novo;
}

// Funcao para inserir transicao na lista
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void inserir_transicao(Lista* l, Transicoes x)
{
    *l = inserir_elemento(*l, x);
}

static Elem* inserir_elemento(Elem* l, Transicoes x)
{
    Elem* aux = (Elem*) malloc(sizeof(Elem));

    aux->info = x;
    aux->prox = l;

    return aux;
}

// Funcao para liberar lista
// Pre-condicao: lista criada
// Pos-condicao: retorna nulo apos destruir lista
Lista* liberar_lista(Lista *l)
{
    liberar(*l);

    return NULL;
}

static void liberar(Elem *l)
{
    Elem* aux = l;

    while(aux != NULL){
        Elem* t = aux;
        aux = aux->prox;
        free(t);
    }
}

// Funcao para imprimir lista
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void imprimir_lista(Lista* l)
{
    Elem* aux;

    for(aux = *l; aux != NULL; aux = aux->prox)
        printf("%d, %c, %d\n", aux->info.estado_atual, aux->info.simbolo_lido, aux->info.proximo_estado);
}

// Funcao para inverter lista encadeada
// Pre-condicao: duas listas validas
// Pos-condicao: retorna ponteiro para Lista com a lista invertida
Lista* inverter_lista(Lista* l1, Lista* l2)
{
    inverter(l1, *l2);

    return l1;
}

static void inverter(Lista* l, Elem* copia)
{
    Elem* aux;

    for(aux = copia; aux != NULL; aux = aux->prox){
        inserir_transicao(l, aux->info);
    }
}

// Funcao para menu do usuario
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void menu()
{
    Automato automato;
    int op;

    do{
        printf("<---AUTOMATO-FINITO-DETERMINISTICO--->\n");
        printf("|\t1 - CARREGAR ARQUIVO         |\n");
        printf("|\t2 - IMPRIMIR GRAMATICA       |\n");
        printf("|\t3 - VERIFICAR PALAVRA        |\n");
        printf("|\t0 - SAIR                     |\n");
        printf("<------------------------------------>\n");
        printf("Escolha uma opcao: ");
        scanf("%d%*c", &op);
        switch(op){
        case 1:
            carregar_arquivo(&automato);
            system("cls");
            break;
        case 2:
            imprimir_gramatica(automato);
            system("pause");
            system("cls");
            break;
        case 3:
            verificar_palavra(automato);
            system("pause");
            system("cls");
            break;
        case 0:
            printf("Obrigado!!\n");
            break;
        default:
            printf("Opcao invalida, tente novamente!!\n");
        }
    }while(op != 0);
}
