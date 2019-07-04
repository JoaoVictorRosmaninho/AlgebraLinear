#include <stdlib.h>
float **Gauss(int l, int c, float **matEquacao);

float **AlocarMatriz(int linha, int coluna)
{
	float **mat;
	int i = 0;
	if ((linha < 1) || (coluna < 1))
	{
		puts("Error no parametro");
		return (NULL);
	}
	mat = (float **)calloc(linha, sizeof(float *));
	if (mat == NULL)
	{
		puts("Memoria insuficiente");
		return (NULL);
	}
	/*Alocar Matriz*/
	for(i; i < linha; i++)
	{
		mat[i] = (float*)calloc(coluna, sizeof(float));
		if (mat[i] == NULL)
		{
			puts("Memoria insuficiente");
			return (NULL);
		}
	}
	return (mat);
}



int PreencherBordas(int l, int c, float **mat, float v_cima, float v_baixo, float v_esquerda, float v_direita)
{
	//*(mat+9) = 5 == mat[1][3]
	int linha, coluna;
  for(linha = 0; linha < l; linha++)
	{
		if (linha == 0)
		{
			 for(coluna = 1; coluna < (c - 1); coluna ++) mat[linha][coluna] = v_cima;
			 mat[linha][0] = (float)(v_cima + v_esquerda)/2;
			 mat[linha][c-1] = (float)(v_cima + v_direita)/2;
	  }
		else if (linha == (l-1))
		{
			for(coluna = 1; coluna < (c - 1	); coluna ++) mat[linha][coluna] = v_baixo;
			mat[linha][0] = (float)(v_baixo + v_esquerda)/2;
			mat[linha][c-1] = (float)(v_baixo + v_direita)/2;
		}
		else
		{
			mat[linha][0] = v_esquerda;
			mat[linha][c-1] = v_direita;
		}

	}
	for (linha = 1; linha < (l-1); linha++)
	{
		for(coluna = 1; coluna < (c-1); coluna++) mat[linha][coluna] = 0.0; //se não zerar os demais é exibido o endereço de memoria
	}
	return 0;
}

	float **MontarEquacoes(int l, int c)
{
  int i_LC = l * c;
	int linha, coluna, cont = 1, aux = 0;
	float *p;
	float **matEquacao = AlocarMatriz(i_LC, i_LC + 1);
	p = matEquacao[0];
  for(int i = 0; i < ((i_LC * (i_LC + 1 ))); i++, p++) *p = 0.0;

	for(linha = 0; linha < i_LC; linha++)
	{
			//primeira ponta da primeira linha
			if (linha < 1)
			{

				matEquacao[linha][0] = -2;
				matEquacao[linha][1] = 1;
				matEquacao[linha][c] = 1;

			}
			//segunda ponta da primeira linha
		  else if (linha == (l - 1))
			{

				matEquacao[linha][linha] = -2;
				matEquacao[linha][linha - 1] = 1;
				matEquacao[linha][linha + c] = 1;
			}
		  //primeira ponta da ultima linha
			else  if (linha == (i_LC - c))
			{
				matEquacao[linha][linha + 1] = 1;
				matEquacao[linha][linha - c] = 1;
				matEquacao[linha][linha] = -2;
			}
			//segunda ponta da ultima linha
			else if (linha == (i_LC - 1))
			{
				matEquacao[linha][linha - 1] = 1;
				matEquacao[linha][linha - c] = 1;
				matEquacao[linha][linha] = -2;

			}
			/*
			 valores que dependem de outro
			 o padrao desse problema sempre vai resultar em indices padroes no caso 4 1 1 1 1
			 0 = -4 * T[i,j] + T[i-1,j] + T[i+1,j] + T[i,j-1] + T[i,j+1]
			*/
			else if((linha >= ((c * cont) + 1)) && (linha < ((c * cont) + c - 1))) //cont controla as fatias da matriz
			{
				matEquacao[linha][linha] = -4;
				matEquacao[linha][linha - 1] = 1;
				matEquacao[linha][linha + 1] = 1;
				matEquacao[linha][linha - c] = 1;
				matEquacao[linha][linha + c] = 1;
				aux++;
				if ((aux == (c - 2)) && (cont < (l - 2))) // preenchendo o miolo da matriz
				{
					aux = 0;
					cont++;
				}
			}
			else
			{
				matEquacao[linha][linha] = 1;
			}
		}
	return (matEquacao);
}

float **Gauss(int l, int c, float **matEquacao) //triangularização da matriz
{
	int linha = 0, coluna = 0, coluna2 = 0;
	int i = 0, j = 0;
  float mult = 0.0;
	for (coluna = 0; coluna < c; coluna++) //triangularização inferior esquerda
	{
		for (linha = coluna + 1; linha < l; linha++)
		{
			if (matEquacao[linha][coluna] == 0) continue;
			mult = (float)(matEquacao[linha][coluna] / matEquacao[coluna][coluna]);		// <----- meu pivo
      for (coluna2 = coluna; coluna2 <= l; coluna2++)
			{
				matEquacao[linha][coluna2] = matEquacao[linha][coluna2] - (matEquacao[coluna][coluna2] * mult);
		  }
		}
	}
	for (coluna = (l - 1); coluna > 0; coluna--)
	{
		for (linha = coluna - 1; linha >= 0; linha--)
		{
			if (matEquacao[linha][coluna] == 0) continue;
			mult = (float)(matEquacao[linha][coluna] / matEquacao[coluna][coluna]);		// <----- meu pivo
			for (coluna2 = (c - 1); coluna2 > 0; coluna2--) //triangularização superior direita
			{
				matEquacao[linha][coluna2] = matEquacao[linha][coluna2] - (matEquacao[coluna][coluna2] * mult);
			}
		}
	}
	return (matEquacao);
}

float **ConcatenarMatriz(int l, int c, float **matEquacao, float **mat)
{
	int i, j, linha = 0, aux = 0;
	int cont = 0;
	for (i = 0; i < l; i++)
	{
		for(j = 0; j < c; j++, cont++)
		{
			if ((cont == 0) || (cont == (c-1)) || (cont == (l*c - 1)) || (cont == (l*c - c)))	continue;
			matEquacao[cont][l*c] = mat[i][j];
		}
	}

	return Gauss(l*c, l*c+1, matEquacao);
}

int exportar(int l, int c, float **mat)
{
	FILE *fp;
	int i, j;
	if (!(fp = fopen("exportacao.txt", "w+")))
	{
			puts("Error ao exportar");
			exit(1);
	}
	for(i = 0; i < l; i++)
	{
		for(j = 0; j < c; j++)
		{
			fprintf(fp, "%.6f ", mat[i][j]);
		}
		putc('\n', fp);
	}
	fclose(fp);
	return 0;
}
