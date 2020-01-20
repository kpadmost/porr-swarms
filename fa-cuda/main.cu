#include <iostream>
#include <ctime>

#include <stdio.h>
#include <assert.h>
#include <cuda.h>
#include <cuda_runtime.h>

#include "FireflyAlgorithm.h"

#define NUMBER_OF_ITERATIONS 10000

using namespace std;

/*#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, char *file, int line, bool abort=true)
{
   if (code != cudaSuccess)
   {
      fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
      if (abort) exit(code);
   }
}*/

__global__ void add(int *a, int *b, int *c)
{
    printf("done\n");
   *c = *a + *b;
}

int main() {

    std::cout << "Start main" << std::endl;
    int a, b, c; // kopie a, b, c na hoscie
    int *d_a, *d_b, *d_c; // kopie a, b, c na GPU
    int size = sizeof(int);

    // Alokacja pamięci na GPU dla kopii a, b, c
    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_b, size);
    cudaMalloc((void **)&d_c, size);

    // ustawienie wartości początkowych
    a = 5;
    b = 10;

    // Kopiowanie wejść do GPU
    cudaMemcpy(d_a, &a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, &b, size, cudaMemcpyHostToDevice);

    std::cout << c << std::endl;

    // Wykonanie kernela add() na GPU
    add<<<1,1>>>(d_a, d_b, d_c);
    cudaDeviceSynchronize();

    // Kopiowanie rezultatu obliczeń do pamięci hosta
    cudaMemcpy(&c, d_c, size, cudaMemcpyDeviceToHost);

    // Zwalnianie pamięci
    cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);

    std::cout << "End main" << c << std::endl;

    const clock_t begin_time = clock();

    //define parameters
    const int numberOfFireflies = 12;//5;
    const int numberOfDimensions = 20;//3;
    const int dimensionRange = 40;
    const float attractivenessFactor = 1.0f; // attractivityFactor (recommended values: 0.5 - 4)
    const float absorptionFactor = 1e-5; // absorptionFactor (recommended values: 1e-9 - 1e-3)

    FireflyAlgorithm algorithm =  FireflyAlgorithm(numberOfFireflies,numberOfDimensions,
                                                   dimensionRange, attractivenessFactor, absorptionFactor);
    //run task no. 1
    algorithm.RunAlgorithm(NUMBER_OF_ITERATIONS, false, false);

    std::cout << "Task no. 1 execution time: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << std::endl;

    const clock_t begin_time2 = clock();

    //run task no. 2
    algorithm.RunAlgorithm(NUMBER_OF_ITERATIONS, false, true);
    std::cout << "Task no. 2 execution time: " << float( clock () - begin_time2 ) /  CLOCKS_PER_SEC << std::endl;

    return 0;
}