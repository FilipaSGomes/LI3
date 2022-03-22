/**
 * @file Ficheiro com as várias invocações às funções relacionadas às queries
 */

#ifndef QUERY_H
#define QUERY_H

#include "utils.h"
#include "meta_catalog.h"
#include "pagination.h"

/**
 * \brief Escreve um menu com instruções para invocar as várias queries
 */
void menu ();

void help();

/**
 * \brief Efetua a query 1, tendo como output o número de utilizadores, bots e organizações
 * @param GStats
 * @returns Char*
 */
void query_1(MCatalog, FILE *);

/**
 * \brief Efetua a query 2, tendo como output o número médio de colaboradores por repositório
 * @param GStats
 * @returns Char*
 */
void query_2(MCatalog, FILE *);

/**
 * \brief Efetua a query 3, tendo como output a quantidade de repositórios com bots como colaboradores
 * @param GStats
 * @returns Char*
 */
void query_3(MCatalog, FILE *);

/**
 * \brief Efetua a query 4, tendo como output a quantidade média de commits por utilizado
 * @param GStats
 * @returns Char*
 */
void query_4(MCatalog, FILE *);

/**
 * \brief Efetua a query 5, tendo como output o top N(int) de utilizadores mais ativos num determinado intervalo de datas(dois char*)
 * @param CatalogC
 * @param CatalogU
 * @param int
 * @param char*
 * @param char*
 * @returns Char*
 */
void query_5(MCatalog, int, char *, char *, FILE *);

/**
 * \brief Efetua a query 6, tendo como output o top N(int) de utilizadores com mais commits em repositórios de uma determinada linguagem(char*)
 * @param CatalogC
 * @param CatalogU
 * @param CatalogR
 * @param int
 * @param char*
 * @returns Char*
 */
void query_6(MCatalog, int, char *, FILE *);

/**
 * \brief Efetua a query 7, tendo como output os repositórios inativos(sem commits) a partir de uma determinada data(char*)
 * @param CatalogR
 * @param char*
 * @returns Char*
 */
void query_7(MCatalog, char *, FILE *);

/**
 * \brief Efetua a query 8, tendo como output o top N(int) de linguagens mais utilizadas a partir de uma determinada data(char*)
 * @param CatalogC
 * @param CatalogR
 * @param int
 * @param char*
 * @returns Char*
 */
void query_8(MCatalog, int, char *, FILE *);

/**
 * \brief Efetua a query 9, tendo como output o top N(int) de utilizadores com mais commits em repositórios cujo owner é um amigo(seguidores mútuos) seu
 * @param CatalogU
 * @param CatalogC
 * @param CatalogR
 * @param int
 * @returns Char*
 */
void query_9(MCatalog, int, FILE *);

/**
 * \brief Efetua a query 10, tendo como output o top N(int) de utilizadores com as maiores mensagens de commit por repositório
 * @param CatalogU
 * @param CatalogC
 * @param int
 * @returns Out
 */
void query_10(MCatalog, int, FILE *);

//Efetua a query 11, tendo como output o top N(int) de utilizadores com as maiores mensagens de commit
void query_11(MCatalog, int, FILE *);

//Efetua a query 12, tendo como output o numero total de registos de utilizadores validos
void query_12(MCatalog, FILE *);

//Efetua a query 13, tendo como output o numero total de registos de commits validos
void query_13(MCatalog, FILE *);

//Efetua a query 14, tendo como output o numero total de registos de repos validos
void query_14(MCatalog, FILE *);

#endif