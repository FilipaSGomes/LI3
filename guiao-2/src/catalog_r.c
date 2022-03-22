/**
 * @file Ficheiro com as várias funções relacionadas ao catálogo que contem os registos de repos
 */

#include "catalog_r.h"

/** Contem toda a informaçao do registo de um repo*/
struct repo{
    /** id do repo*/
    int id;
    /** id do dono */
    int owner;
    /** se o repo tem um bot como um colaborador */
    int has_bot;
    /** linguagem do repo */
    char *language;
    /** data da ultima atividada */
    int last_activ[3];
    /** data do ultimo commit efetuado */
    int last_commit[3];
    /** descriçao do repo */
    char *desc_repo;
    /** numero de commits */
    int n_coms;
    /** lista de ids de commits dados para o repo */
    int *coms;
    /**numero de contribuidores */
    int n_contribs;
    /** lista de ids dos contribuidores */
    int *usrs;
};

/** Struct para representar repos na hashtable*/
struct repo_entry{
    int id;
    Repo r;
    struct repo_entry *next;
};

/** Struct para representar um catálogo de repos (hashtable)*/
struct catalog_r{
    REntry repos[MAX_TABLE];
};

//Devolve um registo de repos conforme o indice(int) pedido
REntry get_repos_entry (CatalogR cr, int n) {
    size_t pos = hash(n);
    REntry r = cr->repos[pos];
    return r;
}

//Devolve um registo de repos conforme uma posição(int) pedido
REntry get_repos_by_position (CatalogR cr, int pos) {
    REntry r = cr->repos[pos];
    return r;
}

//Devolve o registo de repos pedido
Repo get_entry_repos(REntry re){
    return re->r;
}

//Devolve o proximo registo de repos
REntry get_repos_next (REntry repos){
  return repos->next;
}

//Devolve o id associado a um REntry
int get_repo_entry_id ( REntry repos) {
    return repos->id;
}

//Devolve o id do repo associado ao registo
int get_repos_id ( Repo repos) {
    return repos->id;
}

//Devolve o inteiro que reperesenta se o repo associado ao registo tem um bot como colaborador
int get_has_bot(Repo repos){
    return repos->has_bot;
}

//Devolve a linguagem do repo associado ao registo
char *get_repos_language (Repo repos) {
  return strdup(repos->language);
}

//Devolve a data da ultima atividade do repo associado ao registo
int *get_repos_last_activ (Repo repos) {
  int *dt=malloc(sizeof(int)*3);
  dt[0] = repos->last_activ[0];
  dt[1] = repos->last_activ[1];
  dt[2] = repos->last_activ[2];
  return dt;
}

//Devolve a data em que foi efetuado o último commit no repo associado ao registo
int *get_repos_last_commit (Repo repos) {
  int *dt=malloc(sizeof(int)*3);
  dt[0] = repos->last_commit[0];
  dt[1] = repos->last_commit[1];
  dt[2] = repos->last_commit[2];
  return dt;
}

//Devolve a descrição do repo associado ao registo
char *get_desc_repo (Repo repos) {
  return strdup(repos->desc_repo);
}

//Devolve o numero de commits efetuados no repo associado ao registo
int get_repos_n_coms(Repo repos){
    return repos->n_coms;
}

//Devolve a lista que contem os ids dos commits efetuados no repo associado ao registo
int *get_repos_coms (Repo repos) {
    int *i = malloc(sizeof(repos->coms));
    int j=repos->n_coms;
    int n=0;
    while(n<j){
        i[n]=repos->coms[n];
        n++;
    }
    return i;
}

//Devolve a lista que contem os ids dos colaboradores do repo associado ao registo
int *get_repos_usrs (Repo repos ) {
    int *i = malloc(sizeof(repos->usrs));
    int j=repos->n_contribs;
    int n=0;
    while(n<j){
        i[n]=repos->usrs[n];
        n++;
    }
    return i;
}

//Devolve o id do dono do repo associado ao registo
int get_repos_owner (Repo r) {
    return r->owner;
}

//Verifica se um repo de determinado id existe no catálogo
int check_repo_exists(CatalogR u, int id){
    int n =0;
    REntry us= get_repos_entry(u,id);
    while(us!=NULL){
        if(us->id==id){
            n=1;
            us=NULL;
        }else{us=us->next;}
    }
    return n;
}

//Dado um id, devolve o registo de repo associado a esse id
Repo get_repos_by_id(CatalogR u, int id){
    REntry us= get_repos_entry(u,id);
    while(us!=NULL){
        if(us->id==id){
            return us->r;
        }else{us=us->next;}
    }
    return NULL;
}

//Dado um id, devolve a linguagem do repo associado a esse id
char* get_lg_by_id(CatalogR u, int id){
    REntry us= get_repos_entry(u,id);
    while(us!=NULL){
        if(us->id==id){
            return strdup(us->r->language);
        }else{us=us->next;}
    }
    return NULL;
}

//Insere um registo de repo no catálogo
void set_repos_entry (CatalogR cr, int n, REntry re) {
    size_t pos = hash(n);
    REntry new_repos = cr->repos[pos];
    if (new_repos == NULL) {
        cr->repos[pos] = re;
    } else {
        while (new_repos!= NULL) {
            new_repos = get_repos_next(new_repos);
        }
        new_repos = re;
    }
}

//Atribui um apontador para o registo de repo que segue outro registo de repo no catálogo
void set_repos_next (REntry repos, REntry rn){
    repos->next = rn;
}

//Atribui um id a um registo de repo de modo a facilitar a sua procura no catálogo
void set_repo_entry_id (REntry repos, int id) {
    repos->id = id;
}

//Insere um registo de repo na struct REntry
void set_repository_entry(REntry re, Repo r){
    re->r = r;
}

//Guarda o id do repo associado ao registo a guardar
void set_repo_id (Repo repos, int id) {
    repos->id = id;
}

//Guarda a flag que verifica se o bot é um colaborador do repo associado ao registo a guardar
void set_has_bot(Repo repos, int bot){
    repos->has_bot = bot;
}

//Guarda a linguagem do repo associado ao registo a guardar
void set_repos_language (Repo repos, char *language) {
  repos->language = strdup(language);
}

//Guarda a data da ultima atividade do repo associado ao registo a guardar
void set_repos_last_activ (Repo repos, int *date) {
  repos->last_activ[0] = date[0];
  repos->last_activ[1] = date[1];
  repos->last_activ[2] = date[2];
}

//Guarda a data do ultimo commit do repo associado ao registo a guardar
void set_repos_last_commit (Repo repos, int *date) {
  repos->last_activ[0] = date[0];
  repos->last_activ[1] = date[1];
  repos->last_activ[2] = date[2];
}

//Guarda a descrição do repo associado ao registo a guardar
void set_repos_desc_repo (Repo repos, char *desc) {
  repos->desc_repo = strdup(desc);
}

//Guarda a lista dos ids dos commits do repo associado ao registo a guardar
void set_repos_coms (Repo repos, int *com) {
  repos->coms = com;
}

//Guarda a lista dos ids dos colaboradores do repo associado ao registo a guardar
void set_repos_usrs (Repo repos, int *user) {
  repos->usrs = user;
}

//Guarda o id do dono do repo associado ao registo a guardar
void set_repos_owner(Repo r, int owner){
    r->owner=owner;
}

//Insere um registo de repo numa hashtable
void insert_repo(REntry u, CatalogR table) {
    int id = u->id;
    size_t pos = hash(id);
    REntry new_repo = table->repos[pos];
    if (new_repo == NULL) {
        table->repos[pos] = u;
    } else {
        while ( new_repo->next != NULL) {
            new_repo = new_repo->next;
        }
        new_repo->next = u;
    }
}

//Constroi o registo de um repo com os dados associados a este, e depois insere-o numa hashtable
void insert_repo_cat(int id,int  owner, char *desc_repo, char *language, int *data, CatalogR table, GStats gs){
    REntry re = malloc(sizeof(struct repo_entry));
    set_repos_next(re,NULL);
    set_repo_entry_id(re,id);
    Repo r = malloc(sizeof(struct repo));
    set_repos_coms(r, NULL);
    set_repos_usrs(r, NULL);
    set_repo_id(r,id);
    set_has_bot(r, 0);
    set_repos_owner(r, owner);
    set_repos_coms(r, NULL);
    set_repos_usrs(r, NULL);
    set_repos_desc_repo(r,desc_repo);
    set_repos_language(r, language);
    set_repos_last_activ(r, data);
    int *cdt=malloc(sizeof(int)*3);
    cdt[0]=0;
    cdt[1]=0;
    cdt[2]=0;
    r->n_contribs=0;
    r->n_coms=0;
    set_repos_last_commit(r, cdt);
    free(cdt);
    set_t_repos(gs);   
    set_repository_entry(re, r);
    //printf("%d -> %d,%d,%d-%d-%d %d:%d:%d,%s,%s\n", re->id, re->r->id, re->r->owner, re->r->last_activ[0], re->r->last_activ[1], re->r->last_activ[2], re->r->last_activ[3], re->r->last_activ[4], re->r->last_activ[5], re->r->language, re->r->desc_repo);
    insert_repo(re, table);
}

//Inicializa um catálogo de repo (hashtable)
CatalogR cat_r_init() {
    CatalogR c_r = malloc(sizeof(struct catalog_r));
    for(int i=0; i<MAX_TABLE; i++) {
        c_r->repos[i] = malloc(sizeof(struct repo_entry));
        c_r->repos[i] = NULL;
    }
    return c_r;
}

//Aplica a funçao free a um catálogo de repo (hashtable)
void free_catalog_r(CatalogR cr)
{
    REntry repo, r_prev;

    for (int i = 0; i < MAX_TABLE; i++)
    {
        if ((repo = get_repos_by_position(cr,i)) != NULL)
        {
            while (repo != NULL)
            {
                r_prev = repo;
                repo = get_repos_next(repo);
                free(r_prev);
            }
            set_repos_entry(cr, i, NULL);
        }
    }
    free(cr);
}

//Devolve o repo associado ao id, percorrendo uma REntry
Repo get_repo_in_entry(int repo_id,REntry r){
    while (r!=NULL && r->id!=repo_id ){
        r=r->next;
    }
    if (r!=NULL){
        return r->r;
    }
    return NULL;
}

//Adiciona um contribuidor(e os dados relativos a ele) ao registo, atualizando os campos deste relacionados a contribuidores (ultimo commit, ultima atividade, numero de contibuidores, etc..)
int add_contrib(int id,int bot, int user, int repo_id, CatalogR r, GStats gs, int fg,int *cdt){
    REntry entry = get_repos_entry(r, repo_id);
    if (entry==NULL){return 0;}
    Repo repo = get_repo_in_entry(repo_id, entry);
    if (repo!=NULL){
        int flag=0;
        int n=0;
        int max_u=repo->n_contribs;
        while (n<max_u){
            if(user==repo->usrs[n]){n=max_u+1;}
            n++;
        }
        if(n!=max_u+2){
            repo->n_contribs++;
            repo->usrs=realloc(repo->usrs,sizeof(int)*(repo->n_contribs));
            repo->usrs[n]=user;
            flag=1;
        }
        if(bot == 1 && get_has_bot(repo)==0){
            set_has_bot(repo,1);
            set_bot_repos(gs);
        }
        if (fg==1){
            int max_c=repo->n_coms;
            if (cdt[0] > repo->last_commit[0] || (cdt[0] == repo->last_commit[0] && cdt[1] > repo->last_commit[1]) || (cdt[0] == repo->last_commit[0] && cdt[1] == repo->last_commit[1] && cdt[2] > repo->last_commit[2])){
                repo->last_commit[0] = cdt[0];
                repo->last_commit[1] = cdt[1];
                repo->last_commit[2] = cdt[2];
            }
            repo->coms=realloc(repo->coms,sizeof(int)*(max_c+1));
            repo->coms[max_c]=id;
            repo->n_coms++;
        }
        return flag;
    }
    return 0;
}