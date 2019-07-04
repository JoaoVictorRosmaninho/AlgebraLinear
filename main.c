#include <stdio.h>
#include "func.h"

void main()
{
	int l, c, i, j, cont;
	float **matBase, **matConcatenada;
	float v_cima, v_baixo, v_esquerda, v_direita;
	puts("Digite os indices da matriz\nExemplo 5 6 ou 5 5 ou 2 3");
	scanf("%d %d", &l, &c);
	matBase = AlocarMatriz(l, c);
	cont = c + 1;
	puts("digite os valores de entrada. Respectivamente\nValor de Cima, baixo, esquerda e direita");
	scanf("%f %f %f %f", &v_cima, &v_baixo, &v_esquerda, &v_direita);
	puts("");
	puts("");
	PreencherBordas(l, c, matBase, v_cima, v_baixo, v_esquerda, v_direita); //Preenche a matriz com os valores passado
	matConcatenada = ConcatenarMatriz(l, c, MontarEquacoes(l, c), matBase);
	for (i = 1; i < (l - 1); i++)
	{
		for(j = 1; j < (c - 1); j++)
		{
			matBase[i][j] = (float)(matConcatenada[cont][l*c] / matConcatenada[cont][cont]); //achando o valor do x;
			cont++;
		}
		cont += 2;
	}
	exportar(l, c, matBase);

}
