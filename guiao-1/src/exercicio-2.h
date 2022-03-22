/**
 * @file Ficheiro com as várias invocações às funções do exercicio 2
 */
#ifndef EXERCICIO2_H
#define EXERCICIO2_H

#include "structs.h"
#include "users.h"
#include "commits.h"
#include "repos.h"
#include "hash.h"

#define fusers2 "saida/users-ok.csv"
#define fcommits2 "saida/commits-ok.csv"
#define frepos2 "saida/repos-ok.csv"

/**
 * \brief Remove os registos invalidos de 3 ficheiros, de acordo com os requesitos do exercicio 2, e cria 3 novos ficheiros com os registos validos
 * @returns 0
 */
int exercicio_2();

#endif