/**
 * @file Ficheiro com as várias invocações às funções relacionadas ao parsing dos ficheiros
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "meta_catalog.h"

/**
 * \brief Interpreta o ficheiro relacionado aos repos, guardando a informação deste num catálogo de repos
 * @param CatalogR
 * @param char*
 * @param GStats
 * @returns Int
 */
int parse_hash_repo(MCatalog, char *);

/**
 * \brief Interpreta o ficheiro relacionado aos users, guardando a informação deste num catálogo de users
 * @param CatalogU
 * @param char*
 * @param GStats
 * @returns Int
 */
int parse_hash_user(MCatalog, char *);

/**
 * \brief Interpreta o ficheiro relacionado aos commits, guardando a informação deste num catálogo de commits
 * @param CatalogC
 * @param CatalogR
 * @param CatalogU
 * @param char*
 * @param GStats
 * @returns Int
 */
int parse_hash_comm(MCatalog , char *);