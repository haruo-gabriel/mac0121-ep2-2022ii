#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz.h"
#include "pilha.h"

/* COMO COMPILAR
> gcc -Wall -ansi -pedantic -O2 *.c -o a
> ./a
*/


/* DECLARAÇÃO DOS PROTÓTIPOS */
int cruzada (int direcao, char **matrizH, char **matrizV, int *linAtual, int *colAtual, int linhas, int colunas, int nPal, pal *voc, pal *palAntes, pilha *pilhaPal);
int admitePal (int direcao, char **matrizH, char **matrizV, int linAtual, int colAtual, int linhas, int colunas);
int contaEsp (int direcao, char **matrizH, char **matrizV, int linAtual, int colAtual, int linhas, int colunas);
pal *procuraPal (int direcao, char **matrizH, char **matrizV, int linAtual, int colAtual, int linhas, int colunas, int tamLiv, pal *voc, int nPal, pal *p);
void encaixaPal (int direcao, char **matrizH, char **matrizV, int linAtual, int colAtual, pal *p);
void deletaPalMat (int direcao, char **matrizH, char **matrizV, pal *p);
void saltaInds (int *linAtual, int *colAtual, pal *p);
void incInds (int *linAtual, int *colAtual, int linhas, int colunas);




/* NOTAÇÃO
- char **matrizH: matriz para armazenar as palavras horizontalmente.
- char **matrizV: matriz para armazenar as palavras verticalmente.
*/

/* DECLARAÇÃO DAS FUNÇÕES */
int main(){
    int instancia = 1;

    while(1){
        int m, n, p;
        int i, linAtual, colAtual, haSolucao;
        char **matrizH, **matrizV;
        pal *voc; pal *palAntes;
        pilha *pilhaPal;


        /* INPUT DO USUARIO */
        scanf("%d %d", &m, &n);
        if (m == 0 && n == 0)
            break;
    
        /* Alocacao das matrizes */
        matrizH = alocaMatriz(m, n);
        matrizV = alocaMatriz(m, n);
        leMatriz(matrizH, matrizV, m, n);

        /* Alocacao do voc */
		scanf("%d", &p);
        voc = malloc(p * sizeof(pal));
        lePalavras(voc, p);
        ordenaVoc(voc, p);
		for (i = 0; i < p; i++)
			voc[i].posvoc = i;

        /* Criacao da pilha */
        pilhaPal = criaPilha(p);

        /* SOLUÇÃO */
		linAtual = colAtual = 0;
		palAntes = NULL;
        haSolucao = cruzada(0, matrizH, matrizV, &linAtual, &colAtual, m, n, p, voc, palAntes, pilhaPal);

        /* FINALIZACAO DA INSTÂNCIA */
        printf("Instancia %d\n", instancia);
        if (haSolucao){
			mesclaMatrizes(matrizH, matrizV, m, n);
            imprimeMatriz(matrizH, m, n);
		}
        else
            printf("nao ha solucao\n");
		printf("\n");

        destroiPilha(pilhaPal);
        free(voc);
        liberaMatriz(matrizH, m);
		liberaMatriz(matrizV, m);

		instancia++;
    }

    return 0;
}


/* Verifica se uma palavra-cruzada admite solução.
Itera sobre uma matriz 'linhas'x'colunas' linha à linha e, para cada célula da matriz, checa se a célula admite palavra horizontalmente, e em seguida, verticalmente.
O backtracking ocorre se a célula admite palavra mas não há palavra disponível no 'voc' que encaixe.

NOTAÇÃO:
- int direcao: == 0: horizontal / == 1: vertical
- int nPal: número de palavras
- pal *voc: array das palavras
- pal *palAntes: ponteiro para a palavra desempilhada
*/
int cruzada (int direcao, char **matrizH, char **matrizV, int *linAtual, int *colAtual, int linhas, int colunas, int nPal, pal *voc, pal *palAntes, pilha *pilhaPal){
	int tamLiv, admite; pal *palAtual; item palTopo;

	if (*linAtual == linhas) /* Caso base: se a matriz já foi percorrida até o final, há solução */
		return 1;
	
	admite = admitePal(direcao, matrizH, matrizV, *linAtual, *colAtual, linhas, colunas);

	if (admite == 1){
		/* Conta o espaço livre e procura uma palavra que encaixe */
		tamLiv = contaEsp(direcao, matrizH, matrizV, *linAtual, *colAtual, linhas, colunas);
		palAtual = procuraPal(direcao, matrizH, matrizV, *linAtual, *colAtual, linhas, colunas, tamLiv, voc, nPal, palAntes);

		if (palAtual != NULL){
			empilha(pilhaPal, palAtual);
			encaixaPal(direcao, matrizH, matrizV, *linAtual, *colAtual, palAtual);
			
			if (direcao == 1)
				incInds(linAtual, colAtual, linhas, colunas);
			
			return cruzada((direcao+1)%2, matrizH, matrizV, linAtual, colAtual, linhas, colunas, nPal, voc, NULL, pilhaPal);
		}
		else{ /* Backtracking */
			if (pilhaVazia(pilhaPal))
				return 0;
			else{
				palTopo = desempilha(pilhaPal);
				deletaPalMat(direcao, matrizH, matrizV, palTopo);
				saltaInds(linAtual, colAtual, palTopo);

				/* Inicia 'cruzada' para a célula da palavra desempilhada */
				return cruzada(palTopo->dir, matrizH, matrizV, linAtual, colAtual, linhas, colunas, nPal, voc, palTopo, pilhaPal);
			}
		}
	}
	else if (admite == 0){
		if (direcao == 1)
			incInds(linAtual, colAtual, linhas, colunas);
		return cruzada((direcao+1)%2, matrizH, matrizV, linAtual, colAtual, linhas, colunas, nPal, voc, NULL, pilhaPal);
	}
	else{ /* admite == -1, ou seja, a célula tem um '*' */
		incInds(linAtual, colAtual, linhas, colunas);
		return cruzada(0, matrizH, matrizV, linAtual, colAtual, linhas, colunas, nPal, voc, NULL, pilhaPal);
	}
}


/* Verifica se a célula da matriz admite palavra na vertical ou horizontal.
Admite palavra na horizontal quando:
(a célula não é um '*') E (a célula não está na borda direita) E (a célula à direita não é um '*') E ( (a célula está na borda esquerda) OU (a célula não está na borda esquerda E a célula à esquerda é um '*') )

Ex.: |X| | | |*|X| | | |  ->  nessa linha hipotética, as células em X admitem palavra na horizontal

O raciocínio para vertical é análogo.
*/
int admitePal (int direcao, char **matrizH, char **matrizV, int linAtual, int colAtual, int linhas, int colunas){
	if (matrizH[linAtual][colAtual] == '*')
		return -1;

	if (direcao == 0){ /* Caso horizontal */
		if (colAtual != colunas - 1){
			if (matrizH[linAtual][colAtual+1] != '*'){
				if (colAtual == 0)
					return 1;
				else{
					if (matrizH[linAtual][colAtual-1] == '*')	
						return 1;
					else
						return 0;
				}
			}
			else
				return 0;
		}
		else
			return 0;
	}
	else{ /* Caso vertical */
		if (linAtual != linhas - 1){
			if (matrizV[linAtual+1][colAtual] != '*'){
				if (linAtual == 0)
					return 1;
				else{
					if (matrizV[linAtual-1][colAtual] == '*')	
						return 1;
					else
						return 0;
				}
			}
			else
				return 0;
		}
		else
			return 0;
	}

}


/* Conta o espaço disponível desde a célula atual até um '*' ou até a linha/coluna acabar. */
int contaEsp (int direcao, char **matrizH, char **matrizV, int linAtual, int colAtual, int linhas, int colunas){
    int i, tamanho = 1;

	if (direcao == 0){ /* Caso horizontal */
		for (i = colAtual + 1; i < colunas; i++){
			if (matrizH[linAtual][i] == '*')
				break;
			tamanho++;
		}
	}
	else{ /* Caso vertical */
		for (i = linAtual + 1; i < linhas; i++){
			if (matrizV[i][colAtual] == '*')
				break;
			tamanho++;
		}
	}

	return tamanho;
}


/* Procura uma palavra com um tamanho específico no array 'voc'. */
pal *procuraPal (int direcao, char **matrizH, char **matrizV, int linAtual, int colAtual, int linhas, int colunas, int tamLiv, pal *voc, int nPal, pal *palAntes){
	int j, k, l, encaixa;
	/*
	j: índice para percorrer a matriz
	k: índice para percorrer o vocabulário
	l: índice para percorrer a string da palavra do vocabulário
	*/

	/* Em caso de backtracking, k é inicializado como índice para a palavra seguida da desempilhada. */
	if (palAntes == NULL) k = 0; else k = palAntes->posvoc + 1;

	/* Iteração do 'voc' para achar uma palavra válida */
	for (; k < nPal; k++){
		encaixa = 1;

		if (!voc[k].naPilha && voc[k].len == tamLiv){

			if (direcao == 0){ /* Caso horizontal */
				j = colAtual; l = 0;
				while(j < colAtual + tamLiv && encaixa){
					if (matrizV[linAtual][j] != '0' && voc[k].string[l] != matrizV[linAtual][j]) 
						encaixa = 0;
					l++; j++;
				}
			}
			else{ /* Caso vertical */
				j = linAtual; l = 0;
				while(j < linAtual + tamLiv && encaixa){
					if (matrizH[j][colAtual] != '0' && voc[k].string[l] != matrizH[j][colAtual]) 
						encaixa = 0;
					l++; j++;
				}
			}

			if (encaixa){
				voc[k].naPilha = 1;
				voc[k].dir = direcao;		
				voc[k].posmat[0] = linAtual;
				voc[k].posmat[1] = colAtual;		
				return &voc[k];
			}
		}

		/* Como o array 'voc' está ordenado de forma crescente em relação ao tamanho das palavras, não há necessidade de procurar após 'voc[k].len > tamLiv' */
		else if (voc[k].len > tamLiv)
			return NULL;
	}

	return NULL;
}

/* Insere uma palavra na matriz. */
void encaixaPal (int direcao, char **matrizH, char **matrizV, int linAtual, int colAtual, pal *p){
	int j, k;
	if (direcao == 0){ /* Caso horizontal */
		j = colAtual;
		k = 0;
		while (k < p->len){
			matrizH[linAtual][j] = p->string[k];
			j++; k++;
		}
	}
	else{ /* Caso vertical */
		j = linAtual;
		k = 0;
		while (k < p->len){
			matrizV[j][colAtual] = p->string[k];
			j++; k++;
		}
	}
}

/* Substitui uma palavra escrita na matriz por '0's. */
void deletaPalMat (int direcao, char **matrizH, char **matrizV, pal *p){
	int i;
	p->naPilha = 0;
	if (direcao == 0){ /* Caso horizontal */
		for (i = p->posmat[0]; i < p->posmat[0] + p->len; i++)
			matrizH[i][p->posmat[1]] = '0';
	}
	else{ /* Caso vertical */
		for (i = p->posmat[1]; i < p->posmat[1] + p->len; i++)
			matrizH[p->posmat[0]][i] = '0';
	}
} 


/* Muda os índices linAtual e colAtual, que percorrem a matriz, para a posição da palavra desempilhada no caso de backtracking. */
void saltaInds (int *linAtual, int *colAtual, pal *p){
	*linAtual = p->posmat[0];
	*colAtual = p->posmat[1];
}

/* Muda os índices que percorrem a matriz para a próxima célula. Simula uma iteração linha à linha. */
void incInds (int *linAtual, int *colAtual, int linhas, int colunas){
	*colAtual = (*colAtual + 1) % colunas;

	if (*colAtual == 0)
	 	*linAtual = *linAtual + 1;
}