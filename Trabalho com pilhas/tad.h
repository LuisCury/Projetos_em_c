// Arquivo para as funcoes primitivas do funcionamento da pilha

#include <stdio.h>
#include <stdbool.h>

#define TAM 10

struct pilha_numeros {
  int num [TAM];
  int topo;
};

// Função para verificar se a pilha esta cheia
bool cheia (struct pilha_numeros *p1) {
  if (p1->num[TAM - 1] == 0) {
    return false; 
  }
  else {
    return true;
  }
}

// Função para verificar se a pilha esta vazia
bool vazia (struct pilha_numeros *p1) {
  if (p1->num[0] == 0) {
    return true;
  }
  else {
    return false;
  }
}

// Sub-rotina para empilhar um elemento a pilha
void empilha (struct pilha_numeros *p1, int numero, bool deu_certo) {
  if (cheia(p1) == true) {
    deu_certo = false;
  }
  else {
    p1->topo = p1->topo + 1;
    p1->num[p1->topo] = numero;
    deu_certo = true;
  }
}

// Sub-rotina para desempilhar um elemento a pilha
void desempilha (struct pilha_numeros *p1, int *numero, bool deu_certo) {
  if (vazia(p1) == true) {
    deu_certo = false;
  }
  else {
    *numero = p1->num[p1->topo];
    p1->num[p1->topo] = 0;
    p1->topo = p1->topo - 1;
    deu_certo = true;
  }
}

// Sub-rotina para criar uma pilha
void cria (struct pilha_numeros *p1) {
  for (int i = 0; i < 10; i++) {
    p1->num[i] = 0;
    p1->topo = -1;
  }
}
