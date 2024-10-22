// Arquivo com as funcoes nao primitivas e o codigo main

#include "tad.h"

// Sub-rotina para imprimir os elemento de uma pilha
void imprimir_valores (struct pilha_numeros p1) {
  for (int i = 0; i < TAM; i++) {
    printf("%d ", p1.num[i]);
  }
}

// Sub-rotina para imprimir o topo de uma pilha
void imprimir_topo (struct pilha_numeros p1) {
  printf("O topo é %d\n", p1.num[p1.topo]);
}

int main (void) {
  
  struct pilha_numeros p1;
  bool funcionou;
  int num_tirado;
  
  
  cria(&p1);

  if (vazia(&p1) == true) {
    printf("A lista está vazia\n");
  }
  else {
    printf("A lista não está vazia\n");
  }

  empilha(&p1, 10, funcionou);
  empilha(&p1, 20, funcionou);
  empilha(&p1, 30, funcionou);
  empilha(&p1, 40, funcionou);
  empilha(&p1, 50, funcionou);
  
  desempilha(&p1, &num_tirado, funcionou);
  
  printf("O numero tirado é o %d\n", num_tirado);
  
  empilha(&p1, 50, funcionou);
  empilha(&p1, 60, funcionou);
  empilha(&p1, 70, funcionou);
  empilha(&p1, 80, funcionou);
  empilha(&p1, 90, funcionou);

  if (cheia(&p1) == true) {
    printf("A lista está cheia\n");
  }
  else {
    printf("A lista não está cheia\n");
  }

  imprimir_valores(p1);

  printf("\n");

  imprimir_topo(p1);

  return 0;
}
