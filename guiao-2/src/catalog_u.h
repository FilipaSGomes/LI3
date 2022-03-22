/**
 * @file Ficheiro com as várias invocações às funções relacionadas ao catálogo que contem os registos de users
 */

#ifndef CATALOG_U_H
#define CATALOG_U_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "stats.h"

typedef struct user *User;
typedef struct catalog_u *CatalogU;
typedef struct user_entry *UEntry;

int get_user_t_coms (User);

int get_user_t_fr (User); 

/**
 * \brief Dado um catálogo de user e uma posição(int), vai buscar registos de user ao catálogo
 * @param CatalogU
 * @param int
 * @returns UEntry
 */
UEntry get_user_entry_by_pos (CatalogU, int);

/**
 * \brief Dado um catálogo de users e um indice(int), vai buscar registos de users ao catálogo
 * @param CatalogU
 * @param int
 * @returns UEntry
 */
UEntry get_user_entry (CatalogU ,int );

/**
 * \brief Devolve o proximo registo de um user
 * @param UEntry
 * @returns UEntry
 */
UEntry get_user_next (UEntry );

/**
 * \brief Devolve o id de um registo de um user no catálogo
 * @param UEntry
 * @returns Int
 */
int get_user_entry_id (UEntry );

/**
 * \brief Devolve um registo de um user
 * @param UEntry
 * @returns User
 */
User get_entry_user (UEntry);

/**
 * \brief Dado um catálogo de repos e um id(int), devolve o login do user desse id
 * @param CatalogU
 * @param int
 * @returns Char*
 */
char* check_user_login_by_id(CatalogU, int );

/**
 * \brief Dado um catálogo de users e um id(int), vai buscar um registo de um user ao catálogo
 * @param CatalogU
 * @param int
 * @returns User
 */
User get_user_by_id (int , UEntry);

/**
 * \brief Dado um registo de um user, devolve o id do user
 * @param User
 * @returns Int
 */
int get_user_id (User );

/**
 * \brief Dado um catálogo de users e um indice(int), verifica se os registos de user existem
 * @param CatalogU
 * @param int
 * @returns Int
 */
int check_user_exists(CatalogU, int);

/**
 * \brief Dado um registo de um user, devolve o tipo do user
 * @param User
 * @returns Char *
 */
char *get_user_type (User );

/**
 * \brief Dado um registo de um user, devolve o login do user
 * @param User
 * @returns Char *
 */
char *get_user_login (User );

/**
 * \brief Dado um registo de um user, devolve a lista dos ids de commits que o user efetuou
 * @param User
 * @returns Int
 */
int *get_user_coms (User );

/**
 * \brief Dado um registo de um user, devolve lista dos ids de amigos (seguidores mútuos) do user
 * @param User
 * @returns Int
 */
int *get_user_friends (User );

/**
 * \brief Inicializa um catálogo de users
 * @returns CatalogU
 */
CatalogU cat_u_init();

/**
 * \brief Aplica a funçao Free ao catálogo de users
 * @param CatalogU
 */
void free_catalog_u(CatalogU);

/**
 * \brief Insere um registo de um user num catálogo de registos de users
 * @param int
 * @param char*
 * @param char*
 * @param int*
 * @param int
 * @param CatalogU
 * @param GStats
 */
void insert_user_cat(int, char*, char*,int*,int, CatalogU, GStats);

/**
 * \brief Verifica se um user é do tipo Bot
 * @param int
 * @param CatalogU
 * @returns Int
 */
int check_bot(int , CatalogU);

/**
 * \brief Adiciona o id de um commit ao efetuado por um user a lista de commits desse user
 * @param int
 * @param int
 * @param int
 * @param CatalogU
 */
void add_com_to_user(int , int, int , CatalogU );


#endif