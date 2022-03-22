/**
 * @file Ficheiro com as várias invocações às funções relacionadas a várias estatisticas sobre os registos
 */

#ifndef STATS_H
#define STATS_H

typedef struct global_stats *GStats;

/**
 * \brief Inicializa a struct que contem várias estatisticas
 * @returns GStats
 */
GStats init_stats();

/**
 * \brief Aplica a função Free a uma struct GStats
 */
void free_stats(GStats);

/**
 * \brief Dado um catálogo de estatisticas e um tipo de utilizador(int), incrementa o numero associado ao indice da lista que contabiliza o numero de users por tipo
 * @param GStats
 * @param Int
 */
void set_type_n (GStats ,int);

/**
 * \brief Dado um catálogo de estatisticas, incrementa o numero total de users
 * @param GStats
 */
void set_t_users (GStats);

/**
 * \brief Dado um catálogo de estatisticas, incrementa o numero total de contribuidores
 * @param GStats
 */
void set_t_contribs (GStats);

/**
 * \brief Dado um catálogo de estatisticas, incrementa o numero total de repos
 * @param GStats
 */
void set_t_repos (GStats );

/**
 * \brief Dado um catálogo de estatisticas, incrementa o numero total de commits
 * @param GStats
 */
void set_t_comms (GStats );

/**
 * \brief Dado um catálogo de estatisticas, incrementa o numero total de bots que são contribuidores nos repos
 * @param GStats
 */
void set_bot_repos(GStats);

/**
 * \brief Dado um catálogo de estatisticas e um tipo de utilizador(int), devolve o numero total de users desse tipo 
 * @param GStats
 * @param int
 * @returns Int
 */
int get_type_n(GStats, int);

/**
 * \brief Dado um catálogo de estatisticas, devolve o numero total de users
 * @param GStats
 * @returns Int
 */
int get_t_users(GStats);

/**
 * \brief Dado um catálogo de estatisticas, devolve o numero total de contribuidores
 * @param GStats
 * @returns Int
 */
int get_t_contribs(GStats);

/**
 * \brief Dado um catálogo de estatisticas, devolve o numero total de repos
 * @param GStats
 * @returns Int
 */
int get_t_repos(GStats);

/**
 * \brief Dado um catálogo de estatisticas, devolve o numero total de commits
 * @param GStats
 * @returns Int
 */
int get_t_comms(GStats);

/**
 * \brief Dado um catálogo de estatisticas, devolve o numero total de bots que são contribuidores nos repos
 * @param GStats
 * @returns Int
 */
int get_bot_repos(GStats);

#endif