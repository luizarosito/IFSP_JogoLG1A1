#include "forca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

void abertura() { // Abertura do jogo

  printf("\n*** Bem vindo ao jogo da forca ***\n");

  printf("----------------------------------\n\n");
}

void beneficios() { // Ler o arquivo com narrativa
  char historia[500];

  FILE *arquivo = fopen("Arquivos/historia.txt", "r");

  char his;
  int i = 0;
  while ((his = fgetc(arquivo)) != EOF) {
    historia[i] = his;
    i++;
  }

  fclose(arquivo);

  printf(historia);
}

int letraexiste(char letra) {

  for (int i = 0; i < strlen(palavrasecreta); i++) {

    if (letra == palavrasecreta[i]) {
      return 1;
    }
  }

  return 0;
}

int chuteserrados() {

  int erros = 0;

  for (int i = 0; i < chutesdados; i++) {

    if (!letraexiste(chutes[i])) {
      erros++;
    }
  }

  return erros;
}

int enforcou() { return chuteserrados() >= 5; }

int ganhou() {

  for (int i = 0; i < strlen(palavrasecreta); i++) {

    if (!jachutou(palavrasecreta[i])) {

      return 0;
    }
  }

  return 1;
}

void chuta() {

  char chute;

  printf("Qual letra? ");

  scanf(" %c", &chute);

  if (letraexiste(chute)) {

    printf("\nVocê acertou: a palavra tem a letra %c\n\n", chute);

  } else {

    printf("\nVocê errou: a palavra não tem a letra %c\n\n", chute);
  }

  chutes[chutesdados] = chute;

  chutesdados++;
}

int jachutou(char letra) {

  int achou = 0;

  for (int j = 0; j < chutesdados; j++) {

    if (chutes[j] == letra) {

      achou = 1;

      break;
    }
  }

  return achou;
}

void desenhaforca() {

  int erros = chuteserrados();

  printf(" _______ \n");

  printf(" |/ | \n");

  printf(" | %c%c%c \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '),
         (erros >= 1 ? ')' : ' '));

  printf(" | %c%c%c \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '),
         (erros >= 3 ? '/' : ' '));

  printf(" | %c \n", (erros >= 2 ? '|' : ' '));

  printf(" | %c %c \n", (erros >= 4 ? '/' : ' '), (erros >= 4 ? '\\' : ' '));

  printf(" | \n");

  printf("_|___ \n");

  printf("\n\n");

  for (int i = 0; i < strlen(palavrasecreta); i++) {

    if (jachutou(palavrasecreta[i])) {

      printf("%c ", palavrasecreta[i]);

    } else {

      printf("_ ");
    }
  }

  printf("\n");
}

void escolhepalavra() {

  FILE *f;

  f = fopen("Arquivos/palavras.txt", "r");

  if (f == 0) {

    printf("Banco de dados de palavras não disponível\n\n");

    exit(1);
  }

  int qtddepalavras;

  fscanf(f, "%d", &qtddepalavras);

  srand(time(0));

  int randomico = rand() % qtddepalavras;

  for (int i = 0; i <= randomico; i++) {

    fscanf(f, "%s", palavrasecreta);
  }

  fclose(f);
}

void adicionapalavra() {

  char quer;

  printf("\n\nVocê quer adicionar uma palavra? (S/N) ");

  scanf(" %c", &quer);

  if (quer == 'S') {

    char novapalavra[TAMANHO_PALAVRA];

    printf("\nDigite a nova palavra: ");

    scanf("%s", novapalavra);

    FILE *f;

    f = fopen("Arquivos/palavras.txt", "r+");

    if (f == 0) {

      printf("Banco de dados de palavras não disponível\n\n");

      exit(1);
    }

    int qtd;

    fscanf(f, "%d", &qtd);

    qtd++;

    fseek(f, 0, SEEK_SET);

    fprintf(f, "%d", qtd);

    fseek(f, 0, SEEK_END);

    fprintf(f, "\n%s", novapalavra);

    fclose(f);

  } else if (quer == 'N') {

    printf("\nObrigado por jogar!\n");

  } else {

    printf("\nSelecione uma opção correta");

    exit(0);
  }
}


void 


int main() {

  abertura();

  beneficios();

  adicionapalavra();

  escolhepalavra();

  do {

    desenhaforca();

    chuta();

  } while (!ganhou() && !enforcou());

  if (ganhou()) {

    printf("\nParabéns, você ganhou!\n\n");

  } else {

    printf("\nPuxa, você foi enforcado!\n");

    printf("A palavra era **%s**\n\n", palavrasecreta);
  }

  adicionapalavra();
}