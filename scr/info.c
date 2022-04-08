#include "../include/info.h"
#include "../include/arv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//função responsável por juntar todas as informações do trabalho e limpar a main
void inicializaTrab (){
  //abertura do arquivo
    FILE *entrada = fopen("trab2/data/entrada.txt", "r");

  if (entrada == NULL){
    printf("Problemas na abertura do arquivo\n");
    exit(1);
  }

  //criação de um arquivo de saída que será preenchido futuramente com os resultados das expressões numéricas feitas pelas árvores
  FILE *saida = fopen ("trab2/data/saida.txt", "w+");
  FILE *graphviz = fopen ("trab2/data/graphviz.txt", "w+");

  //loop que garante a leitura de todas as linhas do arquivo até o fim dele, além da criação da árvore, do cálculo das expressões numericas e da inclusão de seus resultados no arquivo de saída
  while(1){
    if(feof(entrada)){
      break;
    }
    
    Arv* a = cria_arvore(entrada);
    arv_imprime(a);
    printf("\n\n");

    float num = calcula_arvore(a);

    fprintf(saida, "%.2f\n", num);
    fprintf(graphviz, "strict graph{\n");
    emOrdem(a, graphviz);
    fprintf(graphviz, "\n}\n");
    arv_libera(a);
  }
}

//função que faz o parsing e cria a árvore
Arv* cria_arvore (FILE *arq){
  
  char str[20];
  //a string sempre pegará um caracter do arquivo, que será analisado
  str[0] = fgetc(arq);

  //toda vez que o caracter pegado for '(' ocorre a recursão
  if(str[0] == '('){
    
    //variável que permite que a árvore seja construida recursivamente, garantindo o parsing
    Arv* esq = cria_arvore(arq);
    str[0] = fgetc(arq); 

    //condições para existencia do nó esquerdo
    if(str[0] == '\n' || str[0] == ')' || str[0] == EOF){
      return esq;
    }

    //fgetc usado para descartar os '(' iniciais
    fgetc(arq);

    //variável que permite que a árvore seja construida recursivamente, garantindo o parsing
    Arv* dir = cria_arvore(arq);
    str[1] = '\0';

    //fgets descarta o ')' final
    fgetc(arq);
    return arv_cria(str, esq, dir);

    arv_libera(esq);
    arv_libera(dir);
  }

  //loop utilizado para descartar os '(' localizados antes de numeros
  int i = 1;
  do{
     str[i] = fgetc(arq);
  }
  while(isdigit(str[i++]));

  str[i-1] = '\0';
  return arv_cria(str, arv_criavazia(), arv_criavazia());
}

//função que calcula os resultados das expressões numéricas feitas pelas árvores
float calcula_arvore (Arv* a){
  //cria uma variável associada à informação do nó e observa se ele é número ou operador
  char* c = informacao(a);
  //no caso de número, transforma a variavel char em int, para facilitar o calculo
  if (isdigit(c[0])){
    return atoi(c);
  }
  //no caso de operador, ele calcula recursivamente a operação, utilizando os nos da esquerda e da direita, garantindo que tudo seja calculado corretamente
  else{
    float nesq = calcula_arvore(retornaArvEsq(a));
    float ndir = calcula_arvore(retornaArvDir(a));

    switch(c[0]){
      case '+':
      return nesq + ndir;

      case '-':
      return nesq - ndir;

      case '/':
      return nesq / ndir;

      case '*':
      return nesq * ndir;
    }
      
  }

  return 0;
}

//função responsável por preencher o arquivo "graphviz.txt"
void emOrdem (Arv* a, FILE* fp){
  int i = 0;
 if(a != NULL){
   emOrdem(retornaArvEsq(a), fp);
   fprintf(fp, "no[label = ''%s'']\n", informacao(a));
   fprintf(fp, "no--no\n");
   emOrdem(retornaArvDir(a), fp);
 }
}