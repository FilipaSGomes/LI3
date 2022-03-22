/**
 * @file Ficheiro com as várias invocações às funções relacionadas ao catálogo que contem os registos de repos
 */

#ifndef CATALOG_R_H
#define CATALOG_R_H

#include "stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "catalog_u.h"

typedef struct repo *Repo;
typedef struct repo_entry *REntry;
typedef struct catalog_r *CatalogR;

/**
 * \brief Dado um catálogo de repos e um indice(int), vai buscar registos de repos ao catálogo
 * @param CatalogR
 * @param int
 * @returns REntry
 */
REntry get_repos_entry(CatalogR, int);

int get_repos_n_coms(Repo);

/**
 * \brief Dado um catálogo de repos e um indice(int), vai buscar um registo de um repo ao catálogo
 * @param CatalogR
 * @param int
 * @returns Repo
 */
Repo get_repos_by_id(CatalogR, int);

/**
 * \brief Dado um catálogo de repos e uma posição(int), vai buscar registos de repos ao catálogo
 * @param CatalogR
 * @param int
 * @returns REntry
 */
REntry get_repos_by_position(CatalogR, int);

/**
 * \brief Dado um catálogo de repos e um indice(int), vai buscar a linguagem de repos ao catálogo
 * @param CatalogR
 * @param int
 * @returns REntry
 */
char* get_lg_by_id(CatalogR, int);

/**
 * \brief Devolve um registo de um repo
 * @param REntry
 * @returns Repo
 */
Repo get_entry_repos(REntry );

/**
 * \brief Devolve o proximo registo de um repo
 * @param REntry
 * @returns REntry
 */
REntry get_repos_next (REntry);

/**
 * \brief Devolve o id de um registo de um repo no catálogo
 * @param REntry
 * @returns Int
 */
int get_repos_entry_id ( REntry);

/**
 * \brief Dado um registo de um repo, devolve o id do repo
 * @param Repo
 * @returns Int
 */
int get_repos_id ( Repo);

/**
 * \brief Dado um registo de um repo, devolve a linguagem do repo
 * @param Repo
 * @returns Char *
 */
char *get_repos_language (Repo );

/**
 * \brief Dado um registo de um repo, devolve a data da ultima atividade
 * @param Repo
 * @returns Int *
 */
int *get_repos_last_activ (Repo  );

/**
 * \brief Dado um registo de um repo, devolve a data do ultimo commit efetuado
 * @param Repo
 * @returns Int *
 */
int *get_repos_last_commit (Repo );

/**
 * \brief Dado um registo de um repo, devolve a descrição do repo
 * @param Repo
 * @returns Char *
 */
char *get_desc_repo (Repo);

/**
 * \brief Dado um registo de um repo, devolve a lista de ids de commits dados
 * @param Repo
 * @returns Int *
 */
int *get_repos_coms (Repo  );

/**
 * \brief Dado um registo de um repo, devolve a lista de ids dos contribuidores
 * @param Repo
 * @returns Int *
 */
int *get_repos_usrs (Repo  );

/**
 * \brief Dado um catálogo de repos e um indice(int), verifica se os registos de repos existem
 * @param CatalogR
 * @param int
 * @returns Int
 */
int check_repo_exists(CatalogR ,int);

/**
 * \brief Dado um registo de um repo, devolve o id do dono
 * @param Repo
 * @returns Int
 */
int get_repos_owner (Repo );

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
void insert_repo_cat(int, int,char*, char*, int*, CatalogR, GStats);

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
int add_contrib(int , int, int , int , CatalogR, GStats , int, int *);

#endif