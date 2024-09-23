#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include <string.h>


/* FUNÇÕES PILHA */
pilha *criaPilha (int tam){
  pilha *pil = malloc(sizeof(pilha));
  pil->tam = tam;
  pil->topo = 0;
  pil->v = malloc(tam * sizeof(item));
  if (pil->v == NULL)
	return NULL;
  return pil;
}

void destroiPilha (pilha *pil) {
  free (pil->v);
  free (pil);
}

void empilha (pilha *pil, item item){
  if (pil->topo == pil->tam)
	pil = resize (pil);
  pil->v[pil->topo] = item;
  pil->topo ++;
}

item desempilha (pilha *pil) {
  if (!pilhaVazia (pil)){
	pil->topo --;
	return (pil->v[pil->topo]);
  }
  return NULL;
}

int pilhaVazia (pilha *pil) {
  return (pil->topo == 0);
}

item topoDaPilha (pilha *pil) {
  if (!pilhaVazia(pil)){
	return (pil->v[pil->topo - 1]);
  }
  return NULL;
}

pilha *resize (pilha *pil) {
	int i;
	pilha *qil = criaPilha(pil->tam * 2);
	for (i = 0; i < pil->topo; i++)
		qil->v[i] = pil->v[i];
	qil->topo = pil->topo;
	destroiPilha(pil);
	return (qil);
}



/* FUNÇÕES PALAVRA-CRUZADA */

void lePalavras(pal *voc, int npal){
	int i;
	char pal[46];

	for (i = 0; i < npal; i++){
		scanf("%s", pal);
		voc[i].len = strlen(pal);
		strcpy(voc[i].string, pal);
	}
}

void ordenaVoc(pal *voc, int npal){
	int i, j;
	pal chave;
   
	for (i = 1; i < npal; i++) {
    	chave = voc[i];
    	j = i - 1;

    	while (j >= 0 && voc[j].len > chave.len) {
      		voc[j + 1] = voc[j];
      		j = j - 1;
    	}

    	voc[j + 1] = chave;
  	}
}	