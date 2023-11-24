#pragma once

#include "matrix.h"

void floydWarshall(matrix Matrix, int nThreads);
void printSolution(matrix adjMatrix);