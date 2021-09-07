// gcc -O unrolling.cpp -lstdc++
#include <cstdio>
#include <stdint.h>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <time.h>
#define VERIFY
using namespace std;

#define LONG_LENGTH 100000000

static uint32_t getRandom(int low, int high)
{
    return rand() % (high + 1 - low) + low;
}

// array of random numbers
uint32_t *GetRandomArray(uint32_t length)
{
    uint32_t *array = (uint32_t *)malloc(length * sizeof(uint32_t));

    for (int i = 0; i < length; i++)
    {
        array[i] = getRandom(1, length );
    }

    return array;
}

int main(int args, char **argc)
{
    clock_t start, end;
    double cpu_time_used1, cpu_time_used2;

    uint32_t *array1 = GetRandomArray(LONG_LENGTH);
    uint32_t *array2 = GetRandomArray(LONG_LENGTH);
    uint32_t *array3 = (uint32_t *)malloc(LONG_LENGTH * sizeof(uint32_t));
    uint32_t *array4 = (uint32_t *)malloc(LONG_LENGTH * sizeof(uint32_t));
    start = clock();
    for (int i = 0; i < LONG_LENGTH; i++)
    {
        if ((i % 2) == 0)
        {
            array3[i] = array1[i] * array2[i];
        }
        else
        {
            array3[i] = array1[i] + array2[i];
        }
    }

    end = clock();
    cpu_time_used1 = ((double)(end - start)) / CLOCKS_PER_SEC;

    // repeat unrolled
    start = clock();

    int i;
    for (int i = 0; i < LONG_LENGTH - 1; i += 2)
    {
        array4[i] = array1[i] * array2[i];

        array4[i + 1] = array1[i + 1] + array2[i + 1];
    }
    for (; i < LONG_LENGTH; i++)
    {
        if ((i % 2) == 0)
        {
            array4[i] = array1[i] * array2[i];
        }
        else
        {
            array4[i] = array1[i] + array2[i];
        }
    }

    end = clock();
    cpu_time_used2 = ((double)(end - start)) / CLOCKS_PER_SEC;
  
#ifdef VERIFY
    bool bad = false;
    for (int i = 0; i < LONG_LENGTH; i++)
    {
        if (array3[i] != array4[i])
        {
            bad = true;
            break;
        }
    }
    if (bad)
    {
        printf("Error arrays do not match\n");
        assert(false);
    }
#endif
    printf("loop time %f secs unrolled %f secs %f\n",  cpu_time_used2, cpu_time_used1, cpu_time_used1 / cpu_time_used2);
    free(array1);
    free(array2);
    free(array3);
    free(array4);
}