/**
 * @file Ficheiro com as várias invocações às funções de utilidade
 */

#ifndef UTILS_H
#define UTILS_H

#define MAX_TABLE 2000000

/**
 * \brief Modifica uma string
 * @param char*
 * @returns Char*
 */
char* toLow(char*);


/**
 * \brief Verifica um int numa string
 * @param char*
 * @returns Int
 */
int verify_int(char*);

/**
 * \brief Constroi uma data no formato de inteiros a partir de uma data no formato de sting
 * @param char*
 * @param int*
 */
void build_dt(char *, int *);

/**
 * \brief Compara 2 datas
 * @param int[3]
 * @param int[3]
 * @returns Int
 */
int compare_dates_2 (int [3], int [3]);



/**
 * \brief Função relacionada as hashtables
 * @param size_t
 * @returns size_t
 */
size_t hash(const size_t);

#endif