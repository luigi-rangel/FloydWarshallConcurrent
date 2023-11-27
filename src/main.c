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

    // recebendo argumentos da linha de comando
    if (argc < 3)
    {
        printf("ERRO: chamada incorreta ao programa! Formato correto:\n");
        printf("%s <numero de threads> <arquivo de entrada> <arquivo de saida>\n", argv[0]);
        exit(1);
    }

    // atribuindo args à variaveis do programa
    nThreads = atoi(argv[1]);
    inputFilePath = argv[2];
    
    // argumento opcional: arquivo de saída
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

    // lendo a matriz
    adjMatrix = loadMatrix(inputFilePath);

    // calculando matriz de caminhos mínimos
    floydWarshall(adjMatrix, nThreads);

    /* Se for especificado um arquivo de saída, o resultado é escrito nele. 
    Caso contrário, a saída é printada no terminal */
    if (outputFile != NULL)
    {
        fPrintMatrix(adjMatrix, outputFile);
    }
    else
    {
        printSolution(adjMatrix);
    }

    //liberando espaço alocado e fechando arquivo
    destroyMatrix(adjMatrix);
    fclose(outputFile);

    return 0;
}