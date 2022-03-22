/**
 * @file Ficheiro com as várias invocações às funções relacionadas ao catálogo que contem os registos de commits
 */

#ifndef CATALOG_C_H
#define CATALOG_C_H

#include "stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

typedef struct commit *Commit;
typedef struct commit_entry *CEntry;
typedef struct catalog_c *CatalogC;

/**
 * \brief Dado um catálogo de commits e um indice(int), vai buscar um registo de um commit ao catálogo
 * @param CatalogC
 * @param int
 * @returns Commit
 */
Commit get_com_by_id(CatalogC, int);

/**
 * \brief Dado um catálogo de commits e um indice(int), vai buscar registos de commits ao catálogo
 * @param CatalogC
 * @param int
 * @returns CEntry
 */
CEntry get_com_entry (CatalogC ,int );

/**
 * \brief Devolve o proximo registo de um commit
 * @param CEntry
 * @returns CEntry
 */
CEntry get_com_next (CEntry );

/**
 * \brief Devolve o id de um registo de um commit no catálogo
 * @param CEntry
 * @returns Int
 */
int get_com_entry_id (CEntry );

/**
 * \brief Devolve um registo de um commit
 * @param CEntry
 * @returns Commit
 */
Commit get_entry_commit(CEntry);

/**
 * \brief Dado um registo de um commit, devolve o id do user que deu o commit
 * @param Commit
 * @returns Int
 */
int get_com_u_id (Commit );

/**
 * \brief Dado um registo de um commit, devolve o id do repo em que o commit foi dado
 * @param Commit
 * @returns Int
 */
int get_com_r_id (Commit );

/**
 * \brief Dado um registo de um commit, devolve a mensagem associada ao commit
 * @param Commit
 * @returns Char *
 */
char *get_com_message (Commit );

/**
 * \brief Dado um registo de um commit, devolve a data em que o commit foi dado
 * @param Commit
 * @returns Char *
 */
int *get_com_date (Commit );

/**
 * \brief Inicializa um catálogo de commits
 * @returns CatalogC
 */
CatalogC cat_c_init();

/**
 * \brief Aplica a funçao Free ao catálogo de commits
 * @param CatalogC
 */
void free_catalog_c(CatalogC);

/**
 * \brief Insere um registo de um commit num catálogo de registos de commit
 * @param int
 * @param int
 * @param int
 * @param int
 * @param char*
 * @param int*
 * @param CatalogC
 * @param GStats
 */
void insert_commit_cat(int, int,int,int,char *, int *, CatalogC, GStats);


#endif

