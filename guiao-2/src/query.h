/**
 * @file Ficheiro com as várias invocações às funções relacionadas às queries
 */

#ifndef QUERY_H
#define QUERY_H

#include "utils.h"
#include "stats.h"
#include "catalog_c.h"
#include "catalog_u.h"
#include "catalog_r.h"

/**
 * \brief Escreve um menu com instruções para invocar as várias queries
 */
void menu ();

/**
 * \brief Efetua a query 1, tendo como output o número de utilizadores, bots e organizações
 * @param GStats
 * @returns Char*
 */
char *query_1 (GStats);

/**
 * \brief Efetua a query 2, tendo como output o número médio de colaboradores por repositório
 * @param GStats
 * @returns Char*
 */
char *query_2 (GStats);

/**
 * \brief Efetua a query 3, tendo como output a quantidade de repositórios com bots como colaboradores
 * @param GStats
 * @returns Char*
 */
char *query_3 (GStats);

/**
 * \brief Efetua a query 4, tendo como output a quantidade média de commits por utilizado
 * @param GStats
 * @returns Char*
 */
char *query_4 (GStats);

/**
 * \brief Efetua a query 5, tendo como output o top N(int) de utilizadores mais ativos num determinado intervalo de datas(dois char*)
 * @param CatalogC
 * @param CatalogU
 * @param int
 * @param char*
 * @param char*
 * @returns Char*
 */
char *query_5 (CatalogC , CatalogU , int , char* , char*);

/**
 * \brief Efetua a query 6, tendo como output o top N(int) de utilizadores com mais commits em repositórios de uma determinada linguagem(char*)
 * @param CatalogC
 * @param CatalogU
 * @param CatalogR
 * @param int
 * @param char*
 * @returns Char*
 */
char *query_6 (CatalogC, CatalogU, CatalogR, int , char* );

/**
 * \brief Efetua a query 7, tendo como output os repositórios inativos(sem commits) a partir de uma determinada data(char*)
 * @param CatalogR
 * @param char*
 * @returns Char*
 */
char *query_7 (CatalogR, char*);

/**
 * \brief Efetua a query 8, tendo como output o top N(int) de linguagens mais utilizadas a partir de uma determinada data(char*)
 * @param CatalogC
 * @param CatalogR
 * @param int
 * @param char*
 * @returns Char*
 */
char *query_8 (CatalogC ,CatalogR, int , char* );

/**
 * \brief Efetua a query 9, tendo como output o top N(int) de utilizadores com mais commits em repositórios cujo owner é um amigo(seguidores mútuos) seu
 * @param CatalogU
 * @param CatalogC
 * @param CatalogR
 * @param int
 * @returns Char*
 */
char *query_9 (CatalogU ,CatalogC , CatalogR , int);

/**
 * \brief Efetua a query 10, tendo como output o top N(int) de utilizadores com as maiores mensagens de commit por repositório
 * @param CatalogU
 * @param CatalogC
 * @param int
 * @returns Char*
 */
char *query_10(CatalogU,CatalogC,CatalogR,int,FILE*);

char *query_11(CatalogU, CatalogC, int);

#endif