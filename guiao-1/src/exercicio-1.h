/**
 * @file Ficheiro com as várias invocações às funções do exercicio 1
 */
#ifndef EXERCICIO1_H
#define EXERCICIO1_H

#include "structs.h"
#include "users.h"
#include "commits.h"
#include "repos.h"
#include "hash.h"

#define fusers "entrada/users.csv"
#define fcommits "entrada/commits.csv"
#define frepos "entrada/repos.csv"

/**
 * \brief Remove os registos invalidos de 3 ficheiros, de acordo com os requesitos do exercicio 1, e cria 3 novos ficheiros com os registos validos
 * @returns 0
 */
int exercicio_1();

#endif