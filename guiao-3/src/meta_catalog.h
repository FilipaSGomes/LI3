#ifndef META_CATALOG
#define META_CATALOG

typedef struct meta_catalog *MCatalog;

MCatalog m_cat_init();
void free_m_cat(MCatalog);

void insert_repo_in_db(int,int,char*,char*,int*,MCatalog);
void insert_user_in_db(int,char*,char*,int*,int,MCatalog);
void insert_commit_in_db(int,int,int,int,char*,int*,MCatalog);

int get_total_bot(MCatalog);
int get_total_org(MCatalog);
int get_total_us(MCatalog);
int get_total_contribs(MCatalog);
int get_total_repos(MCatalog);
int get_total_commits(MCatalog);
int get_total_users(MCatalog);
int get_total_bot_repos(MCatalog);

int get_top_u_by_activ(MCatalog, int**, int, int*, int*);
char *check_u_login_by_id(MCatalog, int);
int get_top_u_by_lng(MCatalog,int**,char*,int);
int *check_repos_last_activ_by_position(MCatalog,int,int);
int check_u_friend_com(MCatalog ,int);
int check_repos_id_by_position(MCatalog ,int ,int );
char *check_repos_desc_by_position(MCatalog ,int ,int );
int check_com_r_id_by_position(MCatalog , int , int );
char *check_repos_lng_by_position(MCatalog ,int ,int );
int *check_com_date_by_position(MCatalog, int, int);
char *check_repos_lng_by_id(MCatalog, int);
int check_u_friend_com(MCatalog,int);
int check_user_id_by_pos(MCatalog,int,int);
int check_repos_n_coms_by_id(MCatalog, int);
int *check_repos_coms_by_id(MCatalog, int);
int check_com_u_id(MCatalog, int);
char *check_com_message_by_id(MCatalog, int);

void clean_repos(MCatalog);
int get_n_total_repos(MCatalog);
int get_n_total_commits(MCatalog);
int get_n_total_users(MCatalog);

#endif 