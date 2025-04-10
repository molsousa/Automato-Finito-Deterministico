#ifndef CARREGAR_ARQUIVO_H_
#define CARREGAR_ARQUIVO_H_

// Funcao para carregar arquivo
// Pre-condicao: ponteiro para Automato criado
// Pos-condicao: nenhuma
void carregar_arquivo(Automato* automato);

// Funcao para imprimir gramatica do automato carregado
// Pre-condicao: arquivo carregado
// Pos-condicao: nenhuma
void imprimir_gramatica(Automato automato);

#endif // CARREGAR_ARQUIVO_H_
