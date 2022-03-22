/**
 * @file Ficheiro com as várias funções relacionadas ao tratamento de registos de commits
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commits.h"

int verify_commits(Commit *data){
    int flag = 1;
    if (data->repo_id == -1 || data->author_id == -1 || data->committer_id == -1) flag = 0;
    return flag;
}

int build_commits(Commit *data, char *line, int *i){ //retorna user criado
    char *dt;
    int f=0;
    data->repo_id = verify_int(strsep(&line, ";"));
    data->author_id = verify_int(strsep(&line, ";"));
    data->committer_id = verify_int(strsep(&line, ";"));
    dt = strtok(strsep(&line, ";"),"-:");
    f+=build_date(dt,data->cmt_date);
    data->message = strdup(strsep(&line, "\n"));
    if(verify_commits(data) && f==0){
        (*i)++;
        }
    return 0;
}

Commit *parse_commits(int *i, char *entrada){
    Commit *commits= malloc(sizeof(Commit));
    int  at = 1;
    FILE *r = fopen(entrada, "r");
    char *buff = malloc(sizeof(char) * 200000);

    if (r == NULL){
        printf("Error when opening %s!\n", entrada);
        return NULL;
    }else fgets(buff, 200000, r);

    while (fgets(buff, 200000, r)){
        build_commits(&commits[*i], buff, i);
        //Verifica se é necessário alocar mais espaço para os commits
        if ((*i) == at){
            commits = realloc(commits, sizeof(Commit) * (*i)*2);
            at = 2 * (*i);
        }
    }
    free(buff);
    fclose(r);

    return commits;
}

int save_commits(Commit *u, int i, char *saida){

    FILE *us = fopen(saida, "w"); //Novo ficheiro para guardar a informação correta.
    fprintf(us, "repo_id;author_id;committer_id;commit_at;message\n");
    int j = 0;
    while (j < i){
        fprintf(us, "%d;%d;%d;%d-%02d-%02d %02d:%02d:%02d;%s\n", u[j].repo_id, u[j].author_id, u[j].committer_id, u[j].cmt_date[0], u[j].cmt_date[1], u[j].cmt_date[2], u[j].cmt_date[3], u[j].cmt_date[4], u[j].cmt_date[5], u[j].message);
        j++;
    }
    fclose(us);

    return 0;
}

void free_commits (Commit *commit,int i){
    for (int j=0; j<i; j++){
        free(commit[j].message);
    }
}


//<================= EX2 =================>


void insert_commit(int commit, Hash_table *table){
    size_t pos = hash(commit);
    commit_entry *commit_e = table->commits[pos];
    commit_entry *x = calloc(1, sizeof(struct commit_entry));
    x->id = commit;
    if (commit_e == NULL)table->commits[pos] = x;
    else {
        while (commit_e->next != NULL){
            commit_e = commit_e->next;
        }
        commit_e->next = x;
    }
}

int build_hash_commits(Commit *commit, Hash_table *table, char *line, int *i){ //retorna user criado
    char *dt;
    int f = 0;
    commit->repo_id = verify_int(strsep(&line, ";"));
    commit->author_id = verify_int(strsep(&line, ";"));
    commit->committer_id = verify_int(strsep(&line, ";"));
    dt = strtok(strsep(&line, ";"), "-:");
    f += build_date(dt, commit->cmt_date);
    commit->message = strdup(strsep(&line, "\n"));
    int a = commit->author_id;
    int b = commit->committer_id;
    if ((verify_hash(table, b,1))==0 &&(verify_hash(table, a,1))==0 && f == 0){
        (*i)++;
        insert_commit(commit->repo_id, table);
    }
    return 0;
}

Commit *parse_hash_commits(Hash_table *table, int *i, char *entrada){
    Commit *commits= malloc(sizeof(Commit));
    int  at = 1;
    FILE *r = fopen(entrada, "r");
    char *buff = malloc(sizeof(char) * 500000);

    if (r == NULL){
        printf("Error when opening %s!\n", entrada);
        return NULL;
    }else{fgets(buff, 500000, r);}

    while (fgets(buff, 500000, r)){
        build_hash_commits(&commits[*i],table, buff, i);
        if ((*i) == at){
            commits = realloc(commits, sizeof(Commit) * (*i)*2);
            at = 2 * (*i);
        }
    }
    free(buff);
    fclose(r);

    return commits;
}

int save_hash_commits(Commit *u, Hash_table *table, int i, char *saida){
    FILE *us = fopen(saida, "w"); //Novo ficheiro para guardar a informação correta.
    fprintf(us, "repo_id;author_id;committer_id;commit_at;message\n");
    int j = 0;
    while (j < i){
        if(verify_hash(table,u[j].repo_id,2)==0){ 
            fprintf(us, "%d;%d;%d;%d-%02d-%02d %02d:%02d:%02d;%s\n", u[j].repo_id, u[j].author_id, u[j].committer_id, u[j].cmt_date[0], u[j].cmt_date[1], u[j].cmt_date[2], u[j].cmt_date[3], u[j].cmt_date[4], u[j].cmt_date[5], u[j].message);
        }
        j++;
    }
    fclose(us);

    return 0;
}