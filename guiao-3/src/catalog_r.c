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

//Devolve o inteiro que reperesenta se o repo associado ao registo tem um bot como colaborador
int get_has_bot(Repo repos){
    return repos->has_bot;
}

//Verifica se um repo de determinado id existe no catálogo
int check_repo_exists(CatalogR u, int id){
    int n =0;
    REntry us= u->repos[hash(id)];
    while(us!=NULL){
        if(us->id==id){
            n=1;
            us=NULL;
        }else{us=us->next;}
    }
    return n;
}

//Insere um registo de repo no catálogo
void set_repos_entry (CatalogR cr, int n, REntry re) {
    size_t pos = hash(n);
    REntry new_repos = cr->repos[pos];
    if (new_repos == NULL) {
        cr->repos[pos] = re;
    } else {
        while (new_repos!= NULL) {
            new_repos = new_repos->next;
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
void insert_repo_cat(int id,int  owner, char *desc_repo, char *language, int *data, CatalogR table){
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
    r->last_activ[0] = data[0];
    r->last_activ[1] = data[1];
    r->last_activ[2] = data[2];
    r->last_commit[0]=0;
    r->last_commit[1]=0;
    r->last_commit[2]=0;
    r->n_contribs=0;
    r->n_coms=0;
    set_repository_entry(re, r);
    insert_repo(re, table);
}

//Inicializa um catálogo de repo (hashtable)
CatalogR cat_r_init() {
    CatalogR c_r = malloc(sizeof(struct catalog_r));
    for(int i=0; i<MAX_TABLE; i++) {
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
        if ((repo = cr->repos[i]) != NULL)
        {
            while (repo != NULL)
            {
                r_prev = repo;
                repo = repo->next;
                free(r_prev);
            }
            set_repos_entry(cr, i, NULL);
        }
    }
    free(cr);
}

//Adiciona um contribuidor(e os dados relativos a ele) ao registo, atualizando os campos deste relacionados a contribuidores (ultimo commit, ultima atividade, numero de contibuidores, etc..)
int add_contrib(int id,int bot, int user, int repo_id, CatalogR r, int fg,int *cdt){
    REntry entry = r->repos[hash(repo_id)];
    if (entry==NULL){return 0;}
    Repo repo = NULL;
    while (entry!=NULL && entry->id!=repo_id ){
        entry=entry->next;
    }
    if (entry!=NULL){
        repo= entry->r;
    }
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
            flag=10;
        }
        if(bot == 1 && get_has_bot(repo)==0){
            set_has_bot(repo,1);
            flag++;
        }
        if (fg==1){
            int max_c = repo->n_coms;
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

//Devolve a data do ultimo commit efetuado num repo, por sua vez inserido numa determinada posiçao do catalogo
int *get_repos_last_activ_by_position(CatalogR cr, int x, int y){
    REntry rl=cr->repos[x];
    while(y>0 && rl!=NULL){
        rl=rl->next;
        y--;
    }
    if(rl==NULL)return NULL;
    int *dt=malloc(sizeof(int)*3);
    dt[0]=rl->r->last_commit[0];
    dt[1]=rl->r->last_commit[1];
    dt[2]=rl->r->last_commit[2];
    return dt;
}

//Devolve o id de um repo inserido numa determinada posiçao do catalogo
int get_repos_id_by_position(CatalogR cr, int x, int y){
    REntry rl=cr->repos[x];
    while(y>0 && rl!=NULL){
        rl=rl->next;
        y--;
    }
    if(rl==NULL)return -1;
    return rl->id;
}

//Devolve a descriçao de um repo inserido numa determinada posiçao do catalogo
char *get_repos_desc_by_position(CatalogR cr, int x, int y){
    REntry rl=cr->repos[x];
    while(y>0 && rl!=NULL){
        rl=rl->next;
        y--;
    }
    if(rl==NULL)return NULL;
    return strdup(rl->r->desc_repo);
}

//Devolve a data da ultima atividade num repo inserido numa determinada posiçao do catalogo
int *get_repos_date_by_position(CatalogR cr, int x, int y){ 
    REntry rl=cr->repos[x];
    while(y>0 && rl!=NULL){
        rl=rl->next;
        y--;
    }
    if(rl==NULL)return NULL;
    int *dt=malloc(sizeof(int)*3);
    dt[1]=rl->r->last_activ[1];
    dt[2]=rl->r->last_activ[2];
    dt[0]=rl->r->last_activ[0];
    return dt;
}

//Devolve a linguagem de um repo inserido numa determinada posiçao do catalogo
char *get_repos_lng_by_position(CatalogR cr, int x, int y){
    REntry rl=cr->repos[x];
    while(y>0 && rl!=NULL){
        rl=rl->next;
        y--;
    }
    if(rl==NULL)return NULL;
    return strdup(rl->r->language);
}

//Dado um determinado id, devolve a data do ultimo commit efetuado no repo associado a este
int *get_repos_date_by_id(CatalogR cr, int id){
    size_t pos = hash(id);
    REntry new = cr->repos[pos];
    while(new!=NULL && new->id!=id){
        new=new->next;
    }
    if(new==NULL)return NULL;
    int *dt=malloc(sizeof(int)*3);
    dt[1]=new->r->last_commit[1];
    dt[2]=new->r->last_commit[2];
    dt[0]=new->r->last_commit[0];
    return dt;
}

//Dado um determinado id, devolve a linguagem do repo associado a este
char *get_repos_lng_by_id(CatalogR cr, int id){
    size_t pos = hash(id);
    REntry new = cr->repos[pos];
    while(new!=NULL && new->id!=id){
        new=new->next;
    }
    if(new==NULL)return NULL;
    return strdup(new->r->language);
}

//Dado um determinado id, devolve id do dono do repo associado a este
int get_repo_owner_by_id(CatalogR cr, int id){
    size_t pos = hash(id);
    REntry new = cr->repos[pos];
    while(new!=NULL && new->id!=id){
        new=new->next;
    }
    if(new==NULL)return -1;
    return new->r->owner;
}

//Dado um determinado id, devolve o numero de commits efetuado no repo associado a este
int get_repos_n_coms_by_id(CatalogR cr, int id){
    size_t pos = hash(id);
    REntry new = cr->repos[pos];
    while(new!=NULL && new->id!=id){
        new=new->next;
    }
    if(new==NULL)return -1;
    return new->r->n_coms;
}

//Dado um determinado id, devolve lista de ids de commits dados para o repo associado a este
int *get_repos_coms_by_id(CatalogR cr, int id){
    size_t pos = hash(id);
    REntry new = cr->repos[pos];
    while(new!=NULL && new->id!=id){
        new=new->next;
    }
    if(new==NULL)return NULL;
    int i=0, total=new->r->n_coms;
    int *arr=malloc(sizeof(int)*total);
    while(i<total){
        arr[i]=new->r->coms[i];
        i++;
    }
    return arr;
}

//Verifica se existem registos vazios no catalogo dos repos
void check_empty_repos(CatalogR cr){
    int pos=0;
    while(pos<MAX_TABLE){
        REntry *r = &(cr->repos[pos]);
        while (*r){
            if ((*r)->r->n_coms == 0)
            {
                REntry temp = *r;
                *r = temp->next;
                free(temp);
            }
            else
            { // advance to address of next "link" pointer
                r = &(*r)->next;
            }
        }
        pos++;
    }
}

//Devolve o numero total de registos de repos validados
int check_n_total_repos(CatalogR cr){
    int pos=0, i=0;
    while(pos<MAX_TABLE){
        REntry *r = &(cr->repos[pos]);
        while (*r){
            r = &(*r)->next;
            i++;
        }
        pos++;
    }
    return i;
}