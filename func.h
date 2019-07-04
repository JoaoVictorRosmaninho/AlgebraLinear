#include "func.c"

int PreencherBordas(int l, int c, float **mat, float v_cima, float v_baixo, float v_esquerda, float v_direita);

float **MontarEquacoes(int l, int c);

float **Gauss(int l, int c, float **matEquacao);

float **AlocarMatriz(int linha, int coluna);

float **ConcatenarMatriz(int l, int c, float **matEquacao, float **mat);

int exportar(int l, int c, float **mat);
