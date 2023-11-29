#pragma once

typedef struct
{
    double **weights;
    int size;
} matrix;

matrix loadMatrix(char *filePath);

void fPrintMatrix(matrix adjMatrix, int time, FILE *stream);

void destroyMatrix(matrix adjMatrix);