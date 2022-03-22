/**
 * @file Ficheiro com as várias funções relacionadas ao tratamento de hashtables
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

size_t hash(const size_t s){
	size_t hash=0;
	hash = s;
    hash = hash % MAX_TABLE;
    return hash;
}

void table_init(Hash_table *table) {
    for(int i=0; i<MAX_TABLE; i++) {
        table->commits[i] = malloc(sizeof(commit_entry));
        table->commits[i] = NULL;
        table->users[i] = malloc(sizeof(user_entry));
        table->users[i] = NULL;
        table->repos[i] = malloc(sizeof(repo_entry));
        table->repos[i] = NULL;
    }
}

void free_table(Hash_table *table) {
    user_entry *user, *u_prev;
    repo_entry *repo, *r_prev;
    commit_entry *commit, *c_prev;

    for(int i=0; i<MAX_TABLE; i++) {
        if (table->users[i] != NULL) {
            user = table->users[i];
            while (user != NULL) {
                u_prev = user;
                user = user->next;
                free(u_prev);
            }
            table->users[i] = NULL;
        }
    }
    for(int i=0; i<MAX_TABLE; i++) {
        if (table->repos[i] != NULL) {
            repo = table->repos[i];
            while (repo != NULL) {
                r_prev = repo;
                repo = repo->next;
                free(r_prev);
            }
            table->repos[i] = NULL;
        }
    }
    for(int i=0; i<MAX_TABLE; i++) {
        if (table->commits[i] != NULL) {
            commit = table->commits[i];
            while (commit != NULL) {
                c_prev = commit;
                commit = commit->next;
                free(c_prev);
            }
            table->commits[i] = NULL;
        }
    }

    free(user);
    free(repo);
    free(commit);
}


int verify_hash(Hash_table *table, int data, int flag){
    int f = 2;
    switch(flag){
        case 1:{
            //recebe 1 e verifica se esta nos users "aliniea C"
            //owner_id
            size_t pos = hash(data);
            user_entry *ue = table->users[pos];
            while (ue != NULL && f!=0) {
                if (ue->id == data) f = 0;
                else ue = ue->next;
            } 
            break;
        }
        case 2:{
            //recebe 1 e verifica nos repos "aliniea B"
            //repo_id
            size_t pos = hash(data);
            repo_entry *repo = table->repos[pos];
            while (repo != NULL && f!=0) {
                if (repo->id == data) f = 0;
                else repo = repo->next;
            } 
            break;
        }
        case 3:{
            //recebe 1 e verifica nos repos "aliniea B"
            //repo_id
            size_t pos = hash(data);
            commit_entry *com = table->commits[pos];
            while (com != NULL && f!=0) {
                if (com->id == data) f = 0;
                else com = com->next;
            } 
            break;
        }
        default : {
            break;
        }
    }
    return f;
}