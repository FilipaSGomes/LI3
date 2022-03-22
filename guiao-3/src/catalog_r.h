/**
 * @file Ficheiro com as várias invocações às funções relacionadas ao catálogo que contem os registos de repos
 */

#ifndef CATALOG_R_H
#define CATALOG_R_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

typedef struct repo *Repo;
typedef struct repo_entry *REntry;
typedef struct catalog_r *CatalogR;

/**
 * \brief Dado um catálogo de repos e um indice(int), verifica se os registos de repos existem
 * @param CatalogR
 * @param int
 * @returns Int
 */
int check_repo_exists(CatalogR ,int);

/**
 * \brief Inicializa um catálogo de repos
 * @returns CatalogR
 */
CatalogR cat_r_init();

/**
 * \brief Aplica a funçao Free ao catálogo de repos
 * @param CatalogR
 */
void free_catalog_r(CatalogR);

/**
 * \brief Insere um registo de um repo num catálogo de registos de repos
 * @param int
 * @param int
 * @param char*
 * @param char*
 * @param int*
 * @param CatalogR
 * @param GStats
 */
void insert_repo_cat(int, int,char*, char*, int*, CatalogR);

/**
 * \brief Adiciona contribuidores a um registo de um repo, que se encontra num catalogo de registos de repos 
 * @param int
 * @param int
 * @param int
 * @param int
 * @param CatalogR
 * @param GStats
 * @param int
 * @param int *
 */
int add_contrib(int , int, int , int , CatalogR, int, int *);

int *get_repos_last_activ_by_position(CatalogR,int,int);
int get_repos_id_by_position(CatalogR,int ,int );
char *get_repos_desc_by_position(CatalogR,int,int);
int *get_repos_date_by_position(CatalogR,int,int);
char *get_repos_lng_by_position(CatalogR,int,int);
int *get_repos_date_by_id(CatalogR,int);
char *get_repos_lng_by_id(CatalogR,int);
int get_repo_owner_by_id(CatalogR, int);
int get_repos_n_coms_by_id(CatalogR, int);
int *get_repos_coms_by_id(CatalogR, int);

void check_empty_repos(CatalogR);
int check_n_total_repos(CatalogR);

#endif