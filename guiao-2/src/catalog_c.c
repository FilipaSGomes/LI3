/**
 * @file Ficheiro com as várias funções relacionadas ao catálogo que contem os registos de commits
 */

#include "catalog_c.h"

/** Contem toda a informaçao do registo de um commit*/
struct commit{
    /** id do user que deu commit */
    int u_id;
    /** id do autor */
    int a_id;
    /** id do repo */
    int r_id;
    /** mensagem do commit */
    char *message;
    /** data do commit */
    int date[3];
};

/** Struct para representar commits na hashtable*/
struct commit_entry{
    /**ID do Commit*/
    int id;
    /**Dados do Commit*/
    Commit c;
    /**Proximo Commit da Lista Ligada*/
    struct commit_entry *next;
};

/** Struct para representar um catálogo de commits (hashtable)*/
struct catalog_c{
    /**Hash table de Commits que permite guardar todos os seus dados
     * Cada uma das entradas é em si uma lista ligada contendo os Commits.
    */
    CEntry commits[MAX_TABLE];
    /**Número total de commits*/
    int total;
};

/**Função responsável por retornar uma commit_entry do catalogo através da sua posição*/
CEntry get_com_entry (CatalogC cc, int n) {
  return cc->commits[n];
}

/**Função responsável por retornar uma commit_entry do catalogo através do seu ID*/
CEntry get_com_entry2 (CatalogC cc, int n) {
  size_t pos=hash(n);
  CEntry new=cc->commits[pos];
  return new;
}

/**Função responsável por retornar uma Commit do catalogo através do seu ID caracteristico*/
Commit get_com_by_id(CatalogC u, int id){
    CEntry us= get_com_entry2(u,id);
    while(us!=NULL){
        if(us->id==id){
            return us->c;
        }else{us=us->next;}
    }
    return NULL;
}

/**Função responsável por retornar a próxima commit_entry de uma lista ligada de Entrys*/
CEntry get_com_next (CEntry com) {
    return com->next;
}

/**Função responsável por retornar o ID de um dado Commit */
int get_com_entry_id (CEntry com) {
    return com->id;
}

/**Função responsável por retornar o Commit de uma dada commit_entry*/
Commit get_entry_commit(CEntry cc)
{
    return cc->c;
}

/**Função responsável por retornar o ID do usuário responsável pelo commit*/
int get_com_u_id (Commit commit) {
  return commit->u_id;
}

/**Função responsável por retornar o ID do repositório para onde o commit foi realizado*/
int get_com_r_id (Commit commit) {
  return commit->r_id;
}

/**Função responsável por retornar mensagem de um dado commit*/
char *get_com_message (Commit commit) {
  return strdup(commit->message);
}

/**Função responsável por retornar a data de submissão de um dado commit*/
int *get_com_date (Commit commit ) {
  int *dt=malloc(sizeof(int)*3);
  dt[0] = commit->date[0];
  dt[1] = commit->date[1];
  dt[2] = commit->date[2];
  return dt;
}

/**Função responsável por definir uma dada entry no catalogo dos Commits*/
void set_com_entry (CatalogC cc, int n, CEntry ce) {
    CEntry new_commit = cc->commits[n];
    if (new_commit == NULL) {
        cc->commits[n] = ce;
    } else {
        while (new_commit != NULL) {
            new_commit = get_com_next(new_commit);
        }
        new_commit = ce;
    }
}

/**Função responsável por definir a próxima CEntry da lista ligada*/
void set_com_next (CEntry com, CEntry cn) {
    com->next = cn;
}

/**Função responsável por definir o commit de uma dada CEntry*/
void set_commit_entry (CEntry com, Commit commit) {
    com->c = commit;
}

/**Função responsável por definir o id de uma dada CEntry*/
void set_com_entry_id (CEntry com, int id) {
    com->id = id;
}

/**Função responsável por definir o id de um dado commit*/
void set_com_u_id (Commit commit, int id) {
  commit->u_id = id;
}

/**Função responsável por definir o id do repositorio de um dado commit*/
void set_com_r_id (Commit commit, int id) {
  commit->r_id = id;
}

/**Função responsável por definir o author id de um dado commit*/
void set_com_a_id(Commit c, int a_id){
    c->a_id=a_id;
}

/**Função responsável por definir a mensagem de um dado commit*/
void set_com_message (Commit commit, char* message) {
  commit->message = strdup(message);
}

/**Função responsável por definir a data de um dado commit*/
void set_com_date (Commit commit, int *date) {
  commit->date[0] = date[0];
  commit->date[1] = date[1];
  commit->date[2] = date[2];
}

/**Função responsável por inserir um dado commi no catalogo dos commits*/
void insert_commit(CEntry u, CatalogC table) {
  int id = u->id;
  size_t pos = hash(id);
  CEntry new_com=table->commits[pos];
  if (new_com == NULL){
      table->commits[pos]= u;
  }else{
      while (new_com->next!=NULL)
      {
          new_com=new_com->next;
      }
      new_com->next=u;
  }
}

/**Função responsável por recebendo os dados necessários criar um novo commit*/
void insert_commit_cat(int id,int r_id,int a_id,int u_id,char *message, int *data, CatalogC table, GStats gs){
    table->total+=1;
    CEntry ce=malloc(sizeof(struct commit_entry));
    set_com_next(ce,NULL);
    set_com_entry_id(ce,id);
    Commit c=malloc(sizeof(struct commit));
    set_com_u_id(c, u_id);
    set_com_r_id(c, r_id);
    set_com_a_id(c, a_id);
    set_com_message(c, message);
    set_com_date(c, data);
    set_t_comms(gs);
    set_commit_entry(ce, c);
    insert_commit(ce,table);
}

/**Função responsável por inicializar o catalogo dos commits*/
CatalogC cat_c_init() {
    CatalogC c_c=malloc(sizeof(struct catalog_c));
    c_c->total=0;
    for(int i=0; i<MAX_TABLE; i++) {
        c_c->commits[i] = malloc(sizeof(struct commit_entry));
        c_c->commits[i] = NULL;
    }
    return c_c;
}

/**Função responsável por libertar o espaço ocupado pelo catalogos dos commits*/
void free_catalog_c(CatalogC cc)
{
    CEntry commit, c_prev;

    for (int i = 0; i < MAX_TABLE; i++)
    {
        if ((commit = get_com_entry(cc,i)) != NULL)
        {
            while (commit != NULL)
            {
                c_prev = commit;
                commit = get_com_next(commit);
                free(c_prev);
            }
            set_com_entry(cc, i, NULL);
        }
    }
    free(cc);
}