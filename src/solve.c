#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#include "headers/solve.h"  

//argumentos da thread
typedef struct
{
    int ini, end; //inicio e fim do bloco
    double **distances; //matriz de distancias
} targs;

int size;
pthread_barrier_t barrier;

//função de comparação do caminho minimo atual e do caminho mínimo processado
void step(double **distances, int i, int j, int k)
{
    if (distances[i][j] > distances[i][k] + distances[k][j])
        distances[i][j] = distances[i][k] + distances[k][j];
}

//seção do floyd warshall a ser paralelizada
void *computeBlock(void *arg)
{
    int k, i, j;
    targs block = *(targs *)arg; //importando argumentos

    // rodando floyd warshall para o bloco (delimitado po ini e end)
    for (k = 0; k < size; k++)
    {
        for (i = block.ini; i < block.end; i++)
        {
            for (j = 0; j < size; j++)
            {
                step(block.distances, i, j, k);
            }
        }

        pthread_barrier_wait(&barrier); //esperando para que todas as threads sigam juntas para a proxima iteração
    }

    free(arg);

    pthread_exit(NULL);

    return NULL;
}

//algoritmo floyd warshall paralelizado
void floydWarshall(matrix input, int nThreads)
{
    int i, ini, end;

    pthread_t threads[nThreads];
    targs *block;

    size = input.size; //lendo tamanho da entrada

    if (size < nThreads)
    {
        nThreads = size;
    }

    // inicializando a barreira
    if (pthread_barrier_init(&barrier, NULL, nThreads))
    {
        printf("ERRO: falha na criacao da barreira");
        exit(1);
    }

    //criando e disparando threads
    for (i = 0; i < nThreads; i++)
    {
        //dividindo a carga entre as threads
        ini = (i * size) / nThreads;
        end = ((i + 1) * size) / nThreads;

        //alocando espaço para os argumentos da thread
        block = malloc(sizeof(targs));
        if (block == NULL)
        {
            printf("ERRO: malloc -- block %d", i);
            exit(1);
        }

        //inicializando os argumentos da thread
        block->distances = input.weights;
        block->ini = ini;
        block->end = end;

        //disparando threads
        if (pthread_create(&threads[i], NULL, computeBlock, (void *)block))
        {
            printf("ERRO: falha na criacao da thread %d", i);
            exit(1);
        }
    }

    //esperando o termino da execução de todas as threads
    for (i = 0; i < nThreads; i++)
    {
        if (pthread_join(threads[i], NULL))
        {
            printf("ERRO: join da thread %d", i);
            exit(1);
        }
    }
}

//imprissão de solução no terminal
void printSolution(matrix adjMatrix)
{
    int i, j;

    printf("Aqui esta a matriz de solucao do algoritmo de Floyd-Warshall:\n\n");

    for (i = 0; i < adjMatrix.size; i++)
    {
        for (j = 0; j < adjMatrix.size; j++)
        {
            if (adjMatrix.weights[i][j] == DBL_MAX)
                printf("  inf   ");
            else
                printf("%.5lf ", adjMatrix.weights[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}