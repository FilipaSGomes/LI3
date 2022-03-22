/**
 * @file Ficheiro com as várias invocações às funções relacionadas ao parsing dos ficheiros
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "catalog_c.h"
#include "catalog_r.h"
#include "catalog_u.h"
#include "utils.h"
#include "stats.h"

/**
 * \brief Interpreta o ficheiro relacionado aos repos, guardando a informação deste num catálogo de repos
 * @param CatalogR
 * @param char*
 * @param GStats
 * @returns Int
 */
int parse_hash_repo(CatalogR, char *, GStats);

/**
 * \brief Interpreta o ficheiro relacionado aos users, guardando a informação deste num catálogo de users
 * @param CatalogU
 * @param char*
 * @param GStats
 * @returns Int
 */
int parse_hash_user(CatalogU, char *, GStats);

/**
 * \brief Interpreta o ficheiro relacionado aos commits, guardando a informação deste num catálogo de commits
 * @param CatalogC
 * @param CatalogR
 * @param CatalogU
 * @param char*
 * @param GStats
 * @returns Int
 */
int parse_hash_comm(CatalogC, CatalogR, CatalogU, char *, GStats);