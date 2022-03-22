/**
 * @file Ficheiro com funções relativas ao parsing dos ficheiros .csv que contêm os dados dos Users, Repos e Commits.
 */

#include "parser.h"


/** Função responsável por fazer o parsing do ficheiro contendo os dados dos repositorios*/
int parse_hash_repo(MCatalog database, char *entrada)
{
    // Verificação do ficheiro
    FILE *u = fopen(entrada, "r");
    char *buff = malloc(sizeof(char) * 2500000);

    if (u == NULL)
    {
        printf("Error when opening %s! \n", entrada);
        return 0;
    }
    else
    {
        fgets(buff, 2500000, u);
    }
    // Leitura do ficheiro linha a linha e analize dos dados
    while (fgets(buff, 2500000, u))
    {
        int verf=0;
        char *strc;
        strc = strdup(buff);
        char *ts;
        ts=strc;
        int id = verify_int(strsep(&strc, ";"));
        int owner = verify_int(strsep(&strc, ";"));
        char *full_name = strdup(strsep(&strc, ";"));
        if(strcmp(full_name,"")==0)verf++;
        char *license = strdup(strsep(&strc, ";"));
        if(strcmp(license,"")==0)verf++;
        char *has_wiki = strdup(strsep(&strc, ";"));
        if(!(strcmp(has_wiki,"True")==0 ||strcmp(has_wiki,"False")==0))verf++;
        char *desc_repo = strdup(strsep(&strc, ";"));
        char *language = strdup(strsep(&strc, ";"));
        if(strcmp(language,"")==0)verf++;
        char *d_branch = strdup(strsep(&strc, ";"));
        if(strcmp(d_branch,"")==0)verf++;
        char *dt = strtok(strsep(&strc, ";"), "- :");
        verf += verify_date(dt);
        char *tm = strdup(strsep(&strc, ";"));
        char *tm2 = strdup(tm);
        verf += verify_date(strtok(tm2,"- :"));
        char *cdt = strtok(tm, "- :");
        int data[3],j = 0;
        while (cdt != NULL && j < 3)
        {
            data[j] = verify_int(cdt);
            if (data[j] == -1)
                j = 3;
            j++;
            cdt = strtok(NULL, "- :");
        }
        int forks_count = verify_int(strsep(&strc, ";"));
        if(forks_count==-1)verf++;
        int open_issues = verify_int(strsep(&strc, ";"));
        if(open_issues==-1)verf++;
        int stargazers_count = verify_int(strsep(&strc, ";"));
        if(stargazers_count==-1)verf++;
        int size = verify_int(strsep(&strc, ";\n"));
        if(size==-1)verf++;
        // Inserção do novo repositorio no catalogo dos Repos
        if(verf==0&& id!=-1 && owner!=-1&&j==3){
          insert_repo_in_db(id, owner, desc_repo, language, data, database);
        }
        strc=ts;
        free(tm);
        free(tm2);
        free(strc);
        free(full_name);
        free(license);
        free(has_wiki);
        free(desc_repo);
        free(language);
        free(d_branch);
    }
    free(buff);
    fclose(u);

    return 1;
}

/** Funcao responsável por verificar, em duas listas de ids, os elementos em comum,
 * retornando-os na forma de uma lista de inteiros.
 * Esta função guarda também o tamanho final da lista no apontador "tf".
 */
int *build_friends(char *l1,char *l2,int *tf,int a, int b, int *verf){
    char *token=strtok(l1, "[, ]");
    int n=0, *sz=malloc(sizeof(int));
    int i=0,j=0;
    while(token!=NULL){
        i++;
        //printf("[%s in %s]",token, l2);
        if (strstr(l2, token)!=NULL){
            sz=realloc(sz,sizeof(int)*(n+1));
            sz[n]=verify_int(token);
            if(sz[n]==-1)(*verf)=-1;
            n++;
        }
        token=strtok(NULL,"[, ]");
    }
    *tf=n;
    char *t2=strtok(l2,"[, ]");
    while (t2!=NULL)
    {
      j++;
      t2=strtok(NULL,"[, ]");
    }
    free(token);
    free(t2);
    if(a!=i || b!=j)(*verf)++;
    if (n==0){
      free(sz);
      return NULL;
    }
    return sz;
}

/** Função responsável por fazer o parsing do ficheiro contendo os dados dos utilizadores*/
int parse_hash_user(MCatalog database, char *entrada){
  // Verificação de ficheiros
  FILE *u = fopen(entrada, "r");
  char *buff = malloc(sizeof(char) * 2500000);
  if (u == NULL){
    printf("Error when opening %s! \n", entrada);
    return 0;
  }else{fgets(buff, 2500000, u);}

  // Leitura e intepretação dos dados do ficheiro, linha a linha.
  while (fgets(buff, 2500000, u)){
    char *strc = strdup(buff);
    char *ts;
    ts=strc;
    char *l_check=strstr(buff,";;");
    int tf;
    int id = verify_int(strsep(&strc, ";"));
    char *login = strdup(strsep(&strc, ";"));
    char *type = strdup(strsep(&strc, ";"));
    int verf=0;
    char *dt = strtok(strsep(&strc, ";"),"- :");
    verf+=verify_date(dt);
    int a=verify_int(strsep(&strc, ";"));
    char *l1 = strdup(strsep(&strc, ";"));
    int b=verify_int(strsep(&strc, ";"));
    char *l2 = strdup(strsep(&strc, ";"));
    int v1 = verify_int(strsep(&strc, ";"));
    int v2 = verify_int(strsep(&strc, ";"));
    // Criação de lista de amigos através da lista de pessoas que seguem e sao seguidas por um dado user
    int *fr=build_friends(l1,l2,&tf,a,b,&verf);
    strc=ts;
    // Inserção do novo utilizador no catálogo dos Users
    if(verf==0 && id!=-1 && a!=-1 && b!=-1 &&v1!=-1 && v2!=-1 && l_check==NULL && (strcmp(type,"User")==0 ||strcmp(type,"Organization")==0 ||strcmp(type,"Bot")==0 ))
      insert_user_in_db(id, login, type, fr,tf,database);
    free(login);
    free(strc);
    free(type);
    free(l1);
    free(l2);
  }
  free(buff);
  fclose(u);

  return 1;
}

/** Função responsável por fazer o parsing do ficheiro contendo os dados dos commits*/
int parse_hash_comm(MCatalog database, char *entrada){
  //Verificação dos ficheiros
  FILE *u = fopen(entrada, "r");
  char *buff = malloc(sizeof(char) * 2500000);
  static int id = MAX_TABLE;
  if (u == NULL){
    printf("Error when opening %s! \n", entrada);
    return 0;
  }else{fgets(buff, 2500000, u);}
  // Leitura e interpretação dos commits linha a linha.
  while (fgets(buff, 2500000, u)){
    char *strc;
    strc = strdup(buff);
    char *ts;
    ts=strc;
    int r_id = verify_int(strsep(&strc, ";"));
    int a_id = verify_int(strsep(&strc, ";"));
    int u_id = verify_int(strsep(&strc, ";"));
    char *cdt = strdup(strsep(&strc, ";"));
    char *cdt2 = strdup(cdt);
    char *message=strdup(strsep(&strc,";"));
    int j = 0, data[3];
    char *cd;
    cd=strtok(cdt,"- :");
    while (cd != NULL && j < 3)
    {
        data[j] = verify_int(cd);
        if (data[j] == -1)
            j = 3;
        j++;
        cd = strtok(NULL, "- :");
    }

    if(r_id!=-1 &&a_id!=-1 &&u_id!=-1 &&j==3 && verify_date(strtok(cdt2,"- :"))==0){
      insert_commit_in_db(id,r_id,a_id,u_id,message,data,database);
    }
    id++;
    strc=ts;
    free(strc);
    free(cdt);
    free(cdt2);
    free(message);
  }
  free(buff);
  fclose(u);

  return 1;
}