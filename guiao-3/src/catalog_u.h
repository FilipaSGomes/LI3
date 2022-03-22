/**
 * @file Ficheiro com as várias invocações às funções relacionadas ao catálogo que contem os registos de users
 */

#ifndef CATALOG_U_H
#define CATALOG_U_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

typedef struct user *User;
typedef struct catalog_u *CatalogU;
typedef struct user_entry *UEntry;


/**
 * \brief Dado um catálogo de repos e um id(int), devolve o login do user desse id
 * @param CatalogU
 * @param int
 * @returns Char*
 */
char* check_user_login_by_id(CatalogU, int );

/**
 * \brief Dado um catálogo de users e um indice(int), verifica se os registos de user existem
 * @param CatalogU
 * @param int
 * @returns Int
 */
int check_user_exists(CatalogU, int);

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
int insert_user_cat(int, char*, char*,int*,int, CatalogU);

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

int get_id_by_pos(CatalogU,int,int);
int get_n_coms_by_pos(CatalogU,int,int);
int* get_user_coms_by_pos(CatalogU,int,int);
int get_user_t_fr_by_id(CatalogU,int);
int get_user_t_coms_by_id(CatalogU,int);
int* get_user_friends_by_id(CatalogU, int);
int* get_user_coms_by_id(CatalogU, int);
int check_n_total_users(CatalogU );

#endif