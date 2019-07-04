/*
  ATENCAO: Ainda nao tenho a certeza de que este codigo esteja a funcionar correctamente!

  Em principio, pelos pequenos testes que fiz, parece estar a funcionar como esperado, no
  entanto ainda nao esta completamente verificado.

  O input do programa e um ficheiro chamado gauss.in, existente no mesmo directorio (influencia
  dos concursos do ACM :)). Podem por la quantas matrizes quiserem, com o seguinte formato:

    uma linha com o numero de linhas da matriz
    a matriz no formato normal (podem ver o ficheiro que eu criei para terem um ideia)

  Se tiverem alguma duvida, ou precisarem de alguma coisa... azar :)

  DISCLAIMER: This software is provided "AS IS" without any warranty. Se o vosso computador
  pifar, paciencia...

  COPYRIGHT: Alberto Mota    eh eh eh

  Nao sei que mais e que falta aqui, mas nao deve ser nada de importante.. experimentem la o
  codigo, que deu muito trabalhinho e ate parece estar a funcionar.

 */

#include <stdio.h>
#include <math.h>

#define oo 1000000000

FILE *input;
int i, j, k, l, c, size, scene, ntrocas, variavel[1000];
float matriz[1000][1000], matriz_backup[1000][1000], mult, max, aux, res[1000], s;

void lerInput(void){
  for (i = 0; i < size; i++){
    for (j = 0; j <= size; j++){
      fscanf(input, "%f", &matriz[i][j]);
      matriz_backup[i][j] = matriz[i][j];
    }
    variavel[i] = i;
    res[i] = 0;
  }
}

void inicializa(void){
  for (i = 0; i < size; i++){
    for (j = 0; j <= size; j++)
      matriz[i][j] = matriz_backup[i][j];
    variavel[i] = i;
  }
  ntrocas = 0;
  max = -oo;
}

void gauss(void){
  /* aplicar algoritmo de eliminacao de Gauss */
  for (k = 0; k < size-1; k++){
    for (i = k+1; i < size; i++){
      mult = matriz[i][k]/matriz[k][k];
      matriz[i][k] = 0;
      for (j = k+1; j <= size; j++){
	matriz[i][j] -= mult * matriz[k][j];
      }
    }
  }
}

void gaussPivotagemParcial(void){
  /* aplicar algoritmo de eliminacao de Gauss com pivotagem parcial*/
  for (k = 0; k < size-1; k++){
    max = abs(matriz[k][k]);
    l = k;
    /* procurar o maior da coluna onde esta o pivot */
    for (i = k+1; i < size; i++){
      if (abs(matriz[i][k]) > max){
	max = abs(matriz[i][k]);
	l = i;
      }
    }
    /* se o maior nao e o pivot... */
    if (l != k){
      /* troca a linha onde esta o pivot actual pela linha onde esta o novo pivot */
      ntrocas++;
      for (j = k; j <= size; j++){
	aux = matriz[k][j];
	matriz[k][j] = matriz[l][j];
	matriz[l][j] = aux;
      }
    }
    /* algoritmo de Gauss */
    for (i = k+1; i < size; i++){
      mult = matriz[i][k]/matriz[k][k];
      matriz[i][k] = 0;
      for (j = k+1; j <= size; j++){
	matriz[i][j] -= mult * matriz[k][j];
      }
    }
  }
}

void gaussPivotagemTotal(void){
  /* aplicar algoritmo de eliminacao de Gauss com pivotagem total*/
  for (k = 0; k < size-1; k++){
    max = abs(matriz[k][k]);
    l = c = k;
    for (i = k+1; i < size; i++){
      for (j = k+1; j < size; j++){
	if (abs(matriz[i][j]) > max){
	  max = abs(matriz[i][j]);
	  l = i;
	  c = j;
	}
      }
    }
    if (l != k){
      ntrocas++;
      for (j = k; j <= size; j++){
	aux = matriz[k][j];
	matriz[k][j] = matriz[l][j];
	matriz[l][j] = aux;
      }
    }
    if (c != k){
      ntrocas++;
      for (j = 0; j < size; j++){
	aux = matriz[j][k];
	matriz[j][k] = matriz[j][c];
	matriz[j][c] = aux;
	aux = variavel[c];
	variavel[c] = variavel[k];
	variavel[k] = aux;
      }
    }
    for (i = k+1; i < size; i++){
      mult = matriz[i][k]/matriz[k][k];
      matriz[i][k] = 0;
      for (j = k+1; j <= size; j++){
	matriz[i][j] -= mult * matriz[k][j];
      }
    }
  }
}

void determinante(void){
  float det;
  int i;

  det = 1;
  for (i = 0; i < size; i++){
    det *= matriz[i][i];
  }

  if (ntrocas & 1) det = -det;

  printf("Determinante = %f\n", det);
}

void substituicao(void){
  res[size-1] = matriz[size-1][size] / matriz[size-1][size-1];
  for (i = size-2; i >= 0; i--){
    s = 0;
    for (j = i+1; j < size; j++){
      s += matriz[i][j] * res[j];
    }
    res[i] = (matriz[i][size] - s)/ matriz[i][i];
  }

  for (i = 0; i < size; i++){
    printf("\t%c = %f\n", variavel[i]+'A', res[i]);
  }

}

void imprimeMatriz(void){
  for (i = 0; i < size; i++){
    for (j = 0; j <= size; j++){
      printf("%12f\t", matriz[i][j]);
    }
    printf("\n");
  }
}

int main(void){

  input = fopen("gauss.in", "r");
  scene = 1;

  /* ler input */
  while (fscanf(input, "%d", &size) == 1){
    printf("------------ Matriz %3d -------------------------------------------\n\n", scene++);
    lerInput();

    inicializa();

    gauss();
    printf("Matriz obtida com eliminacao de Gauss\n");
    imprimeMatriz();
    determinante();
    printf("Resultados finais:\n");
    substituicao();
    printf("\n");

    inicializa();

    gaussPivotagemParcial();
    printf("Matriz obtida com eliminacao de Gauss utilizando pivotagem parcial\n");
    imprimeMatriz();
    determinante();
    printf("Resultados finais:\n");
    substituicao();
    printf("\n");

    inicializa();

    gaussPivotagemTotal();
    printf("Matriz obtida com eliminacao de Gauss utilizando pivotagem total\n");
    imprimeMatriz();
    determinante();
    printf("Resultados finais:\n");
    substituicao();
    printf("\n");

    printf("-------------------------------------------------------------------\n");
  }

  return(1);

}
