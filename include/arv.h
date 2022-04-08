#ifndef ARV_H
#define ARV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arv Arv;

//cria uma arvore vazia
Arv* arv_criavazia(void);

//cria uma arvore com a informacao do no raiz al, e com subarvore esquerda e e subarvore direita d
Arv* arv_cria (char* c, Arv* e, Arv* d);

//libera o espaco de memoria ocupado pela arvore a
void arv_libera (Arv* a);

//retorna true se a arvore estiver vazia e false caso contrario
int arv_vazia (Arv* a);

//imprime as informacoes dos nos da arvore
void arv_imprime (Arv* a);

//retorna o campo informacao de um dado no
char* informacao (Arv* a);

//retorna a arvore da esquerda
Arv* retornaArvEsq (Arv* a);

//retorna a arvore da direita
Arv* retornaArvDir (Arv* a);

#endif