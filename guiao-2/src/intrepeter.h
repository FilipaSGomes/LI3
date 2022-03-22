/**
 * @file Ficheiro com as várias invocações às funções relacionadas à interpretação dos ficheiros de entrada
 */

#ifndef INTREPETER_H
#define INTREPETER_H
#include "stats.h"
#include "catalog_c.h"
#include "catalog_u.h"
#include "catalog_r.h"
#include "query.h"

/**
 * \brief Divide uma string de entrada em vários tokens
 * @param char*
 * @param char*
 * @param char*
 * @param char*
 * @returns Char *
 */
char *strmbtok ( char *, char *, char *, char *);

/**
 * \brief Divide uma string, sendo o separador da divisão um determinado carater
 * @param char*
 * @param char*
 * @returns Char **
 */
char** split_at(char* ,char* );

/**
 * \brief Decide qual das queries a tratar, atribuindo-lhes os argumentos necessários
 * @param CatalogU
 * @param CatalogR
 * @param CatalogC
 * @param GStats
 */
void loop (CatalogU, CatalogR, CatalogC, GStats);

/**
 * \brief Conforme as queries pedidas no ficheiro de entrada, interpreta-as, executa-as e devolve o resultado de cada comando no seu proprio ficheiro output
 * @param char*
 * @param CatalogU
 * @param CatalogR
 * @param CatalogC
 * @param GStats
 */
void interpete_query_file(char *, CatalogU, CatalogR, CatalogC, GStats);

#endif