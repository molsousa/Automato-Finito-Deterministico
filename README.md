# AUTÔMATO FINITO DETERMINÍSTICO

## Esse algoritmo é capaz de reconhecer uma especificação de um autômato finito determinístico, verificar geração de palavras e gerar gramática regular.

Este repositório contém um algoritmo que simula o funcionamento de um autômato finito determinístico e gera a gramática regular correspondente. O algoritmo foi implementado em linguagem C. A estrutura base do autômato foi feita utilizando registros, enquanto as transições foram feitas utilizando estrutura de lista encadeada.

### O formato da especificação deve ser feito da seguinte forma:

- 1ª linha: alfabeto={a,b,...,z} -> representa o alfabeto possivel de ser lido pelo algoritmo
- 2ª linha: estados={qɑ,qβ,...,qn} -> representa os estados validos
- 3ª linha: finais={qɑ,qɣ,...,qm} -> representa os estados finais validos
- 4ª linha: (qɑ, x) = qβ -> especificação para transicao, onde:
    - qɑ -> estado atual.
    - x -> símbolo lido.
    - qβ -> próximo estado.
      
     ### **Exemplo de especificação:**
      
      alfabeto={a,b,c,0,1,2}
      estados={q0,q1,q2,q3,q4,q5}
      finais={q2,q5}
      (q0,a) = q1
      (q1,a) = q2
      (q1,b) = q1
      (q1,0) = q4
      (q2,c) = q3
      (q3,b) = q2
      (q3,0) = q5
      (q4,0) = q2
      (q4,1) = q5
      (q5,2) = q4
