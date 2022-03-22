/**
 * @file Ficheiro com as várias invocações às funções do tratamento de registos dos Users
 */
#ifndef USERS_H
#define USERS_H

#include "structs.h"
#include "hash.h"

/**
 * \brief Verifica se os parametros do user são validos
 * @param User*
 * @returns Se for válido retorna 1, caso contrário retorna 0
 */
int verify_user(User *);

/**
 * \brief Constroi uma lista dos seguidores de um user a partir de um registo, se este for valido
 * @param char*
 * @param User*
 * @returns int
 */
int build_followers(char *, User *);

/**
 * \brief Constroi uma lista dos seguidores que um user segue a partir de um registo, se este for valido
 * @param char*
 * @param User*
 * @returns int
 */
int build_following(char *, User *);

/**
 * \brief Constroi uma struct User a partir de um registo, se este for valido
 * @param User*
 * @param char*
 * @param int*
 * @returns 0
 */
int build_users(User *, char *, int *);

/**
 * \brief Insere um user numa hashtable
 * @param int
 * @param Hash_table*
 */
void insert_user(int, Hash_table *);

/**
 * \brief Interpeta o ficheiro retornando as linhas validas na forma de um lista de structs Users
 * @param int*
 * @param char*
 * @returns User*
 */
User *parse_users(int *, char *);

/**
 * \brief Guarda os users validos num ficheiro .csv
 * @param User*
 * @param int
 * @param char*
 * @returns 0
 */
int save_users(User *, int, char *);

/**
 * @brief Da free a todos os repos existentes
 * @param User*
 * @param int
 */
void free_users(User *, int );

/**
 * \brief Interpeta o ficheiro retornando as linhas validas na forma de um lista de structs User
 * @param Hash_table*
 * @param char*
 * @returns 1
 */
int parse_hash_users(Hash_table *, char *);

#endif