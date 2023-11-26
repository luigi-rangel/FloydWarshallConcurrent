#include <stdio.h>
#include <stdlib.h>

#include "headers/matrix.h"
#include "headers/solve.h"

int main(int argc, char *argv[])
{
    int nThreads;
    matrix adjMatrix;
    char *inputFilePath, *outputFilePath;
    FILE *outputFile;

    if (argc < 3)
    {
        printf("ERRO: chamada incorreta ao programa! Formato correto:\n");
        printf("%s <numero de threads> <arquivo de entrada> <arquivo de saida>\n", argv[0]);
        exit(1);
    }
    nThreads = atoi(argv[1]);
    inputFilePath = argv[2];
    if (argc == 4)
    {
        outputFilePath = argv[3];
        outputFile = fopen(outputFilePath, "w");
        if (outputFile == NULL)
        {
            printf("ERRO: falha na criacao do arquivo de saida\n");
            exit(1);
        }
    }
    else
    {
        outputFile = NULL;
    }

    adjMatrix = loadMatrix(inputFilePath);

    floydWarshall(adjMatrix, nThreads);

    if (outputFile != NULL)
    {
        fPrintMatrix(adjMatrix, outputFile);
    }
    else
    {
        printSolution(adjMatrix);
    }

    destroyMatrix(adjMatrix);
    fclose(outputFile);

    return 0;
}