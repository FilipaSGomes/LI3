/**
 * @file Ficheiro com as várias funções relacionadas ao catálogo que contem os registos de users
 */

#include "catalog_u.h"

/** Contem toda a informaçao do registo de um user*/
struct user{
    /** id do user */
    int id;
    /** nome de login */
    char *login;
    /** tipo do user */
    char *type;
    /** numero total de repos em que o user é um contribuidor */
    int t_repos;
    /** lista dos ids de repos em que o user é um contribuidor */
    int *repos;
    /** numero total de commits que o user efetuou */
    int t_coms;
    /** lista dos ids de commits que o user efetuou */    
    int *coms;
    /** numero total de amigos (seguidores mútuos) do user */
    int t_fr;
    /** lista dos ids de amigos (seguidores mútuos) do user */
    int *friends;
};

/** Struct para representar users na hashtable*/
struct user_entry{
    int id;
    User u;
	struct user_entry *next;
};

/** Struct para representar um catálogo de users (hashtable)*/
struct catalog_u{
    UEntry users[MAX_TABLE];
};

//Verifica o nome de login de um user, com base num id
char* check_user_login_by_id(CatalogU u, int id){
    UEntry us= u->users[hash(id)];
    while(us!=NULL){
        if(us->id==id){
            return strdup(us->u->login);
        }else{us=us->next;}
    }
    return "";
}

//Verifica se um user de determinado id existe no catálogo
int check_user_exists(CatalogU u, int id){
    int n =0;
    UEntry us= u->users[hash(id)];
    while(us!=NULL){
        if(us->id==id){
            n=1;
            us=NULL;
        }else{us=us->next;}
    }
    return n;
}

//Insere um registo de user no catálogo
void set_user_entry (CatalogU cu, int n, UEntry ue){
    UEntry new_user = cu->users[n];
    if (new_user == NULL) {
    cu->users[n] = ue;
    } else {
        while (new_user != NULL) {
            new_user = new_user->next;
        }
        new_user = ue;
    }
}

//Cria um novo UEntry que contem um registo de um user
void set_usuary_entry(UEntry new, User u){
    new->u = u;
}

//Atribui um apontador para o registo de user que segue outro registo de user no catálogo
void set_user_next (UEntry user, UEntry un) {
    user->next = un;
}

//Atribui um id a uma struct REntry
void set_user_entry_id (UEntry user, int id) {
    user->id = id;
}

//Guarda o id do user associado ao registo a guardar
void set_user_id (User user, int id) {
    user->id = id;
}

//Guarda o tipo do user associado ao registo a guardar
void set_user_type (User user, char* type) {
    user->type = strdup (type);
}

//Guarda o nome de login user associado ao registo a guardar
void set_user_login (User user, char* login) {
    user->login = strdup(login);
}

//Guarda a lista dos ids dos commits efetuados pelo user associado ao registo a guardar
void set_user_coms (User user, int* coms) {
    user->coms = coms;
}

//Guarda a lista dos ids dos repos em que o user associado ao registo a guardar, é um contribuidor
void set_user_reps (User user, int* reps) {
    user->repos = reps;
}

//Guarda a lista dos ids dos amigos do user associado ao registo a guardar
void set_user_friends (User user, int* friends) {
    user->friends = friends;
}

//Insere um registo de user numa hashtable
void insert_user(UEntry u, CatalogU table) {
    int id=u->id;
    size_t pos = hash(id);
    UEntry new_user = table->users[pos];
    if (new_user == NULL) {
        table->users[pos] = u;
    } else {
        while ( new_user->next != NULL) {
            new_user = new_user->next;
        }
        new_user->next = u;
    }
}

//Verifica se um user de um determinado id é um bot
int check_bot(int id, CatalogU table){
    size_t pos = hash(id);
    UEntry u=table->users[pos];
    while (u!=NULL && u->id!=id){
        u=u->next;
    }
    if(strcmp(u->u->type,"Bot")==0){return 1;}
    return 0;
    
}

//Constroi o registo de um user com os dados associados a este, e depois insere-o numa hashtable
int insert_user_cat(int id, char*log, char*tp, int *fr,int tf, CatalogU table){
    UEntry new = malloc(sizeof(struct user_entry));
    set_user_entry_id(new,id);
    set_user_next(new,NULL);
    User u = malloc(sizeof(struct user));
    set_user_id(u,id);
    set_user_login(u, log);
    set_user_type(u, tp);
    set_user_friends(u,fr);
    set_user_reps(u,NULL);
    set_user_coms(u,NULL);
    u->t_fr=tf;
    u->t_coms=0;
    u->t_repos=0;
    int gs=-1;
    if (strcmp(tp,"Bot") == 0) gs=0;
    else if (strcmp(tp,"Organization") == 0) gs=1;
    else if (strcmp(tp,"User") == 0) gs=2;
    set_usuary_entry(new, u);
    //printf("%d -> %d,%s,%s\n", new->id, new->u->id, new->u->login, new->u->type);
    insert_user(new, table);
    return gs;
}

//Inicializa um catálogo de user (hashtable)
CatalogU cat_u_init() {
    CatalogU c_u=malloc(sizeof(struct catalog_u));
    for(int i=0; i<MAX_TABLE; i++) {
        c_u->users[i] = NULL;
    }
    return c_u;
}

//Aplica a funçao free a um catálogo de user (hashtable)
void free_catalog_u(CatalogU cu)
{
    UEntry user, u_prev;

    for (int i = 0; i < MAX_TABLE; i++)
    {
        if ((user = cu->users[i]) != NULL)
        {
            while (user != NULL)
            {
                u_prev = user;
                user = user->next;
                free(u_prev);
            }
            set_user_entry(cu, i, NULL);
        }
    }
    free(cu);
}

//Adiciona um commit e o seu respetivo id, a lista de ids de commits de um user
void add_com_to_user(int id, int r_id, int com_id, CatalogU table){
    size_t pos = hash(id);
    UEntry u=table->users[pos];
    while (u!=NULL && u->id!=id){
        u=u->next;
    }
    if (u!=NULL){
        User us=u->u;
        int n=0;
        int max_r=us->t_repos;
        int max_c=us->t_coms;
        while (n<max_r){
            if(us->repos[n]==r_id){n=max_r+1;}
            n++;
        }
        if(n!=max_r+2){
            us->t_repos++;
            us->repos=realloc(us->repos,sizeof(int)*(max_r+1));
            us->repos[max_r]=r_id;
        }
        us->coms=realloc(us->coms,sizeof(int)*(max_c+1));
        us->coms[max_c] = com_id;
        us->t_coms++;
    }
}

//Devolve o id do user associado a um registo numa determinada posiçao do catalogo
int get_id_by_pos(CatalogU cu, int x, int y){
    UEntry ul=cu->users[x];
    while(y>0 && ul!=NULL){
        ul=ul->next;
        y--;
    }
    if(ul==NULL)return -1;
    return ul->id;
}

//Devolve numero de commits efetuado por um user associado a um registo numa determinada posiçao do catalogo
int get_n_coms_by_pos(CatalogU cu, int x, int y){
    UEntry ul=cu->users[x];
    while(y>0 && ul!=NULL){
        ul=ul->next;
        y--;
    }
    if(ul==NULL)return -1;
    return ul->u->t_coms;
}

//Devolve uma lista com os ids dos commits efetuados por um user associado a um registo numa determinada posiçao do catalogo
int *get_user_coms_by_pos(CatalogU cu, int x, int y){
    UEntry ul=cu->users[x];
    while(y>0 && ul!=NULL){
        ul=ul->next;
        y--;
    }
    if(ul==NULL)return NULL;
    int i=ul->u->t_coms,j=0;
    int *list=malloc(sizeof(int)*i);
    while(j<i){
        list[j]=ul->u->coms[j];
        j++;
    }
    return list;
}

//Devolve o numero de amigos do user associado a um registo, dado um id de procura
int get_user_t_fr_by_id(CatalogU cu, int id){
    size_t pos = hash(id);
    UEntry new = cu->users[pos];
    while(new!=NULL && new->id!=id){
        new=new->next;
    }
    if(new==NULL)return -1;
    return new->u->t_fr;
}

//Devolve o numero total de commits efetuado pelo user associado a um registo, dado um id de procura
int get_user_t_coms_by_id(CatalogU cu, int id){
    size_t pos = hash(id);
    UEntry new = cu->users[pos];
    while(new!=NULL && new->id!=id){
        new=new->next;
    }
    if(new==NULL)return -1;
    return new->u->t_coms;
}

//Devolve uma lista com os ids dos amigos do user associado a um registo, dado um id de procura
int *get_user_friends_by_id(CatalogU cu, int id){
    size_t pos = hash(id);
    UEntry new = cu->users[pos];
    while(new!=NULL && new->id!=id){
        new=new->next;
    }
    if(new==NULL)return NULL;
    int i=0, total = new->u->t_fr;
    int *arr=malloc(sizeof(int)*total);
    while(i<total){
        arr[i]=new->u->friends[i];
        i++;
    }
    return arr;
}

//Devolve uma lista com os ids dos commits efetuados pelo o user associado a um registo, dado um id de procura
int *get_user_coms_by_id(CatalogU cu, int id){
    size_t pos = hash(id);
    UEntry new = cu->users[pos];
    while(new!=NULL && new->id!=id){
        new=new->next;
    }
    if(new==NULL)return NULL;
    int i=0, total = new->u->t_coms;
    int *arr=malloc(sizeof(int)*total);
    while(i<total){
        arr[i]=new->u->coms[i];
        i++;
    }
    return arr;
}

//Devolve o numero total de registos de users validados
int check_n_total_users(CatalogU cu){
    int pos=0, i=0;
    while(pos<MAX_TABLE){
        UEntry *r = &(cu->users[pos]);
        while (*r){
            r = &(*r)->next;
            i++;
        }
        pos++;
    }
    return i;
}