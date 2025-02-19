#include "brute_force.h"
#include "key_generator.h"
#include <stdio.h>
#include <string.h>
#include <omp.h>

void brute_force_search(const char *target, int key_length, unsigned long long start, unsigned long long end, int *found) {
#pragma omp parallel shared(found)
    {
#pragma omp for schedule(dynamic)
        for (unsigned long long i = start; i < end; i++) {
            // Si ya se encontró la clave, se salta la iteración.
#pragma omp flush(found)
            if (*found) continue;

            // Cada iteración crea su propio buffer para la clave candidata.
            char candidate_buffer[key_length + 1];
            candidate_buffer[key_length] = '\0';

            unsigned long long index = i;
            // Convierte el índice a una clave usando el charset.
            for (int j = key_length - 1; j >= 0; j--) {
                candidate_buffer[j] = CHARSET[index % CHARSET_SIZE];
                index /= CHARSET_SIZE;
            }

            // Compara la clave generada con la clave objetivo.
            if (strcmp(candidate_buffer, target) == 0) {
#pragma omp critical
                {
                    if (!(*found)) {
                        *found = 1;
#pragma omp flush(found)
                        printf("\n=======================================\n");
                        printf("          CLAVE ENCONTRADA!\n");
                        printf("          %s\n", candidate_buffer);
                        printf("=======================================\n");
                    }
                }
            }
        }
    }
}
