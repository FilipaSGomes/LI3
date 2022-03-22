/**@file Ficheiro com as várias invocações às funções do tratamento de hashtables
 */
#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include "structs.h"

/**
 * \brief Inicializa uma hashtable
 * @param Hash_table*
 */
void table_init(Hash_table *);

/**
 * \brief Recebe uma key e devolve a posiçao onde a key se encontra na tabela
 * @param size_t
 * @returns size_t
 */
size_t hash(const size_t  );

/**
 * \brief Trata dos registos de acordo com as varias alineas do ex.2
 * @param Hash_table*
 * @param int*
 * @param int
 * @returns int
 */
int verify_hash(Hash_table *, int, int);

/** @brief Verifica se os repositorios tem commits
 * @param Hash_table*
 * @param int
 * @return int 
 */
int verify_cmt_repo (Hash_table *,int );

/**
 * @brief Liberta o espaço ocupado pela hash table
 * @param Hash_table*
 */
void free_table(Hash_table *);

#endif