#include <stdio.h>
#include <omp.h>
#include "brute_force.h"
#include "key_generator.h"

#define NUM_THREADS 250   // Número de hilos
#define KEY_LENGTH 5   // Longitud de la clave (puede cambiar)
#define TARGET_KEY "X053S" // Clave objetivo

int main() {

    unsigned long long total_combinations = calculate_combinations(KEY_LENGTH);

    int found = 0;
    printf("==============================================\n");
    printf("      BUSQUEDA DE CLAVE POR FUERZA BRUTA\n");
    printf("==============================================\n");
    printf("Clave objetivo: %s\n", TARGET_KEY);
    printf("Longitud de clave: %d\n", KEY_LENGTH);
    printf("Total de combinaciones posibles: %llu\n", total_combinations);
    printf("Hilos utilizados: %d\n", NUM_THREADS);

    double start_time = omp_get_wtime();
    omp_set_num_threads(NUM_THREADS);
    brute_force_search(TARGET_KEY, KEY_LENGTH, 0, total_combinations, &found);
    double end_time = omp_get_wtime();

    if (!found) printf("\n[!] Clave no encontrada.\n");
    printf("=======================================\n");
    printf("Tiempo total de ejecucion: %.4f segundos\n", end_time - start_time);
    printf("=======================================\n");
    return 0;
}
