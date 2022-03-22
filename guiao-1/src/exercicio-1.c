/**
 * @file Ficheiro com as várias funções relacionadas ao exercicio 1
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exercicio-1.h"

#define fusers "entrada/users.csv"
#define fcommits "entrada/commits.csv"
#define frepos "entrada/repos.csv"

int exercicio_1() {
	int total_users = 0, total_repos = 0, total_commits = 0;

	printf("\nPARSING ORIGINAL FILES!\n\n");

	//Users
	printf("PARSING USERS...\n");
	User *users;							   //Alocar espaço para os Users
	users = parse_users(&total_users, fusers); //Criar a lista dos usuarios
	printf("USERS PARSED!\n");
	save_users(users, total_users, "saida/users-ok.csv");
	printf("USERS SAVED!\n\n");
	free_users(users, total_users);
	free(users);

	//Repos
	printf("PARSING REPOS...\n");
	Repo *repos;							   //Alocar espaço para os Repos
	repos = parse_repos(&total_repos, frepos); //Criar lista de repositorios
	printf("REPOS PARSED!\n");
	save_repos(repos, total_repos, "saida/repos-ok.csv");
	printf("REPOS SAVED!\n\n");
	free_repos(repos, total_repos);
	free(repos);

	//Commits
	printf("PARSING COMMITS...\n");
	Commit *commits;								   //Alocar espaço para os Commits
	commits = parse_commits(&total_commits, fcommits); //Criar lista de commits
	printf("COMMITS PARSED!\n");
	save_commits(commits, total_commits, "saida/commits-ok.csv");
	printf("COMMITS SAVED!\n\n");
	free_commits(commits, total_commits);
	free(commits);

	printf("ALL FILES PARSED AND SAVED!\n\n");

	return 0;
}