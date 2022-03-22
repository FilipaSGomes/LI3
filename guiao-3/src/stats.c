/**
 * @file Ficheiro com as várias funções relacionadas a várias estatisticas sobre os registos
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stats.h"

/** Representa um catálogo de várias estatisticas globais sobre os registos*/
struct global_stats {
    /** número total de users*/
    int t_users;
    /** número total de commits*/
    int t_comms;
    /** número total de repos*/
    int t_repos;
    /** número total de contribuidores*/
    int t_contribs;
    /** lista em que cada elemento contem o numero de users de um determinado tipo*/
    int u_type[3];
    /** número total de repos com bots como contribuidores*/
    int bot_repos;
};

//Inicializa um catálogo de várias estatisticas globais sobre os registos
GStats init_stats(){
    GStats s=malloc(sizeof(struct global_stats));
    s->t_users = 0;
    s->t_comms = 0;
    s->t_repos = 0;
    s->t_contribs = 0;
    s->bot_repos = 0;
    s->u_type[0] = 0;
    s->u_type[1] = 0;
    s->u_type[2] = 0;
    return s;
}

//Aplica a função Free a um catálogo de várias estatisticas globais sobre os registos
void free_stats(GStats s){
    free(s);
}

//Aumenta o número total de utilizadores em um catálogo de várias estatisticas globais sobre os registos
void set_t_users(GStats gs){
    gs->t_users ++;
}

//Aumenta o número total de utilizadores em tipo do int fornecido, de um catálogo de várias estatisticas globais sobre os registos
void set_type_n (GStats gs, int i) {
    gs->u_type[i] ++;
}

//Aumenta o número total de contribuidores em um catálogo de várias estatisticas globais sobre os registos
void set_t_contribs (GStats gs){
    gs->t_contribs ++;
}

//Aumenta o número total de repos em um catálogo de várias estatisticas globais sobre os registos
void set_t_repos(GStats gs){
    gs->t_repos ++;
}

//Aumenta o número total de commits em um catálogo de várias estatisticas globais sobre os registos
void set_t_comms(GStats gs){
    gs->t_comms ++;
}

//Aumenta o número total de bots que são colaboradores em um catálogo de várias estatisticas globais sobre os registos
void set_bot_repos (GStats gs){
    gs->bot_repos ++;
}


//Devolve o número total de users registados em um catálogo de várias estatisticas globais sobre os registos
int get_t_users(GStats gs)
{
    return gs->t_users;
}

//Devolve o número total de users do tipo i(int) registados em um catálogo de várias estatisticas globais sobre os registos
int get_type_n(GStats gs, int i)
{
    return gs->u_type[i];
}

//Devolve o número total de contribuidores registados em um catálogo de várias estatisticas globais sobre os registos
int get_t_contribs(GStats gs)
{
    return gs->t_contribs;
}

//Devolve o número total de repos registados em um catálogo de várias estatisticas globais sobre os registos
int get_t_repos(GStats gs)
{
    return gs->t_repos;
}

//Devolve o número total de commits registados em um catálogo de várias estatisticas globais sobre os registos
int get_t_comms(GStats gs)
{
    return gs->t_comms;
}

//Devolve o número total de bots que são colaboradores registados em um catálogo de várias estatisticas globais sobre os registos
int get_bot_repos(GStats gs)
{
    return gs->bot_repos;
}
