// Programa para criação do jogo TERMO
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

// Número de palavras existentes do arquivo de palavras
#define NUM_PALAVRAS 324

// Struct usado para armazenar uma palavra e dividi-la em letras
struct palavra {
  char letra[6];
  bool letra_contida[5];
};

// Sub-rotina para escolher a palavra aleatoriamente
void escolher_palavra_aleatoria (struct palavra* resposta) {

  char palavra[NUM_PALAVRAS][6];
  int contador = 0;

  FILE* arquivo = fopen("lista_nomes", "r");

  //Verificação se o arquivo é aberto corretamente
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo!\n");
  }
  else {

      //Conjunto para associar as palavras do arquivo as variaveis
      for (int i = 0; i < NUM_PALAVRAS; i++) {
        fscanf(arquivo, "%s", palavra[contador]);
        contador = contador + 1;
      }

      // Escolha da palavra aleatoriamente
      srand(time(NULL));
      char *palavra_certa = palavra[rand() % contador];

      // Passando a palavra escolhida para a variavel de fora da função
      for (int i = 0; i < 5; i++) {
        resposta->letra[i] = palavra_certa[i];
        resposta->letra_contida[i] = false;
      }

      fclose(arquivo);
  }
}

// Sub-rotina para colher a palavra escolhida pelo jogador
void colhendo_palavra (char letra_escolhida[5]) {
  char entrada[160];

  //Coleta da palavra digitada pelo jogador
  printf("\n");
  printf("Digite seu chute: ");
  fgets(entrada, sizeof entrada, stdin);
  sscanf(entrada, "%c%c%c%c%c", &letra_escolhida[0], &letra_escolhida[1], &letra_escolhida[2], &letra_escolhida[3], &letra_escolhida[4]);
}

// Função para verificar se a letra da palavra está certa
void verificar_letra (struct palavra* letras_certas, char letras_escolhidas[5]) {
  bool letra_escolhida_existe[5] = {false};  //Variavel para controle em alguns "if" e "loops"
  bool posicao_certa[5] = {false};  //Variavel para verificar se a letra está na posição correta, caso seja verdadeira a letra será verde
  bool posicao_errada[5] = {false};   //Variavel para verificar se a letra está na posição errada, caso seja verdadeira a letra será amarela
  bool letra_errada[5] = {false};  //Variavel para verificar que a letra não existe na palavra certa, caso seja verdadeira a letra será vermelha
  bool letra_escolhida_contida[5] = {false};  // Variavel de controle para o caso do usuario chutar letras iguais a mais do que existam na palavra. Palavra certa: "navio", palavra chutada: "casas" (ex. para a letra A; o segundo A deve ser vermelho e não amarelo)
  int contador_letra_certa[5] = {0};  //Contador de cada letra da palavra certa. "arara" terá a posiçao [0] = 3 e [1] = 2
  int contador_para_pintar[5] = {0};  

  //Contador para a quantidade de cada letra na palavra escolhida pelo computador. Como no exemplo anterior, as letras repetidas serão adicionadas no contador já existente para ela
  for (int i = 0; i < 5; i++) {
    if (letras_certas->letra[i] == letras_certas->letra[0]) {    //Primeira letra
        contador_letra_certa[0] = contador_letra_certa[0] + 1;
    }
    else if (letras_certas->letra[i] == letras_certas->letra[1]) {  //Segunda letra
        contador_letra_certa[1] = contador_letra_certa[1] + 1;
    }
    else if (letras_certas->letra[i] == letras_certas->letra[2]) {  //Terceira letra
        contador_letra_certa[2] = contador_letra_certa[2] + 1;
    }
    else if (letras_certas->letra[i] == letras_certas->letra[3]) {  //Quarta letra
        contador_letra_certa[3] = contador_letra_certa[3] + 1;
    }
    else if (letras_certas->letra[i] == letras_certas->letra[4]) {   //Quinta letra
        contador_letra_certa[4] = contador_letra_certa[4] + 1;
    }
  }

  //Verificacao se a letra está presente na palavra ou nao
  //Dois loops, sendo "i" para as letras da palavra chutada pelo jogador e "j" para a palavra certa 
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
        if (letras_escolhidas[i] == letras_certas->letra[j]) {
            letra_escolhida_existe[i] = true;  // Mudando a variavel para verdadeiro caso a letra EXISTA, não mostra nada sobre a posição da letra na palavra
        }
    }
  }

  //Verificacao se a letra sera pintada de verde ou vermelho, ou ira para o caso do amarelo se ela estiver na palavra mas na posicao errada
  for (int i = 0; i < 5; i++) {
    if (letra_escolhida_existe[i]) {  //Se a letra existir na palavra (Situação da cor: verde ou amarelo)
        for (int j = 0; j < 5; j++) {
            if (letras_escolhidas[i] == letras_certas->letra[j] && i == j){
                posicao_certa[i] = true;  // Caso seja verdadeira, será verde
                letra_escolhida_contida[i] = true;  // Variavel par
            }
        }
    }
    else {  // Se a letra não existir na palavra certa (Situação da cor: Vermelho)
        letra_errada[i] = true;
    }
  }

  //Verificacao se as letras existentes na palavra devem ser pintadas de amarelo ou vermelho de acordo com as regras do jogo (Exemplo citado na declaração das variaveis)
  for (int i = 0; i < 5; i++) {  // "i" para as letras da palavra escolhida pelo usuario
    for (int j = 0; j < 5; j++) {  // "j" para as letras da palavra certa
        if (letras_escolhidas[i] == letras_certas->letra[j] && i != j) {  //Se a letra for a mas posição errada
            if (letras_escolhidas[i] == letras_certas->letra[j] && !letra_escolhida_contida[j]) { //Se a letra for a mesma mas ainda não está na posição correta
                for (int k = 0; k < 5; k++) {
                    if (contador_para_pintar[k] < contador_letra_certa[j] && letras_escolhidas[i] == letras_escolhidas[k]) { // Caso em que o número de letras para pintar ainda é menor do que o numero de letras na palavra certa
                        posicao_errada[i] = true;  // Situação da cor: amarela
                        contador_para_pintar[k] = contador_para_pintar[k] + 1;
                    }
                    else {
                        letra_errada[i] = true;  // Situação da cor: vermelho
                    }
                }
            }
            else {
                letra_errada[i] = true;  //Situação da cor: vermelho
            }
        }
    }
  }

  //Pintando as letras no console
  for (int i = 0; i < 5; i++){  // Loop para as 5 letras. Verificar se é verde, depois amarelo, e se não for nenhuma vermelha
    if (posicao_certa[i]){
        //Função para pintar as letras do console, pode não funcionar dependendo do compilador que utiliza, função funciona no codeblocks
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);  //Cor verde para acerto na posicao
        printf("%c ", letras_escolhidas[i]);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);  //Cor padrao do console
    }
    else {
        if (posicao_errada[i]) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);   //Cor amarela para semi acerto
            printf("%c ", letras_escolhidas[i]);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);  //Cor padrao do console
        }
        else {
            if (letra_errada[i]) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);  //Cor vermelha para erro
                printf("%c ", letras_escolhidas[i]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);  //Cor padrao do console
            }
            else {
                printf("%c", letras_escolhidas[i]); //Ultimo printf é para controle caso alguma coisa de errado a letra saira sem cor
            }
        }
    }
  }

}

// Função para verificar se o jogador acertou a palavra
bool verificar_se_ganhou (struct palavra letras_certas, char letras_escolhidas[5]) {
  bool retorno = false;

  // Verificação simples com if se as palavras são as mesmas
  if (letras_escolhidas[0] == letras_certas.letra[0]) {
    if (letras_escolhidas[1] == letras_certas.letra[1]) {
      if (letras_escolhidas[2] == letras_certas.letra[2]) {
        if (letras_escolhidas[3] == letras_certas.letra[3]) {
          if (letras_escolhidas[4] == letras_certas.letra[4]) {
            retorno = true;
          }
        }
      }
    }
  }

  return retorno;
}

int main (void) {

  //Colocando cor padrao nas letras do console
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

  //Regras
  printf("   TERMO\n");
  printf("REGRAS:\n");
  printf("O computador escolhera uma palavra de 5 letras aleatoriamente\n");
  printf("O jogador tera 6 tentativas para acertar essa palavra\n");
  printf("Se o jogador colocar uma letra contida na palavra e na posicao correta, ela ficara VERDE\n");
  printf("Se o jogador colocar uma letra contida na palavra mas na posicao errada, a letra ficara AMARELA\n");
  printf("Se o jogador colocar uma letra que nao esta na palavra, a letra ficara VERMELHA\n");

  // Escolha da palavra pelo computador
  struct palavra resposta;
  escolher_palavra_aleatoria(&resposta);

  int contador_jogadas = 0;
  bool ganhou = false;

  // While padrão de jogos, sendo que ele para quando o jogador ganha ou acaba suas tentativa
  while (contador_jogadas < 6 && !ganhou) {

    //Escolha da palavra pelo jogador
    char letras_escolhidas[5];
    colhendo_palavra(letras_escolhidas);

    //Verificacao do acerto das letras e impressao delas com a cor correspondente
    verificar_letra(&resposta, letras_escolhidas);

    //Verificacao se ganhou o jogo
    ganhou = verificar_se_ganhou(resposta, letras_escolhidas);

    contador_jogadas = contador_jogadas + 1;
  }

  // Impressão do resultado do jogo, para vitorias somente indicando que o jogador saiu vitorioso, e para derrotas tambem indicando a palavra certa
  if (ganhou && contador_jogadas <= 6) {
    printf("\nParabens, voce ganhou");
  }
  else {
    printf("\nNao foi dessa vez :( \n");
    printf("A palavra era: %c%c%c%c%c", resposta.letra[0],resposta.letra[1],resposta.letra[2],resposta.letra[3],resposta.letra[4]);
  }

  // Só para as mensagens padrões do console ficarem longe do jogo em si. Sem função nenhuma no jogo
  printf("\n\n\n");
  
  return  0;
}
