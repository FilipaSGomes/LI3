/**
 * @file Ficheiro com as várias funções relacionadas ao tratamento de registos de Users
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"

int verify_user(User * data){
    int flag = 1;
    if (data->id == -1 || data->followers == -1 || data->following == -1 || data->pub_gist == -1 || data->pub_repo== -1){flag=0;}
    return flag;
}

int build_followers(char *fl, User *data){
    int j=0, f=0;
    data->flr_id = realloc(data->flr_id, sizeof(int) * data->followers);
    while (fl != NULL && j < data->followers)
    {
        data->flr_id[j] = verify_int(fl);
        if (data->flr_id[j]==-1) j=data->followers;
        j++;
        fl = strtok(NULL, "[] ,");
    }
    if (j!=data->followers || fl!=NULL ){f=1;} 
    return f;
}

int build_following(char *fg, User *data){
    int j=0, f=0;
    data->flg_id = realloc(data->flg_id, sizeof(int) * data->following);
    while (fg != NULL && j<data->following)
    {
        data->flg_id[j] = verify_int(fg);
        if (data->flg_id[j]==-1) j=data->following;
        j++;
        fg = strtok(NULL, "[] ,");

    }
    if (j!=data->following|| fg!=NULL){f=1;}  
    return f;
}

int build_users(User *data, char *line, int *i) //retorna user criado
{
    char *l_check, *fl, *fg, *dt;
    l_check= strstr(line,";;"); //Ve se algum campo esta vazio
    int f=0;
    data->id = verify_int(strsep(&line, ";"));
    data->login = strdup(strsep(&line, ";"));
    data->type = strdup(strsep(&line, ";"));
    f+=!verify_type(data->type);
    dt = strtok(strsep(&line, ";"),"- :");
    f+=build_date(dt,data->c_date);
    data->followers = verify_int(strsep(&line, ";"));
    fl = strtok(strsep(&line, ";"), "[] ,");
    f+=build_followers(fl,data);
    data->following = verify_int(strsep(&line, ";"));
    fg = strtok(strsep(&line, ";"), "[] ,");  
    f+=build_following(fg,data);
    data->pub_gist = verify_int(strsep(&line, ";"));
    data->pub_repo = verify_int(strsep(&line, ";\n"));
    if(verify_user(data) && l_check==NULL&&f==0){(*i)++;}
    return 0;
}

User *parse_users(int *i, char *entrada)
{
    User *users= malloc(sizeof(User));
    int  at = 1;
    FILE *u = fopen(entrada, "r");
    char *buff = malloc(sizeof(char) * 500000);

    if (u == NULL){
        printf("Error when opening %s! \n", entrada);
        return NULL;
    }else{
        fgets(buff, 500000, u);
    }

    while (fgets(buff, 500000, u))
    {
        build_users(&users[*i], buff, i);
        //Verifica se é necessário alocar mais espaço para os users
        if ((*i) == at)
        {
            users = realloc(users, sizeof(User) * (*i)*2);
            at = 2 * (*i);
        }
    }
    free(buff);
    fclose(u);

    return users;
}

int save_users(User *u, int i, char *saida){

    FILE *us = fopen(saida, "w"); //Novo ficheiro para guardar a informação correta.
    fprintf(us,"id;login;type;created_at;followers;follower_list;following;following_list;public_gists;public_repos\n");
    int j = 0, m = 0;
    while (j < i)
    {
        fprintf(us, "%d;%s;%s;%d-%02d-%02d %02d:%02d:%02d;%d;[", u[j].id, u[j].login, u[j].type, u[j].c_date[0], u[j].c_date[1], u[j].c_date[2], u[j].c_date[3], u[j].c_date[4], u[j].c_date[5], u[j].followers);
        if ((u[j].followers) != 0){
            m = 0;
            while (m < (u[j].followers)){
                fprintf(us,"%d", u[j].flr_id[m]);
                m++;
                if (m != u[j].followers){
                    fprintf(us, ", ");
                }
            }
        }
        fprintf(us,"];%d;[",u[j].following);

        //Lista de Pessoas que Segue
        if ((u[j].following) != 0){
            m = 0;
            while (m < (u[j].following)){
                fprintf(us, "%d", u[j].flg_id[m]);
                m++;
                if (m != u[j].following){
                    fprintf(us, ", ");
                }
            }
        }
        fprintf(us,"];%d;%d\n",u[j].pub_gist,u[j].pub_repo);
        j++;
    }
    fclose(us);

    return 0;
}

void free_users (User *user,int i){
    for (int j=0; j<i; j++){
        free(user[j].login);
        free(user[j].type);
        free(user[j].flr_id);
        free(user[j].flg_id);
    }
}

 
//<================= EX2 =================>

void insert_user(int id, Hash_table *table) {
    size_t pos = hash(id);
    user_entry *new_user = table->users[pos];
    user_entry *x = calloc(1,sizeof(struct user_entry));
    x->id = id;
    if (new_user == NULL) {
        table->users[pos] = x;
    } else {
        while ( new_user->next != NULL) {
            new_user = new_user->next;
        }
        new_user->next = x;
    }
}

int parse_hash_users(Hash_table *table, char *entrada)
{
    FILE *u = fopen(entrada, "r");
    FILE *o = fopen("saida/users-final.csv", "w");
    char *buff = malloc(sizeof(char) * 500000);

    if (u == NULL){
        printf("Error when opening %s! \n", entrada);
        return 0;
    }else{
        fgets(buff, 500000, u);
        fprintf(o,"%s",buff);
    }

    while (fgets(buff, 500000, u))
    {
        char *strc;
        strc=strdup(buff);
        int token=verify_int(strtok(strc, ";"));
        insert_user(token, table);
        fprintf(o,"%s",buff);
        free(strc);
    }
    free(buff);
    fclose(u);
    fclose(o);

    return 1;
}