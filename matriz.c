#include <stdio.h>
#include <stdlib.h>

char **alocaMatriz (int lin, int col) {
	char ** mat = malloc (lin * sizeof(char *));
	int i;
	for (i = 0; i < lin; i++)
		mat[i] = malloc (col * sizeof(char));
	return (mat);
}

void liberaMatriz (char ** mat, int lin){
	int i;
	for (i = 0; i < lin; i++)
		free(mat[i]);
	free (mat);
}

void imprimeMatriz (char **a, int m, int n) {
	int i,j;
	for (i = 0; i < m; i++){
		for (j = 0; j < n; j++){
			if (j == n -1)
				printf("%c", a[i][j]);
			else
				printf("%c ", a[i][j]);
		}
		printf("\n");
	}
}

void leMatriz (char **matrizH, char **matrizV, int linhas, int colunas){
	int i, j, aux; 
	for (i = 0; i < linhas; i++)
		for (j = 0; j < colunas; j++){
			scanf("%d", &aux);
			if (aux == 0){
				matrizH[i][j] = '0';
				matrizV[i][j] = '0';
			}
			else{
				matrizH[i][j] = '*';
				matrizV[i][j] = '*';
			}
		}
}

void mesclaMatrizes (char **matrizH, char **matrizV, int linhas, int colunas){
	int i, j;
	for (i = 0; i < linhas; i++)
		for (j = 0; j < colunas; j++)
			if (matrizH[i][j] == '0')
				matrizH[i][j] = matrizV[i][j];
}