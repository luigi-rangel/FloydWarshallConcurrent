#pragma once

typedef struct
{
    double **weights;
    int size;
} matrix;

matrix loadMatrix(char *filePath);

void fPrintMatrix(matrix adjMatrix, FILE *stream);
void printMatrix(matrix adjMatrix);

void destroyMatrix(matrix adjMatrix);