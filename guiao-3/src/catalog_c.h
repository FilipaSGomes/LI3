/**
 * @file Ficheiro com as várias invocações às funções relacionadas ao catálogo que contem os registos de commits
 */

#ifndef CATALOG_C_H
#define CATALOG_C_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

typedef struct commit *Commit;
typedef struct commit_entry *CEntry;
typedef struct catalog_c *CatalogC;

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
void insert_commit_cat(int, int,int,int,char *, int *, CatalogC);

int *get_com_date_by_id(CatalogC, int);
char *get_com_message_by_id(CatalogC, int);
int get_com_r_by_id(CatalogC,int);
int get_com_u_by_id(CatalogC,int);
int get_com_r_id_by_position(CatalogC, int, int);
int *get_com_date_by_position(CatalogC, int, int);

int check_n_total_commits(CatalogC);

#endif

