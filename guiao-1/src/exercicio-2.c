/**
 * @file Ficheiro com as várias funções relacionadas ao exercicio 2
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exercicio-2.h"

#define fusers2 "saida/users-ok.csv"
#define fcommits2 "saida/commits-ok.csv"
#define frepos2 "saida/repos-ok.csv"

int exercicio_2() {
	int total_repos = 0, total_commits = 0;
	Repo *repos;							   
	Commit *commits;
	Hash_table *table = malloc(sizeof(Hash_table));
	table_init(table);

	printf("\nPARSING OK FILES!\n");
	parse_hash_users(table, fusers2);
	printf("\nUSERS PARSED!");
	repos = parse_hash_repos(table, &total_repos, frepos2);
	printf("\nREPOS PARSED!");
	commits = parse_hash_commits(table, &total_commits, fcommits2);
	printf("\nCOMMITS PARSED!");
	save_hash_commits(commits, table, total_commits, "saida/commits-final.csv");
	printf("\nCOMMITS SAVED!");
	save_hash_repos(repos, table, total_repos, "saida/repos-final.csv");
	printf("\nREPOS SAVED!\n\n");
	free_commits(commits, total_commits);
	free(commits);
	free_repos(repos, total_repos);
	free(repos);
	printf("ALL FILES PARSED AND SAVED!\n\n");
	free_table(table);

	return 0;
}