#include "catalog_u.h"
#include "catalog_r.h"
#include "catalog_c.h"
#include "stats.h"
#include "meta_catalog.h"

//Representa um meta catalogo
struct meta_catalog
{
    //Catalogo de users
    CatalogU users;
    //Catalogo de repos
    CatalogR repos;
    //Catalogo de commits
    CatalogC commits;
    //Estatisticas globais sobre os registos
    GStats stats;
};

// Inicializa o meta catalogo
MCatalog m_cat_init(){
    MCatalog mc=malloc(sizeof(struct meta_catalog));
    mc->users=cat_u_init();
    mc->repos=cat_r_init();
    mc->commits=cat_c_init();
    mc->stats=init_stats();
    return mc;
}

//Liberta o espaço ocupado pelo catalogo
void free_m_cat(MCatalog mc){
    free_catalog_u(mc->users);
    free_catalog_r(mc->repos);
    free_catalog_c(mc->commits);
    free_stats(mc->stats);
    free(mc);
}

//Inserir repositorio no catalogo
void insert_repo_in_db(int id, int owner, char *desc, char* lang, int* data, MCatalog mc){
    if(check_user_exists(mc->users,owner)==1){
        insert_repo_cat(id,owner,desc,lang,data,mc->repos);
        set_t_repos(mc->stats);
    }
}

//Inserir user no catalogo
void insert_user_in_db(int id, char *lg, char *tp, int *dt, int tf, MCatalog mc){
    int i = insert_user_cat(id,lg,tp,dt,tf,mc->users);
    set_t_users(mc->stats);
    if(i!=-1)set_type_n(mc->stats,i);
}

//Inserir commit no catalogo
void insert_commit_in_db(int id, int r_id, int a_id, int u_id, char *message, int *data, MCatalog mc){
    //Verificação da existencia dos repos e users aos quais o commit se referem
    if (check_user_exists(mc->users, a_id)==1 && check_user_exists(mc->users,u_id)==1 && check_repo_exists(mc->repos,r_id)==1){
        int a=add_contrib(id,check_bot(u_id, mc->users),u_id,r_id,mc->repos,1,data);
        int b=add_contrib(id,check_bot(a_id, mc->users),a_id,r_id,mc->repos,0,data);

        //Adição de commits e contribuidores ao repositorio para o qual este se refere
        //Caso este nao seja ainda um contribuidor do repositorio atual, o numero de contribuidores global é incrementado.
        if (a-10>=0)set_t_contribs(mc->stats);
        if (b-10>=0)set_t_contribs(mc->stats);
        if(a==1||a==11)set_bot_repos(mc->stats);
        if(b==1||b==11)set_bot_repos(mc->stats);
        
        //Adição do id do commit a lista de commits dados pelo o user_id
        add_com_to_user(u_id, r_id, id, mc->users);

        //Incerção do novo commit no catalogo dos Commits
        insert_commit_cat(id,r_id,a_id,u_id,message,data,mc->commits);
        set_t_comms(mc->stats);
        id++;
    }
}

//Devolve o numero total de users do tipo bot
int get_total_bot(MCatalog mc){
    return get_type_n(mc->stats,0);
}

//Devolve o numero total de users do tipo organization
int get_total_org(MCatalog mc){
    return get_type_n(mc->stats,1);
}

//Devolve o numero total de users do tipo user
int get_total_us(MCatalog mc){
    return get_type_n(mc->stats,2);
}

//Devolve o numero total de contribuidores
int get_total_contribs(MCatalog mc){
    return get_t_contribs(mc->stats);
}

//Devolve o numero total de repos
int get_total_repos(MCatalog mc){
    return get_t_repos(mc->stats);
}

//Devolve o numero total de commits
int get_total_commits(MCatalog mc){
    return get_t_comms(mc->stats);
}

//Devolve o numero total de users
int get_total_users(MCatalog mc){
    return get_t_users(mc->stats);
}

//Devolve o numero total de repos que contem bots como colaboradores
int get_total_bot_repos(MCatalog mc){
    return get_bot_repos(mc->stats);
}

//Determina os users mais ativos num determinado espaço de datas
int get_top_u_by_activ(MCatalog mc, int **top_n, int n, int* d1,int* d2){
    int k=0, t1, t2;
    for (int x = 0; x < MAX_TABLE; x++)
    {
        int y=0,n_com=0,*coms;
        coms=NULL;
        int id=get_id_by_pos(mc->users,x,y);
        while(id>=0){
            n_com=get_n_coms_by_pos(mc->users,x,y);
            if (n_com > 0) coms = get_user_coms_by_pos(mc->users,x,y);
            int j = 0, tot_user = 0;
            while (j < n_com){
                int *d3 = get_com_date_by_id(mc->commits, coms[j]);
                if (((d1[0] < d3[0]) || (d1[0] == d3[0] && d1[1] < d3[1]) || (d1[0] == d3[0] && d1[1] == d3[1] && d1[2] < d3[2])) && ((d2[0] > d3[0]) || (d2[0] == d3[0] && d2[1] > d3[1]) || (d2[0] == d3[0] && d2[1] == d3[1] && d2[2] > d3[2])))
                {
                    tot_user++;
                }
                j++;
                free(d3);
            }
            j = 0;
            while (j < k)
            {
                if (tot_user > top_n[1][j])
                {
                    t1 = top_n[0][j];
                    t2 = top_n[1][j];
                    top_n[0][j] = id;
                    top_n[1][j] = tot_user;
                    id = t1;
                    tot_user = t2;
                }
                j++;
            }
            if (k < n)
            {
                top_n[0][k] = id;
                top_n[1][k] = tot_user;
                k++;
            }
            y++;
            id=get_id_by_pos(mc->users,x,y);
        }
        free(coms);
    }
    return k;
}

//Devolve o login id de um user
char * check_u_login_by_id(MCatalog mc, int id){
    return check_user_login_by_id(mc->users,id);
}

//Determina os users mais ativos de uma determinada linguagem
int get_top_u_by_lng(MCatalog mc, int**top_n, char* lng,int n){
    int k=0,t1,t2;
    for(int x=0;x<MAX_TABLE;x++){
        int y=0,n_com=0,*coms;
        coms=NULL;
        int id=get_id_by_pos(mc->users,x,y);
        while(id>=0){
            n_com=get_n_coms_by_pos(mc->users,x,y);
            if (n_com > 0) coms = get_user_coms_by_pos(mc->users,x,y);
            int j=0,tot_user=0;
            while (j < n_com){
                int r_id = get_com_r_by_id(mc->commits,coms[j]);
                char *r_lng = get_repos_lng_by_id(mc->repos,r_id);
                if(strcasecmp(lng,r_lng)==0){
                    tot_user++;
                }
                j++;
                free(r_lng);
            }
            j=0;
            while (j < k)
            {
                if (tot_user>top_n[1][j]){
                    t1=top_n[0][j];
                    t2=top_n[1][j];
                    top_n[0][j]=id;
                    top_n[1][j]=tot_user;
                    id=t1;
                    tot_user=t2;
                }
                j++;   
            }
            if (k < n){
                top_n[0][k]=id;
                top_n[1][k]=tot_user;
                k++;
            }
            y++;
            id=get_id_by_pos(mc->users,x,y);
        }
        free(coms);
    }
    return k;
}

//Devolve a data do ultimo commit efetuado num repo, por sua vez inserido numa determinada posiçao do catalogo
int *check_repos_last_activ_by_position(MCatalog mc,int x,int y){
    return get_repos_last_activ_by_position(mc->repos,x,y);
}

//Devolve o id de um repo inserido numa determinada posiçao do catalogo
int check_repos_id_by_position(MCatalog mc,int x,int y){
    return get_repos_id_by_position(mc->repos,x,y);
}

//Devolve a descriçao de um repo inserido numa determinada posiçao do catalogo
char *check_repos_desc_by_position(MCatalog mc,int x,int y){
    return get_repos_desc_by_position(mc->repos,x,y);
}

//Devolve o id do repo em que o commit, numa determinada posiçao do catalogo, foi efetuado
int check_com_r_id_by_position(MCatalog mc, int x, int y){
    return get_com_r_id_by_position(mc->commits,x,y);
}

//Devolve a linguagem de um repo inserido numa determinada posiçao do catalogo
char *check_repos_lng_by_position(MCatalog mc,int x,int y){
    return get_repos_lng_by_position(mc->repos,x,y);
}

//Devolve a data de um commit numa determinada posiçao do catalogo
int *check_com_date_by_position(MCatalog mc,int x,int y){
    return get_com_date_by_position(mc->commits, x, y);
}

//Dado um determinado id, devolve a linguagem do repo associado a este
char *check_repos_lng_by_id(MCatalog mc,int id){
    return get_repos_lng_by_id(mc->repos,id);
}

//Determina quais os users com mais commits em repositorios cujo dono e seu amigo
int check_u_friend_com(MCatalog mc,int id){
    int tot = 0;
    int ft = get_user_t_fr_by_id(mc->users, id);
    int ct = get_user_t_coms_by_id(mc->users, id);
    if (ft != 0 && ct != 0)
    {
        int *fr = get_user_friends_by_id(mc->users, id);
        int *coms = get_user_coms_by_id(mc->users, id);
        int aux, n = 0, m,r_id;
        while (n < ct){
            r_id = get_com_r_by_id(mc->commits,coms[n]);
            if (r_id>=0){
                aux = get_repo_owner_by_id(mc->repos,r_id);
                if (aux>=0){
                    m = 0;
                    while (m < ft)
                    {
                        if (aux == fr[m])
                        {
                            tot++;
                            m = ft;
                        }
                        m++;
                    }
                }
            }
            n++;
        }
    }
    return tot;
}

//Devolve o id do user associado a um registo numa determinada posiçao do catalogo
int check_user_id_by_pos(MCatalog mc, int x, int y){
    return get_id_by_pos(mc->users,x,y);
}

//Dado um determinado id, devolve o numero de commits efetuado no repo associado a este
int check_repos_n_coms_by_id(MCatalog mc, int id){
    return get_repos_n_coms_by_id(mc->repos,id);
}

//Dado um determinado id, devolve lista de ids de commits dados para o repo associado a este
int *check_repos_coms_by_id(MCatalog mc, int id){
    return get_repos_coms_by_id(mc->repos,id);
}

//Dado um id de procura, devolve o id do user que efetuou o commit
int check_com_u_id(MCatalog mc, int id){
    return get_com_u_by_id(mc->commits,id);
}

//Dado um id de procura, devolve a mensagem associada a um commit
char *check_com_message_by_id(MCatalog mc, int id){
    return get_com_message_by_id(mc->commits,id);
}

//Verifica se existem registos vazios no catalogo dos repos
void clean_repos(MCatalog mc){
    check_empty_repos(mc->repos);
}

//Devolve o numero total de registos de repos validados
int get_n_total_repos(MCatalog mc){
    return check_n_total_repos(mc->repos);
}

//Devolve o numero total de registos de commits validados
int get_n_total_commits(MCatalog mc){
    return check_n_total_commits(mc->commits);
}

//Devolve o numero total de registos de users validados
int get_n_total_users(MCatalog mc){
    return check_n_total_users(mc->users);
}