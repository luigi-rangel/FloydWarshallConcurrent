#include <stdio.h>
#include <stdlib.h>

#include <sys/timeb.h>

#include "headers/matrix.h"
#include "headers/solve.h"

int main(int argc, char *argv[])
{
    int nThreads, execTime;
    matrix adjMatrix;
    char *inputFilePath, *outputFilePath;
    FILE *outputFile;
    struct timeb start, end;

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
    ftime(&start);
    floydWarshall(adjMatrix, nThreads);
    ftime(&end);
    execTime = (int) (1000.0 * (end.time - start.time)  + (end.millitm - start.millitm));

    /* Se for especificado um arquivo de saída, o resultado é escrito nele. 
    Caso contrário, a saída é printada no terminal */
    if (outputFile != NULL)
    {
        fPrintMatrix(adjMatrix, execTime, outputFile);
    }
    else
    {
        printSolution(adjMatrix, execTime);
    }

    //liberando espaço alocado e fechando arquivo
    destroyMatrix(adjMatrix);
    fclose(outputFile);

    return 0;
}