#include "brute_force.h"
#include "key_generator.h"
#include <stdio.h>
#include <string.h>
#include <omp.h>

void brute_force_search(const char *target, int key_length,
                        unsigned long long start, unsigned long long end,
                        int *found) {
    double start_time_local = omp_get_wtime();

#pragma omp parallel shared(found)
    {
#pragma omp for schedule(dynamic)
        for (unsigned long long i = start; i < end; i++) {
#pragma omp cancellation point for
            if (*found) {
#pragma omp cancel for
            }

            char candidate_buffer[key_length + 1];
            candidate_buffer[key_length] = '\0';

            unsigned long long index = i;
            for (int j = key_length - 1; j >= 0; j--) {
                candidate_buffer[j] = CHARSET[index % CHARSET_SIZE];
                index /= CHARSET_SIZE;
            }

            if (strcmp(candidate_buffer, target) == 0) {
                int local_found = 0;
#pragma omp critical
                {
                    if (!(*found)) {
                        *found = 1;
                        local_found = 1;
                        double t_end = omp_get_wtime();
                        printf("\n==============================================\n");
                        printf("          CLAVE ENCONTRADA!\n");
                        printf("          %s\n", candidate_buffer);
                        printf("          Tiempo de ejecucion: %.4f segundos\n", t_end - start_time_local);
                        printf("==============================================\n");
                    }
                }
                if (local_found) {
#pragma omp cancel for
                }
            }
        }
    }
}
