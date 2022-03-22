/**
 * @file Ficheiro com funções relativas ao parsing dos ficheiros .csv que contêm os dados dos Users, Repos e Commits.
 */

#include "parser.h"


/** Função responsável por fazer o parsing do ficheiro contendo os dados dos repositorios*/
int parse_hash_repo(CatalogR table, char *entrada, GStats gs)
{
    // Verificação do ficheiro
    FILE *u = fopen(entrada, "r");
    char *buff = malloc(sizeof(char) * 500000);

    if (u == NULL)
    {
        printf("Error when opening %s! \n", entrada);
        return 0;
    }
    else
    {
        fgets(buff, 500000, u);
    }

    // Leitura do ficheiro linha a linha e analize dos dados
    while (fgets(buff, 500000, u))
    {
        char *strc;
        strc = strdup(buff);
        int id = verify_int(strtok(strc, ";"));
        int owner = verify_int(strtok(NULL, ";"));
        strtok(NULL, ";");
        strtok(NULL, ";");
        strtok(NULL, ";");
        char *desc_repo = strdup(strtok(NULL, ";"));
        char *language = strdup(strtok(NULL, ";"));
        strtok(NULL, ";");
        strtok(NULL, ";");
        char *cdt = strtok(strtok(NULL, ";"), "- :");
        int data[6],j = 0;
        while (cdt != NULL && j < 3)
        {
            data[j] = verify_int(cdt);
            if (data[j] == -1)
                j = 3;
            j++;
            cdt = strtok(NULL, "- :");
        }

        // Inserção do novo repositorio no catalogo dos Repos
        insert_repo_cat(id, owner, desc_repo, language, data, table, gs);
        free(strc);
    }
    free(buff);
    fclose(u);

    return 1;
}

/** Funcao responsável por verificar, em duas listas de ids, os elementos em comum,
 * retornando-os na forma de uma lista de inteiros.
 * Esta função guarda também o tamanho final da lista no apontador "tf".
 */
int *build_friends(char *l1,char *l2,int *tf){
    char *token=strtok(l1, "[, ]");
    int n=0, *sz=malloc(sizeof(int));
    while(token!=NULL){
        //printf("[%s in %s]",token, l2);
        if (strstr(l2, token)!=NULL){
            sz=realloc(sz,sizeof(int)*(n+1));
            sz[n]=verify_int(token);
            n++;
        }
        token=strtok(NULL,"[, ]");
    }
    *tf=n;
    if (n==0){return NULL;}
    return sz;
}

/** Função responsável por fazer o parsing do ficheiro contendo os dados dos utilizadores*/
int parse_hash_user(CatalogU table, char *entrada, GStats gs){
  
  // Verificação de ficheiros
  FILE *u = fopen(entrada, "r");
  char *buff = malloc(sizeof(char) * 500000);
  if (u == NULL){
    printf("Error when opening %s! \n", entrada);
    return 0;
  }else{fgets(buff, 500000, u);}

  // Leitura e intepretação dos dados do ficheiro, linha a linha.
  while (fgets(buff, 500000, u)){
    char *strc;
    int tf;
    strc = strdup(buff);
    int id = verify_int(strsep(&strc, ";"));
    char *login = strdup(strsep(&strc, ";"));
    char *type = strdup(strsep(&strc, ";"));
    strsep(&strc, ";");
    strsep(&strc, ";");
    char *l1 = strdup(strsep(&strc, ";"));
    strsep(&strc, ";");
    char *l2 = strdup(strsep(&strc, ";"));

    // Criação de lista de amigos através da lista de pessoas que seguem e sao seguidas por um dado user
    int *fr=build_friends(l1,l2,&tf);

    // Inserção do novo utilizador no catálogo dos Users
    insert_user_cat(id, login, type, fr,tf,table, gs);
    free(l1);
    free(l2);
  }
  free(buff);
  fclose(u);

  return 1;
}

/** Função responsável por fazer o parsing do ficheiro contendo os dados dos commits*/
int parse_hash_comm(CatalogC table,CatalogR r_table, CatalogU u_table, char *entrada, GStats gs){
  
  //Verificação dos ficheiros
  FILE *u = fopen(entrada, "r");
  char *buff = malloc(sizeof(char) * 500000);
  static int id = 300000;
  if (u == NULL){
    printf("Error when opening %s! \n", entrada);
    return 0;
  }else{fgets(buff, 500000, u);}

  // Leitura e interpretação dos commits linha a linha.
  while (fgets(buff, 500000, u)){
    char *strc;
    strc = strdup(buff);
    int r_id = verify_int(strtok(strc, ";"));
    int a_id = verify_int(strtok(NULL, ";"));
    int u_id = verify_int(strtok(NULL, ";"));
    char *cdt = strdup(strtok(NULL, ";"));
    char *message=strdup(strtok(NULL,";"));
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

    //Verificação da existencia dos repos e users aos quais o commit se referem
    if (check_user_exists(u_table, a_id)==1 && check_user_exists(u_table,u_id)==1 && check_repo_exists(r_table,r_id)==1){
        
        //Adição de commits e contribuidores ao repositorio para o qual este se refere
        //Caso este nao seja ainda um contribuidor do repositorio atual, o numero de contribuidores global é incrementado.
        if (add_contrib(id,check_bot(u_id, u_table),u_id,r_id,r_table,gs,1,data)){set_t_contribs(gs);};
        if (add_contrib(id,check_bot(a_id, u_table),a_id,r_id,r_table,gs,0,data)){set_t_contribs(gs);};
        
        //Adição do id do commit a lista de commits dados pelo o user_id
        add_com_to_user(u_id, r_id, id, u_table);

        //Incerção do novo commit no catalogo dos Commits
        insert_commit_cat(id,r_id,a_id,u_id,message,data, table, gs);
        id++;
    }
    free(strc);
  }
  free(buff);
  fclose(u);

  return 1;
}