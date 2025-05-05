#ifndef VERIFICAR_PALAVRA_H_
#define VERIFICAR_PALAVRA_H_

// Funcao para verificar palavra
// Pre-condicao: arquivo carregado
// Pos-condicao: nenhuma
void verificar_palavra(Automato automato);

// Funcao para liberar tudo que foi alocado no automato
// Pre-condicao: automato criado
// Pos-condicao: libera as especificacoes de dentro da estrutura
void liberar_automato(Automato automato);

#endif // VERIFICAR_PALAVRA_H_
