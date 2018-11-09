#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
typedef struct
{
int codigo;
char nome[50];
} ARTISTA;

typedef struct
{
char exc;   // campo usado para marcar registros excluídos
char titulo[50];
int cod_artista;
char estilo[50];
} MUSICA;

FILE *art,*mus,*play;

void cadastroart()
{
  ARTISTA a;
  art=fopen("artista.dat","ab");
  fseek(art,0,2);
  a.codigo = ftell(art)/sizeof(a)+1;
  puts ("Digite o nome do artista:");
  fflush(stdin);
  gets(a.nome);
  fwrite(&a, sizeof(a), 1, art);
  fclose(art);
}

void listagemart() {
  ARTISTA a;
  if  ((art=fopen("artista.dat", "rb"))==NULL){
      puts ("Erro ao abrir o arquivo!");
      getch();
   }
   else{
   while ((fread(&a, sizeof(a),1,art))==1){
     printf ("%i - %s \n", a.codigo,a.nome);
    }
   getch(); fclose(art);
  }
}

void consultaart()
{
 ARTISTA a;
     char tit[30];
     int existe;
     printf("Informe o nome do artista => ");
     fflush(stdin);
     gets(tit);
     if  ((art=fopen("artista.dat", "rb"))==NULL){
      puts ("Erro ao abrir o arquivo!");
     }
     else{
       existe=0;
    while ((fread(&a, sizeof(a),1,art))==1){
             if (strcmp(tit,a.nome)==0)
             {
               printf ("%i - %s \n", a.codigo,a.nome);
             existe=1;
             break;
         }
       }
       if (!existe)
          printf("\n\n Artista nao cadastrado!!");
       fclose(art);
    }
    getch();
}


void alteraart(){
ARTISTA a;
int cod, achou=0;
int pos;
puts("Digite o codigo do artista para alterar");
scanf("%d", &cod);
art = fopen("artista.dat", "rb+");
while (fread(&a, sizeof(a),1,art)){
if (cod == a.codigo)
    {
    achou = 1;
    break;
}
}
if (achou)
{
  puts ("Digite o novo nome do artista:");
fflush(stdin);
gets(a.nome);
pos = ftell(art);
fseek (art, pos-sizeof(a),SEEK_SET);
fwrite(&a, sizeof(a), 1, art);
fclose(art);
}
else{
printf("\nArtista nao cadastrado!");
    getch();
}
}

int buscArt(int cod){
ARTISTA a;
int achou=0;
art = fopen("artista.dat", "rb");
while (fread(&a, sizeof(a),1,art)){
if (cod == a.codigo)
    {
    achou = 1;
    break;
}
}
if (achou)
{
  printf("%s \n", a.nome);
  getch();
  return 1;
}
else
{
printf("\nArtista nao cadastrado!");
getch();
return 0;
}

}
void cadmus(){
MUSICA m;
int existe=0;
char music[30];
  mus=fopen("musica.dat","ab+");
  puts ("Digite o título da música:");
  fflush(stdin);
  gets(music);
  while ((fread(&m, sizeof(m),1,mus))==1){
             if (strcmp(music,m.titulo)==0)
             {
               printf ("%s \n",m.titulo);
              existe=1;
              break;
        }
    }
    if (!existe){
    strcpy(m.titulo,music);
    puts ("Digite o estilo da música:");
  fflush(stdin);
  gets(m.estilo);
  printf("Digite o codigo do artista: ");
scanf("%d", &m.cod_artista);
  if (buscArt(m.cod_artista)==0)
  printf("\nCadastro nao efetuado");
  else
        fwrite(&m, sizeof(m), 1, mus);
   }
  fclose(mus);
}

void listamusica(){
MUSICA m;
  if  ((mus=fopen("musica.dat", "rb"))==NULL){
      puts ("Erro ao abrir o arquivo!");
      getch();
   }
   else{
   while ((fread(&m, sizeof(m),1,mus))==1){
     printf ("%s \n", m.titulo);
    }
   getch();
   fclose(mus);
  }
}

void menuartista()
{
  char op;
  do
  {
     system("CLS");
     puts ("1 - Cadastro de artistas");
     puts ("2 - Listagem dos artistas");
     puts ("3 - Consulta a um determinado artista");
     puts ("4 - Alterar um determinado artista");
     puts("5 - Voltar");
     op=getchar();
     switch(op)
     {
          case '1': cadastroart();break;
          case '2': listagemart(); break;
          case '3': consultaart(); break;
          case '4': alteraart();
     }
  } while (op!='5');
}
void menumusica()
{
  char op;
  do
  {
     system("CLS");
     puts ("1 - Cadastro de musicas");
     puts ("2 - Listagem das musicas");
     puts ("3 - Consulta a uma determinada musica");
     puts ("4 - Remover uma musica");
     puts("5 - Voltar");
     op=getchar();
     switch(op)
     {
          case '1': cadmus(); break;
          case '2': listamusica(); break;
     }
  } while (op!='5');
}

// Funções para menu artista

main()
{
  setlocale(LC_ALL, "Portuguese");
  char op;
  system("color F0");
  do
  {
     system("CLS");
     puts ("1 - Artistas ");
     puts ("2 - Músicas");
     puts ("3 - Playlist");
     puts ("4 - Sair");
     op=getchar();
     switch(op)
     {
          case '1': menuartista(); break;
          case '2': menumusica(); break;
     }
  } while (op!='4');
}

