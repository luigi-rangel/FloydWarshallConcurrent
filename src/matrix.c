#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "headers/matrix.h"

matrix loadMatrix(char *filePath)
{
    int i, j, nNodes;
    double weight;
    FILE *fptr;
    matrix adjMatrix;

    // abrindo arquivo que contem o tamanho e a representação do grafo
    fptr = fopen(filePath, "r");
    if (fptr == NULL)
    {
        printf("ERRO: nao foi possivel abrir arquivo\n");
        exit(1);
    }

    // lendo o tamanho do grafo
    fscanf(fptr, "# %d", &nNodes);

    adjMatrix.size = nNodes;
    adjMatrix.weights = malloc(sizeof(double *) * nNodes);

    for (i = 0; i < nNodes; i++)
    {
        adjMatrix.weights[i] = malloc(sizeof(double) * nNodes);

        for (j = 0; j < nNodes; j++)
        {
            adjMatrix.weights[i][j] = (i == j) ? 0 : DBL_MAX;
        }
    }
    while (fscanf(fptr, "%d %d {'weight': %lf}", &i, &j, &weight) == 3)
    {
        adjMatrix.weights[i][j] = weight;
        adjMatrix.weights[j][i] = weight;
    }

    fclose(fptr);

    return adjMatrix;
}

void fPrintMatrix(matrix adjMatrix, int time, FILE *outputFile)
{
    int i, j;

    fprintf(outputFile, "# %d\n", time);

    for (i = 0; i < adjMatrix.size; i++)
    {
        for (j = 0; j < adjMatrix.size; j++)
        {
            if (adjMatrix.weights[i][j] == DBL_MAX)
                fprintf(outputFile, " inf ");
            else
                fprintf(outputFile, " %.16lf ", adjMatrix.weights[i][j]);
        }
        fprintf(outputFile, "\n");
    }
    fprintf(outputFile, "\n");
}

void destroyMatrix(matrix adjMatrix)
{
    int i;

    for (i = 0; i < adjMatrix.size; i++)
    {
        free(adjMatrix.weights[i]);
    }

    free(adjMatrix.weights);
}