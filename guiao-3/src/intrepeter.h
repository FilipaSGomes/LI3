/**
 * @file Ficheiro com as várias invocações às funções relacionadas à interpretação dos ficheiros de entrada
 */

#ifndef INTREPETER_H
#define INTREPETER_H

#include "meta_catalog.h"
#include "query.h"
#include "pagination.h"



int loop(MCatalog);

void do_query_from_line(char *, MCatalog ,FILE *);

void interpete_query_file(char *,MCatalog);

#endif