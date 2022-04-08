#ifndef INFO_H
#define INFO_H

#include "../include/arv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct usada para a variável nós. Ela é responsável por separar os valores do arquivo para facilitar a montagem da árvore.
typedef struct value Value;

//função responsável por juntar todas as informações do trabalho e limpar a main
void inicializaTrab ();

//função que faz o parsing e cria a árvore
Arv* cria_arvore (FILE *arq);

//função que calcula os resultados das expressões numéricas feitas pelas árvores
float calcula_arvore (Arv* a);

//função responsável por preencher o arquivo "graphviz.txt"
void emOrdem (Arv* a, FILE* fp);

#endif