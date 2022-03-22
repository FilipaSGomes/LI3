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

/**Função responsável por definir uma dada entry no catalogo dos Commits*/
void set_com_entry (CatalogC cc, int n, CEntry ce) {
    CEntry new_commit = cc->commits[n];
    if (new_commit == NULL) {
        cc->commits[n] = ce;
    } else {
        while (new_commit != NULL) {
            new_commit = new_commit->next;
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
void insert_commit_cat(int id,int r_id,int a_id,int u_id,char *message, int *data, CatalogC table){
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
    set_commit_entry(ce, c);
    insert_commit(ce,table);
}

/**Função responsável por inicializar o catalogo dos commits*/
CatalogC cat_c_init() {
    CatalogC c_c=malloc(sizeof(struct catalog_c));
    c_c->total=0;
    for(int i=0; i<MAX_TABLE; i++) {
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
        if ((commit = cc->commits[i]) != NULL)
        {
            while (commit != NULL)
            {
                c_prev = commit;
                commit = commit->next;
                free(c_prev);
            }
            set_com_entry(cc, i, NULL);
        }
    }
    free(cc);
}

//Devolve a data de um commit, dado um id de procura
int* get_com_date_by_id(CatalogC cc, int id){
    int *dt=malloc(sizeof(int)*3);
    size_t pos = hash(id);
    CEntry new = cc->commits[pos];
    while(new!=NULL && new->id!=id){
        new=new->next;
    }
    if(new==NULL)return NULL;
    dt[0]=new->c->date[0];
    dt[1]=new->c->date[1];
    dt[2]=new->c->date[2];
    return dt;
}

//Devolve a data de um commit numa determinada posiçao do catalogo
int* get_com_date_by_position(CatalogC cc, int x,int y){
    CEntry cl=cc->commits[x];
    while(y>0 && cl!=NULL){
        cl=cl->next;
        y--;
    }
    if(cl==NULL)return NULL;
    int *dt=malloc(sizeof(int)*3);
    dt[0]=cl->c->date[0];
    dt[1]=cl->c->date[1];
    dt[2]=cl->c->date[2];
    return dt;
}

//Devolve o id do repo em que o commit foi efetuado, dado um id de procura
int get_com_r_by_id(CatalogC cc, int id){
    size_t pos = hash(id);
    CEntry new = cc->commits[pos];
    while(new!=NULL && new->id!=id){
        new=new->next;
    }
    if(new==NULL)return -1;
    return new->c->r_id;
}

//Devolve o id do repo em que o commit, numa determinada posiçao do catalogo, foi efetuado
int get_com_r_id_by_position(CatalogC cc, int x, int y){
    CEntry cl=cc->commits[x];
    while(y>0 && cl!=NULL){
        cl=cl->next;
        y--;
    }
    if(cl==NULL)return -1;
    return cl->c->r_id;
}

//Dado um id de procura, devolve o id do user que efetuou o commit
int get_com_u_by_id(CatalogC cc, int id){
    size_t pos = hash(id);
    CEntry new = cc->commits[pos];
    while(new!=NULL && new->id!=id){
        new=new->next;
    }
    if(new==NULL)return -1;
    return new->c->u_id;
}

//Dado um id de procura, devolve a mensagem associada a um commit
char* get_com_message_by_id(CatalogC cc, int id){
    size_t pos = hash(id);
    CEntry new = cc->commits[pos];
    while(new!=NULL && new->id!=id){
        new=new->next;
    }
    if(new==NULL)return NULL;
    return strdup(new->c->message);
}

//Devolve o numero total de registos de commits validados
int check_n_total_commits(CatalogC cc){
    int pos=0, i=0;
    while(pos<MAX_TABLE){
        CEntry *r = &(cc->commits[pos]);
        while (*r){
            r = &(*r)->next;
            i++;
        }
        pos++;
    }
    return i;
}