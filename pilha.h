#include <stdio.h>

typedef struct {
	char string[46]; /* Vetor string da palavra*/
	int len; /* Tamanho da palavra*/
	int posvoc; /* Posição da palavra no array 'vocabulario' */
	int posmat[2]; /* Coordenadas (linha, coluna) da primeira letra da palavra */
	int naPilha; /* Assume valores 0 ou 1 */
	int dir; /* Assume valor 0 se palavra está na matriz horizontal ou 1 se na matriz vertical*/
} pal;

typedef pal *item; /* Pilha de ponteiros para as palavras do vocabulario */

typedef struct {
	item *v;
	int topo;
	int tam;
} pilha;

void empilha (pilha *pil, item item);
item desempilha (pilha *pil);
item topoPilha (pilha *pil);
int pilhaVazia (pilha *pil);
pilha *resize (pilha *pil);
pilha *criaPilha (int tam);
void destroiPilha (pilha *pil);

void lePalavras(pal *voc, int npal);
void ordenaVoc(pal *voc, int npal);