# AUTÔMATO FINITO DETERMINÍSTICO

## Esse algoritmo é capaz de reconhecer uma especificação de um autômato finito determinístico e verificar geração de palavras.

### O formato da especificação deve ser feito da seguinte forma:

- 1ª linha: alfabeto={a,b,...,z} -> representa o alfabeto possivel de ser lido pelo algoritmo
- 2ª linha: estados={qɑ,qβ,...,qn} -> representa os estados validos
- 3ª linha: finais={qɑ,qɣ,...,qm} -> representa os estados finais validos
- 4ª linha: (qɑ, x) = qβ -> especificação para transicao, onde:
    - qɑ -> estado atual.
    - x -> símbolo lido.
    - qβ -> próximo estado.
