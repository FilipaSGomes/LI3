/**
 * @file Ficheiro com as várias invocações às funções de utilidade
 */

#ifndef UTILS_H
#define UTILS_H

#define MAX_TABLE 2000000


/**
 * \brief Verifica um int numa string
 * @param char*
 * @returns Int
 */
int verify_int(char*);

/**
 * \brief Função relacionada as hashtables
 * @param size_t
 * @returns size_t
 */
size_t hash(const size_t);

int verify_date(char *);

void cls();

char *int_to_str(int );

char *max_len_str(int, char *);

#endif