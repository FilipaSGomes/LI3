/** 
 * @file Ficheiro com as várias invocações às funções relacionadas as structs
 */
#ifndef STRUCTS_H
#define STRUCTS_H 
#define _XOPEN_SOURCE

#define MAX_TABLE 300000

// <========= Structs =========>

/** Contem toda a informaçao do registo de um user*/
typedef struct Users{
	/** id do user */
    int id;
	/** nome de login */
	char *login;
	/** tipo do user */
	char *type;
	/** data de criaçao */
	int c_date[6];
	/** numero de seguidores */
	int followers;
	/** lista de seguidores */
	int *flr_id;
	/** numero de users que segue */
	int following;
	/** lista de users que segue */
	int *flg_id;
	/** numeros de gists publicos */
	int pub_gist;
	/** numero de repos publicos */
	int pub_repo;

}User;

/** Contem toda a informaçao do registo de um commit*/
typedef struct Commits{
	/** id do repo */
    int repo_id;
	/** id do autor */
    int author_id;
	/** id do user que deu commit */
	int committer_id;
	/** data do commit */
	int cmt_date[6];
	/** mensagem do commit */
	char *message;

}Commit;

/** Contem toda a informaçao do registo de um repo*/
typedef struct Repos{
	/** id do commit */
	int cmt_id;
	/** id do dono */
	int owner_id;
	/** nome do repo */
	char *full_name;
	/** nome da licença */
	char *license;
	/** bool -> se tem wiki */
	char *has_wiki;
	/** descriçao do repo */
	char *description;
	/** linguagem do repo */
	char *language;
	/** default branch do repo */
	char *default_branch;
	/** data de criaçao do repo */
	int cr_date[6];
	/** data da ultima atualizaçao do repo */
	int updated_at[6];
	/** numero de forks do repo */
	int forks_count;
	/** numero de open issues do repo */
	int open_issues;
	/** numero de stargazers do repo */
	int stargazers_count;
	/** tamanho do repo */
	int size;

}Repo;

/** Struct para representar users na hashtable*/
typedef struct user_entry{
	int id;
	struct user_entry *next;

}user_entry;

/** Struct para representar repos na hashtable*/
typedef struct repo_entry{
	int id;
	struct repo_entry *next;

}repo_entry;

/** Struct para representar commits na hashtable*/
typedef struct commit_entry{
	int id;
	struct commit_entry *next;

}commit_entry;

/** Representa uma hashtable */
typedef struct hash_table {
	user_entry *users[MAX_TABLE];
	repo_entry *repos[MAX_TABLE];
	commit_entry *commits[MAX_TABLE];

}Hash_table;

/**
 * \brief Verifica se o inteiro é nao negativo, ou seja, se e valido
 * @param char*
 * @returns int
 */
int verify_int(char *);

/**
 * \brief Verifica se o tipo e valido
 * @param char*
 * @returns int
 */
int verify_type(char *);

/**
 * \brief Verifica se a data e valida 
 * @param Commit*
 * @returns int
 */
int build_date(char *dt, int *data);

#endif
