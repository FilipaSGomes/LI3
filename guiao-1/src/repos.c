/**
 * @file Ficheiro com as várias funções relacionadas ao tratamento de registos de repos
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "repos.h"

int verify_repos(Repo * data){
    int flag = 1;
    if (strcmp(data->full_name,"")==0 ||strcmp(data->license,"")==0 || !(strcmp(data->has_wiki,"True")==0 || strcmp(data->has_wiki,"False")==0 ) ||strcmp(data->language,"")==0 ||strcmp(data->default_branch,"")==0 || data->cmt_id == -1 || data->owner_id == -1 || data->forks_count == -1 || data->open_issues == -1 || data->stargazers_count == -1 || data->size == -1){flag = 0;}
    return flag;
}

//Cria User A Partir da Linha
int build_repos(Repo *data, char *line, int *i) //retorna user criado
{
    char *cdt,*udt;
    //l_check= strstr(line,";;"); //Ve se algum campo esta vazio
    int f=0;
    data->cmt_id = verify_int(strsep(&line, ";"));
    data->owner_id = verify_int(strsep(&line, ";"));
    data->full_name = strdup(strsep(&line, ";"));
    data->license = strdup(strsep(&line, ";"));
    data->has_wiki = strdup(strsep(&line, ";"));
    data->description = strdup(strsep(&line, ";"));
    data->language = strdup(strsep(&line, ";"));
    data->default_branch = strdup(strsep(&line, ";"));
    cdt = strtok(strsep(&line, ";"), "- :");
    f += build_date(cdt, data->cr_date);
    udt = strtok(strsep(&line, ";"), "- :");
    f += build_date(udt, data->updated_at);
    data->forks_count = verify_int(strsep(&line, ";"));
    data->open_issues = verify_int(strsep(&line, ";"));
    data->stargazers_count = verify_int(strsep(&line, ";"));
    data->size = verify_int(strsep(&line, ";\n"));
    if(verify_repos(data) && f==0){(*i)++;}
    return 0;
}


Repo * parse_repos(int *i, char* entrada )
{
    Repo *repos= malloc(sizeof(Repo));
    int  at = 1;
    FILE *r = fopen(entrada, "r");
    char *buff = malloc(sizeof(char) * 500000);

    if (r == NULL){
        printf("Error when opening %s!\n", entrada);
        return NULL;
    }else{fgets(buff, 500000, r);}

    while (fgets(buff, 500000, r)){
        build_repos(&repos[*i], buff, i);
        //Verifica se é necessário alocar mais espaço para os repos
        if ((*i) == at){
            repos = realloc(repos, sizeof(Repo) * (*i)*2);
            at = 2 * (*i);
        }
    }
    free(buff);
    fclose(r);

    return repos;
}

int save_repos(Repo *u, int i, char *saida){

    FILE *us = fopen(saida, "w"); //Novo ficheiro para guardar a informação correta.
    fprintf(us, "id;owner_id;full_name;license;has_wiki;description;language;default_branch;created_at;updated_at;forks_count;open_issues;stargazers_count;size\n");
    int j = 0;
    while (j < i)
    {
        fprintf(us, "%d;%d;%s;%s;%s;%s;%s;%s;%d-%02d-%02d %02d:%02d:%02d;%d-%02d-%02d %02d:%02d:%02d;%d;%d;%d;%d\n", u[j].cmt_id, u[j].owner_id, u[j].full_name, u[j].license, u[j].has_wiki, u[j].description, u[j].language, u[j].default_branch, u[j].cr_date[0], u[j].cr_date[1], u[j].cr_date[2], u[j].cr_date[3], u[j].cr_date[4], u[j].cr_date[5], u[j].updated_at[0], u[j].updated_at[1], u[j].updated_at[2], u[j].updated_at[3], u[j].updated_at[4], u[j].updated_at[5], u[j].forks_count, u[j].open_issues, u[j].stargazers_count, u[j].size);
        j++;
    }
    fclose(us);

    return 0;
}

void free_repos (Repo *repo,int i){
    for (int j=0; j<i; j++){
        free(repo[j].full_name);
        free(repo[j].license);
        free(repo[j].has_wiki);
        free(repo[j].description);
    }
}

//<================= EX2 =================>

void insert_repo(int repo, Hash_table *table){
    size_t pos = hash(repo);
    repo_entry *new_repo = table->repos[pos];
    repo_entry *x = calloc(1,sizeof(struct repo_entry));
    x->id = repo;
    if (new_repo == NULL) {
        table->repos[pos] = x;
    } else {
        while ( new_repo->next != NULL) {
            new_repo = new_repo->next;
        }
        new_repo->next = x;
    }
}

//Cria User A Partir da Linha
int build_hash_repos(Repo *data, Hash_table *table, char *line, int *i) //retorna user criado
{
    char *cdt,*udt;
    int f=0;
    data->cmt_id = verify_int(strsep(&line, ";"));
    data->owner_id = verify_int(strsep(&line, ";"));
    data->full_name = strdup(strsep(&line, ";"));
    data->license = strdup(strsep(&line, ";"));
    data->has_wiki = strdup(strsep(&line, ";"));
    data->description = strdup(strsep(&line, ";"));
    data->language = strdup(strsep(&line, ";"));
    data->default_branch = strdup(strsep(&line, ";"));
    cdt = strtok(strsep(&line, ";"), "- :");
    f += build_date(cdt, data->cr_date);
    udt = strtok(strsep(&line, ";"), "- :");
    f += build_date(udt, data->updated_at);
    data->forks_count = verify_int(strsep(&line, ";"));
    data->open_issues = verify_int(strsep(&line, ";"));
    data->stargazers_count = verify_int(strsep(&line, ";"));
    data->size = verify_int(strsep(&line, ";\n"));
    if(f==0){ // && owner id esta na user hash table
        (*i)++;
        insert_repo(data->cmt_id, table);
    }
    return 0;
}

Repo *parse_hash_repos(Hash_table *table, int *i, char *entrada)
{
    Repo *repos= malloc(sizeof(Repo));
    int  at = 1;
    FILE *r = fopen(entrada, "r");
    char *buff = malloc(sizeof(char) * 500000);

    if (r == NULL){
        printf("Error when opening %s!\n", entrada);
        return NULL;
    }else{fgets(buff, 500000, r);}

    while (fgets(buff, 500000, r)){
        build_hash_repos(&repos[*i],table, buff, i);
        if ((*i) == at){
            repos = realloc(repos, sizeof(Repo) * (*i)*2);
            at = 2 * (*i);
        }
    }
    free(buff);
    fclose(r);

    return repos;
}

int save_hash_repos(Repo *u, Hash_table *table, int i, char *saida){

    FILE *us = fopen(saida, "w"); //Novo ficheiro para guardar a informação correta.
    fprintf(us, "id;owner_id;full_name;license;has_wiki;description;language;default_branch;created_at;updated_at;forks_count;open_issues;stargazers_count;size\n");
    int j = 0;
    while (j < i){
        if (verify_hash(table, u[j].owner_id, 1) == 0 && verify_hash(table, u[j].cmt_id, 3) == 0)
        {
            fprintf(us, "%d;%d;%s;%s;%s;%s;%s;%s;%d-%02d-%02d %02d:%02d:%02d;%d-%02d-%02d %02d:%02d:%02d;%d;%d;%d;%d\n", u[j].cmt_id, u[j].owner_id, u[j].full_name, u[j].license, u[j].has_wiki, u[j].description, u[j].language, u[j].default_branch, u[j].cr_date[0], u[j].cr_date[1], u[j].cr_date[2], u[j].cr_date[3], u[j].cr_date[4], u[j].cr_date[5], u[j].updated_at[0], u[j].updated_at[1], u[j].updated_at[2], u[j].updated_at[3], u[j].updated_at[4], u[j].updated_at[5], u[j].forks_count, u[j].open_issues, u[j].stargazers_count, u[j].size);
        }
        j++;
    }
    fclose(us);

    return 0;
}