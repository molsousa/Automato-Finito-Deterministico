#ifndef HEADER_H_
#define HEADER_H_

// Definicao de tipo para manipulacao de lista
typedef struct lista Elem;
// Definicao de tipo para utilizar lista
typedef struct lista* Lista;

// Estrutura para especificacao de transicao
typedef struct{
    int estado_atual;
    char simbolo_lido;
    int proximo_estado;
}Transicoes;

// Estrutura para lista encadeada
struct lista{
    Transicoes info;
    struct lista* prox;
};

// Estrutura para automato finito deterministico
typedef struct{
    char* alfabeto;
    char* estados;
    int* estados_finais;
    Lista* transicoes;
}Automato;

// Funcao para criar lista
// Pre-condicao: ponteiro criado
// Pos-condicao: nenhuma
Lista* criar_lista();

// Funcao para inserir transicao na lista
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void inserir_transicao(Lista* l, Transicoes x);

// Funcao para liberar lista
// Pre-condicao: lista criada
// Pos-condicao: retorna nulo apos destruir lista
Lista* liberar_lista(Lista* l);

// Funcao para imprimir lista
// Pre-condicao: lista criada
// Pos-condicao: nenhuma
void imprimir_lista(Lista* l);

// Funcao para inverter lista encadeada
// Pre-condicao: duas listas validas
// Pos-condicao: retorna ponteiro para Lista com a lista invertida
Lista* inverter_lista(Lista* l1, Lista* l2);

// Funcao para menu do usuario
// Pre-condicao: nenhuma
// Pos-condicao: nenhuma
void menu();

#endif // HEADER_H_
