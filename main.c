#include "forca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

void iniciojogo() { // Abertura do jogo

  printf("\n*** Bem vindo ao jogo da forca ***\n");

  printf("----------------------------------\n\n");
}

void beneficios() { // Ler o arquivo com narrativa/história
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

void opcoes() {
  
  char atividades;

  printf("\n\nVocê quer saber as sugestões dos amigos da Vânia? Digite V para visualizar ou S para sair: ");

  scanf(" %c", &atividades);

  if (atividades == 'V') {

    char opcao[500];

  FILE *arquivo = fopen("Arquivos/opcaoatv.txt", "r");

  char atv;
  int i = 0;
  while ((atv = fgetc(arquivo)) != EOF) {
    opcao[i] = atv;
    i++;
  }

  fclose(arquivo);

  printf(opcao);

  }
  else {

      printf("Poxa, Vânia não terá ninguem para testar seu projeto\n\n");

      exit(0);
    }
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

  printf("\n\nVocê quer adicionar uma palavra, para testar o jogo? (S/N) ");

  scanf(" %c", &quer);

  if (quer == 'S') {

    char novapalavra[TAMANHO_PALAVRA];

    printf("\nDigite a palavra teste: ");

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

    printf("\nPoxa, Vânia terá que pedir para um de seus amigos testarem!\n");

  } else {

    printf("\nSelecione uma opção correta");

    exit(1);
  }
}


void escolheratividade() {

  int opcao;
  
  printf("\n\nTente adivinhar qual opção a professora Vânia escolheu: ");
  scanf("%d", &opcao);

  switch(opcao) {
    case 1:
        printf("\nA professora prefere fazer as atividades com mais dedicação. Por isso escolheu a opção 2 e desenvolveu um jogo.\n\n");
    break;
    case 2:
        printf("\nParabéns! Você acertou. A professora pensou em desenvolver um jogo que os alunos amam.\n\n");
    break;
    case 3:
        printf("\nEla não gostou, pois os alunos ficariam sem suas aulas. Por isso escolheu a opção 2 e desenvolveu um jogo.\n\n");
    break;
  default:
    printf("Opção inválida");
    
  } 

  printf("\nPor favor teste o jogo da professora Vânia e deixe sua avaliação no final.\n\n");
}


void avaliacao(){
  
 int avaliacao;

  printf("\nDeixa uma avaliação de 1 a 10: ");

  scanf("%d", &avaliacao);

  FILE *arquivo;

  arquivo = fopen("Arquivos/avaliacao.txt", "r+");

  fprintf(arquivo, "\n%d", &avaliacao);

  fclose(arquivo);
}

int main() {

  beneficios();

  opcoes();

  escolheratividade();

  iniciojogo();

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
  
  avaliacao();
}
  