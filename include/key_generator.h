#ifndef BRUTEFORCE_KEY_GENERATOR_H
#define BRUTEFORCE_KEY_GENERATOR_H

#define CHARSET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
#define CHARSET_SIZE 62

void generate_dictionary(const char *filename);
unsigned long long calculate_combinations(int key_length); // Ahora recibe key_length como parámetro

#endif // BRUTEFORCE_KEY_GENERATOR_H
