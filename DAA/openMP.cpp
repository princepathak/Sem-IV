#include <iostream>
#include <omp.h>

int main(int argc, char const *argv[])
{
    #pragma omp parallel
    printf("This is thread %d out of %d\n", omp_get_thread_num(), omp_get_num_threads());
    return 0;
}