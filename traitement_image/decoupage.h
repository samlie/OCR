#ifndef DECOUPAGE_H
#define DECOUPAGE_H

#include <stdlib.h>
#include <SDL.h>

void printMat(size_t nbrows, size_t nbcols, int mat[nbrows][nbcols]);
void printMatfloat(size_t nbrows, size_t nbcols, float mat[nbrows][nbcols]);
void initialize(size_t nbrows, size_t nbcols, int mat[nbrows][nbcols]);
void initializefloat(size_t nbrows, size_t nbcols, float mat[nbrows][nbcols]);
void boundAndColor(size_t nbrows, size_t nbcols, int mat[nbrows][nbcols], size_t rows, size_t cols, int nb, size_t bounds[4]);
void resize(size_t nbrows, size_t nbcols, int caractere[nbrows][nbcols], size_t n, float res[n][n]);
void matrixdec(size_t nbrows,size_t nbcols, int mat[nbrows][nbcols], size_t bounds[4], int mat2[bounds[1]-bounds[0]+1][bounds[3]-bounds[2]+1], int key);
void isoleTache(size_t nbrows, size_t nbcols, int mat[nbrows][nbcols]);
void save(int n, float minicar[n][n]);
void isoleTacheFromLine(size_t nbrows, size_t nbcols, int mat[nbrows][nbcols], int bounds[4]);
void getLineBlocks(size_t nbrows, size_t nbcols, int mat[nbrows][nbcols], int nboftextrows, int allbounds[nboftextrows][4]);

#endif