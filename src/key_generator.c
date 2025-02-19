#include "key_generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función para calcular el total de combinaciones posibles según la longitud de clave especificada
unsigned long long calculate_combinations(int key_length) {
    unsigned long long total = 1;
    for (int i = 0; i < key_length; i++) {
        total *= CHARSET_SIZE;
    }
    return total;
}
