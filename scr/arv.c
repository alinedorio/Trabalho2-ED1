#include "../include/arv.h"

struct arv {
  char* info;
  struct arv* esq;
  struct arv* dir;
};

//cria uma arvore vazia
Arv* arv_criavazia(void){
  return NULL;
}

//cria uma arvore com a informacao do no raiz al, e com subarvore esquerda e e subarvore direita d
Arv* arv_cria (char* c, Arv* e, Arv* d){
  Arv* a = (Arv*) malloc (sizeof(Arv));

  a->info = strdup(c);
  a->esq = e;
  a->dir = d;
  return a;
}

//libera o espaco de memoria ocupado pela arvore a
void arv_libera (Arv* a){
  if (!arv_vazia(a)){
    arv_libera(a->esq); /* libera sae */
    arv_libera(a->dir); /* libera sad */
    free(a); /* libera raiz */
  }
}

//retorna true se a arvore estiver vazia e false caso contrario
int arv_vazia (Arv* a){
  if (a == NULL){
    return 1;
  }
  return 0;
}

//imprime as informacoes dos nos da arvore
void arv_imprime (Arv* a){
  printf ("<");

  if (!arv_vazia(a)){
    printf("%s", a->info); /* imprime a raiz */
    arv_imprime (a->esq); /* mostra sae */
    arv_imprime (a->dir); /* mostra sad */
  }

  printf(">");
}

//retorna o campo informacao de um dado no
char* informacao (Arv* a){
    if (!arv_vazia(a)){
    return a->info;
  }

  return 0;
}

//retorna a arvore da esquerda
Arv* retornaArvEsq (Arv* a){
  return a->esq;
}

//retorna a arvore da direita
Arv* retornaArvDir (Arv* a){
  return a->dir;
}
