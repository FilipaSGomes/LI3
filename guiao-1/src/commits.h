/**
 * @file Ficheiro com as várias invocações às funções do tratamento de registos dos Commits
 */
#ifndef COMMITS_H
#define COMMITS_H

#include "structs.h"
#include "hash.h"

/**
 * \brief Verifica se os parametros do Commit são validos
 * @param Commit*
 * @returns Se for válido retorna 1, caso contrário retorna 0
 */
int verify_commits(Commit *);

/**
 * \brief Constroi uma struct Commit a partir de um registo, se este for valido
 * @param Commit*
 * @param char*
 * @param int*
 * @returns 0
 */
int build_commits(Commit *, char *, int *);

/**
 * \brief Insere um commit numa hashtable
 * @param int
 * @param Hash_table*
 */
void insert_commit(int, Hash_table *);

/**
 * @brief Da free a todos os commits existentes
 * @param Commit*
 * @param int
 */
void free_commits(Commit *, int );

/**
 * \brief Constroi uma struct Commit a partir de um registo, se este for valido
 * @param Commit*
 * @param Hash_table*
 * @param char*
 * @param int*
 * @returns 0
 */
int build_hash_commits(Commit *, Hash_table *, char *, int *);

/**
 * \brief Interpeta o ficheiro retornando as linhas validas na forma de um lista de structs commits
 * @param Hash_table*
 * @param int*
 * @param char*
 * @returns Commit*
 */
Commit *parse_hash_commits(Hash_table *, int *, char *);

/**
 * \brief Guarda os commits validos num ficheiro .csv
 * @param Commit*
 * @param Hash_table*
 * @param int
 * @param char*
 * @returns 0
 */
int save_hash_commits(Commit *, Hash_table *,int , char *);

/**
 * \brief Interpeta o ficheiro retornando as linhas validas na forma de um lista de structs commits
 * @param int*
 * @param char*
 * @returns Commit
 */
Commit *parse_commits(int *, char *);

/**
 * \brief Guarda os commits validos num ficheiro .csv
 * @param Commit*
 * @param int
 * @param char*
 * @returns 0
 */
int save_commits(Commit *, int, char *);

#endif
