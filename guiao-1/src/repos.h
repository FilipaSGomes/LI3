/**
 * @file Ficheiro com as várias invocações às funções do tratamento de registos dos Repos
 */
#ifndef REPOS_H
#define REPOS_H

#include "structs.h"
#include "hash.h"

/**
 * \brief Verifica se os parametros do repo são validos
 * @param Repo*
 * @returns Se for válido retorna 1, caso contrário retorna 0
 */
int verify_repos(Repo *);

/**
 * \brief Constroi uma struct Repo a partir de um registo, se este for valido
 * @param Repo*
 * @param char*
 * @param int*
 * @returns 0
 */
int build_repos(Repo *, char *, int *);

/**
 * \brief Insere um repo numa hashtable
 * @param int
 * @param Hash_table*
 */
void insert_repo(int, Hash_table *);

/**
 * \brief Constroi uma struct Repo a partir de um registo, se este for valido
 * @param Repo*
 * @param Hash_table*
 * @param char*
 * @param int*
 * @returns 0
 */
int build_hash_repos(Repo *, Hash_table *, char *, int *);

/**
 * \brief Interpeta o ficheiro retornando as linhas validas na forma de um lista de structs Repo
 * @param int*
 * @param char*
 * @returns Repo*
 */
Repo *parse_repos(int *, char *);

/**
 * \brief Guarda os repos validos num ficheiro .csv
 * @param Repo*
 * @param int
 * @param char*
 * @returns 0
 */
int save_repos(Repo *, int, char *);

/**
 * @brief Da free a todos os repos existentes
 * @param Repo*
 * @param int
 */
void free_repos(Repo *, int );

/**
 * \brief Interpeta o ficheiro retornando as linhas validas na forma de um lista de structs Repo
 * @param Hash_table*
 * @param int*
 * @param char*
 * @returns Repo*
 */
Repo *parse_hash_repos(Hash_table *, int *, char *);

/**
 * \brief Guarda os repos validos num ficheiro .csv
 * @param Repo*
 * @param Hash_table*
 * @param int
 * @param char*
 * @returns 0
 */
int save_hash_repos(Repo *, Hash_table *, int, char *);

#endif