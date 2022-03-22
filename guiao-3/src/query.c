/**
 * @file Ficheiro com as várias funções relacionadas às queries
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "query.h"


/** Representa o número de vezes que uma linguagem é utilizada nos repos*/
typedef struct language{
    /** nome da linguagem */
    char *name;
    /** número de vezes que é utilizada */
    int count;} *LNG;

//Imprime um menu com as indicações de cada query
void menu (){ //when input command is 0
    cls();
    printf ("+----+-------------------------------------------------------------------------+\n");
    printf ("| G3 |  GitHub Stats Menu                                                      |\n");
    printf ("+----+-------------------------------------------------------------------------+\n");
    printf ("| 0  |  ‌C‌arregar de um ficheiro                                                |\n");
    printf ("| 1  |  ‌Quantidade ‌‌de ‌‌cada‌‌ tipo ‌‌de‌‌ utilizador‌ ‌                                 |\n");
    printf ("| 2  |  Número‌‌ médio‌‌ de‌‌ colaboradores‌‌ por‌‌ repositório                          |\n");
    printf ("| 3  |  Quantidade‌‌ de‌‌ repositórios‌‌ com‌ bots                                    |\n");
    printf ("| 4  |  Quantidade‌‌ média‌‌ de‌ c‌ommits‌‌‌ por‌‌ utilizador                             |\n");
    printf ("| 5  |  Top‌‌ N‌‌ utilizadores‌‌ mais‌‌ ativos‌‌ num‌‌ determinado‌‌ intervalo‌‌ de‌‌ datas      |\n");
    printf ("| 6  |  Top‌‌ N‌‌ utilizadores‌‌ com‌‌ mais‌‌ commits‌‌ de‌‌ uma‌‌ determinada‌‌ linguagem       |\n");
    printf ("| 7  |  Repositórios‌‌ inativos‌‌ a‌‌ partir‌‌ de‌‌ uma‌‌ determinada‌‌ data                 |\n");
    printf ("| 8  |  Top‌‌ N‌‌ linguagens‌‌ mais‌‌ utilizadas‌‌ a‌‌ partir‌‌ de‌‌ uma‌‌ determinada‌‌ data      |\n");
    printf ("| 9  |  Top‌‌ N‌‌ de‌‌ utilizadores‌‌ com‌‌ mais‌ c‌ommits‌ em‌‌ repositórios‌‌ de um‌‌ amigo‌‌ seu |\n");
    printf ("| 10 |  Top‌‌ N‌‌ de‌‌ utilizadores‌‌ com‌‌ as‌‌ maiores‌‌ c‌ommit‌ messages por‌‌ r‌epositório   |\n");
    printf ("| 11 |  Top‌‌ N‌‌ de‌‌ utilizadores‌‌ com‌‌ as‌‌ maiores‌‌ c‌ommit‌ messages                   |\n");
    printf ("| 12 |  Número total de registos de utilizadores válidos                       |\n");
    printf ("| 13 |  Número total de registos de commits válidos                            |\n");
    printf ("| 14 |  Número total de registos de repositórios válidos                       |\n");
    printf ("+----+-------------------------------------------------------------------------+\n");
    printf ("| R  |  Reload Data       | H  | Ajuda               | Q  | Sair               |\n");
    printf ("+----+-------------------------------------------------------------------------+\n");
}

//Imprime a secçao de ajuda do menu
void help(){
    cls();
    printf("*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n|                                                                              |\n|                              SOBRE ESTE PROJETO                              |\n|                                                                              |\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
    printf("| Este projeto foi reslizado no ambito da disciplina de Laboratorios de        |\n| Informatica III pelos alunos do 2o ano de Engenharia Informatica da          |\n| Universidade do Minho:                                                       |\n| -> Filipa Gomes (a96556@uminho.pt)                                           |\n| -> João Loureiro (a97257@uminho.pt)                                          |\n");
    printf("| -> Ricardo Oliveira (a96794@uminho.pt)                                       |\n|                                                                              |\n| Atualmente este projeto apresenta um total de 14 querys bem como a           |\n| capacidade de recarregar os dados em memoria atraves dos ficheiros que se    |\n| encontram na pasta '.entrada/', devendo seguir o formato de '*-g3.csv'.      |\n");
    printf("|                                                                              |\n| Para testar o programa pode-se recorrer ao modulo de testes ('./tests')      |\n| ou ainda utilizar os ficheiros presentes em './testes/samples/'              |\n|                  (Pressione 'enter' para voltar ao menu...)                  |\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
    char enter = 0;
    getchar();
    while (enter != '\r' && enter != '\n'){enter = getchar();}
}

/*
Modelo para output


    if(o==NULL){
        printf("",);
    }else{
        fprintf(o,"",);
    }

*/

//Trata da query 1, utilizando o meta catalogo e um FILE
void query_1 (MCatalog database, FILE *o) {
    int n_bot=get_total_bot(database);
    int n_org=get_total_org(database);
    int n_us=get_total_us(database);
    if(o==NULL){
        printf("*~~~~*\n| 1  |  Bot : %d; Organization : %d; User : %d\n*~~~~*\n", n_bot, n_org, n_us);
        char enter = 0;
        getchar();
        while (enter != '\r' && enter != '\n'){enter = getchar();}
    }else{
        fprintf(o,"Bot : %d; Organization : %d; User : %d",n_bot,n_org,n_us);
    }
}

//Trata da query 2, utilizando o meta catalogo e um FILE
void query_2 (MCatalog database, FILE*o) {
    double t_colab = get_total_contribs(database);
    double t_repos = get_total_repos(database);
    double x = (t_colab)/(t_repos);
    if(o==NULL){
        printf("*~~~~*\n| 2  |  %0.2f Colaboradores por Repositorio\n*~~~~*\n", x);
        char enter = 0;
        getchar();
        while (enter != '\r' && enter != '\n'){enter = getchar();}
    }else{
        fprintf(o,"%0.2f",x);
    }
}

//Trata da query 3, utilizando o meta catalogo e um FILE
void query_3 (MCatalog mc, FILE*o) {
    int n_bot_repos=get_total_bot_repos(mc);
    if(o==NULL){
        printf("*~~~~*\n| 3  |  %d Repositorios com Bots\n*~~~~*\n", n_bot_repos);
        char enter = 0;
        getchar();
        while (enter != '\r' && enter != '\n'){enter = getchar();}
    }else{
        fprintf(o,"%d",n_bot_repos);
    }
}

//Trata da query 4, utilizando o meta catalogo e um FILE
void query_4 (MCatalog mc, FILE *o) {
    double t_commits = get_total_commits(mc);
    double t_users = get_total_users(mc);
    double x = (t_commits)/(t_users);
    if(o==NULL){
        printf("*~~~~*\n| 4  |  %0.2f Commits por Utilizador\n*~~~~*\n", x);
        char enter = 0;
        getchar();
        while (enter != '\r' && enter != '\n'){enter = getchar();}
    }else{
        fprintf(o,"%0.2f",x);
    }
}

//Trata da query 5, utilizando o meta catalogo, o número desejado(int n), as duas datas desejadas(duas strings/char*) e um FILE
void query_5 (MCatalog database, int n, char* date1, char* date2, FILE *O){
    int d1[3],d2[3];
    char*token1=strtok(date1,"- :");
    d1[0]=verify_int(token1);
    token1=strtok(NULL,"- :");
    d1[1]=verify_int(token1);
    token1=strtok(NULL,"- :");
    d1[2]=verify_int(token1);
    char*token2=strtok(date2,"- :");
    d2[0]=verify_int(token2);
    token2=strtok(NULL,"- :");
    d2[1]=verify_int(token2);
    token2=strtok(NULL,"- :");
    d2[2]=verify_int(token2);
    int **top_n=malloc(sizeof(int)*2);
    top_n[0]=malloc(sizeof(int)*n);
    top_n[1]=malloc(sizeof(int)*n);
    int k=get_top_u_by_activ(database, top_n, n,d1,d2);
    if (k>=0){
        if(O==NULL){
            FILE *cache=fopen("cache.txt","w");
            for (int g = 0; g<k; g++)
            {
                fprintf(cache,"| %s | %s | %s |\n", max_len_str(16, int_to_str(top_n[0][g])), max_len_str(38, check_u_login_by_id(database,top_n[0][g])), max_len_str(16, int_to_str(top_n[1][g])));
            }
            fclose(cache);
        }else{
            for (int g = 0; g < k; g++){
                fprintf(O, "%d;%s;%d\n", top_n[0][g], check_u_login_by_id(database, top_n[0][g]), top_n[1][g]);
            }
        }
    }
    free(top_n);
}

//Trata da query 6, utilizando utilizando o meta catalogo ,o número desejado(int n), a linguagem pretendida(string/char*) e um FILE
void query_6 (MCatalog database, int n, char* lng, FILE *O){
    int **top_n=malloc(sizeof(int)*2);
    top_n[0]=malloc(sizeof(int)*n);
    top_n[1]=malloc(sizeof(int)*n);
    int k=get_top_u_by_lng(database,top_n,lng,n);
    if (k>=0){
        if(O==NULL){
            FILE *cache=fopen("cache.txt","w");
            for (int g = 0; g<k; g++){
                fprintf(cache, "| %s | %s | %s |\n", max_len_str(16, int_to_str(top_n[0][g])), max_len_str(38, check_u_login_by_id(database, top_n[0][g])), max_len_str(16, int_to_str(top_n[1][g])));
            }
            fclose(cache);
        } else {
            for (int g = 0; g<k; g++){
                fprintf(O,"%d;%s;%d\n",top_n[0][g],check_u_login_by_id(database,top_n[0][g]),top_n[1][g]);
            }
        }
    }
    free(top_n);
}

//Trata da query 7, utilizando o meta catalogo, a data desejada(string/char*) e um FILE
void query_7 (MCatalog database, char* date, FILE *O){
    int d1[3];
    char * token = strtok(date,"- /");
    d1[0]=verify_int(token);
    token=strtok(NULL, "- /");
    d1[1] = verify_int(token);
    token = strtok(NULL, "- /");
    d1[2] = verify_int(token);

    if(O==NULL){
        FILE *f = fopen("cache.txt","w");
        fclose(f);
    }

    for (int x = 0; x<MAX_TABLE; x++){
        int y=0;
        int *d3 = check_repos_last_activ_by_position(database, x,y);
        while(d3!=NULL){
            if((d1[0]>d3[0])||(d1[0]==d3[0] && d1[1]>d3[1])||(d1[0]==d3[0] && d1[1]==d3[1] && d1[2]>d3[2])){
                if(O==NULL){
                    FILE *cache=fopen("cache.txt","a");
                    fprintf(cache,"| %s | %s |\n", max_len_str(16, int_to_str(check_repos_id_by_position(database, x, y))), max_len_str(57, check_repos_desc_by_position(database,x,y)));
                    fclose(cache);
                }else{
                    fprintf(O,"%d;%s\n",check_repos_id_by_position(database,x,y),check_repos_desc_by_position(database,x,y));
                }
            }
            y++;
            d3 = check_repos_last_activ_by_position(database, x,y);
        }
    }
}

//Função de auxílio para a função quicksort
int partition (LNG arr, int low, int high)
{ 
    int pivot = arr[high].count; // pivot 
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
    struct language l1;
  
    for (int j = low; j <= high - 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if (arr[j].count < pivot) 
        { 
            i++; // increment index of smaller element 
            l1= arr[i];
            arr[i]=arr[j];
            arr[j]=l1;
            //swap(&arr[i], &arr[j]); 
        } 
    }
    l1 = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = l1;
    //swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 

//Aplica o algoritmo de ordenação QuickSort a um array de structs LNG
void quickSort(LNG arr, int low, int high)
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
        at right place */
        int pi = partition(arr, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
}

//Trata da query 8, utilizando o utilizando o meta catalogo ,o número desejado(int n), a data desejada(string/char*) e um FILE
void query_8 (MCatalog database, int n, char* date, FILE* O){
    int d1[3];
    int k=0, j;
    char *token = strtok(date,"- /");
    d1[0]=verify_int(token);
    token=strtok(NULL, "- /");
    d1[1] = verify_int(token);
    token = strtok(NULL, "- /");
    d1[2] = verify_int(token);
    LNG l = NULL;
    for (int x = 0; x < MAX_TABLE; x++){
        int y=0;
        int id=check_com_r_id_by_position(database,x,y);
        int *d3=check_com_date_by_position(database,x,y);
        while(d3!=NULL){
            j = 0;
            if ((d1[0] < d3[0]) || (d1[0] == d3[0] && d1[1] < d3[1]) || (d1[0] == d3[0] && d1[1] == d3[1] && d1[2] < d3[2]))
            {
                char *lng_r = check_repos_lng_by_id(database, id);
                while (j < k)
                {
                    if ((strcasecmp(l[j].name, lng_r)) == 0)
                    {
                        l[j].count++;
                        j = k + 1;
                    }
                    j++;   
                }
                if (j != k+2) {
                    l = realloc(l,(sizeof(struct language))*(k+1));
                    l[j].name =strdup(lng_r);
                    l[j].count = 1;
                    k++;
                }
                free(lng_r);
            }
            d3 = check_com_date_by_position(database, x, y);
            id=check_com_r_id_by_position(database,x,y);
            y++;
        }
    }
    
    LNG result = malloc(sizeof(struct language)*n);
    j = 0;
    int p = 0,q;
    struct language temp;
    while (j < k)
    {
        q = 0;
        if (p<n) {
            result[p] = l[j];
            p++;
        }
        else {
            while (q < n)
            {
                if (result[q].count < l[j].count) {
                    temp = result[q];
                    result[q] = l[j];
                    l[j] = temp;
                }
                q++;
            } 
        }
        j++;
    }
    quickSort(result,0,(p-1));
    
    if(O==NULL){
        FILE *cache=fopen("cache.txt","w");
        for (int g = p-1; g>=0; g--){
            fprintf(cache,"| %s |\n", max_len_str(76, result[g].name));
        }
        fclose(cache);
    }else{
        for (int g = p-1; g>=0; g--){
            fprintf(O,"%s\n",result[g].name);
        }
    }
    free(l);
    free(result);
}

//Trata da query 9, utilizando utilizando o meta catalogo, o número desejado(int n) e um FILE
void query_9(MCatalog database, int n, FILE *O){
    int k=0, j,sz,t1,t2;
    int bc[2][n];
    
    for (int x = 0; x < MAX_TABLE; x++){
        int y=0;
        int id=check_user_id_by_pos(database,x,y);
        while(id>=0){       
            j=0;
            sz=check_u_friend_com(database,id);
            while (j < k && id!=bc[0][j])
            {
                if (sz>bc[1][j]){
                    t1=bc[0][j];
                    t2=bc[1][j];
                    bc[0][j]=id;
                    bc[1][j]=sz;
                    id=t1;
                    sz=t2;
                }
                j++;   
            }
            if (k < n && id!=bc[0][j]){
                bc[0][k]=id;
                bc[1][k]=sz;
                k++;
            }
            id=check_user_id_by_pos(database,x,y);
            y++;
        }
    }

    if(O==NULL){
        FILE *cache=fopen("cache.txt","w");
        for (int g = 0; g < k; g++){
            fprintf(cache,"| %s | %s |\n", max_len_str(16, int_to_str(bc[0][g])), max_len_str(57, check_u_login_by_id(database, bc[0][g])));
        }
        fclose(cache);
    }else{
        for (int g = 0; g < k; g++){
            fprintf(O,"%d;%s\n",bc[0][g],check_u_login_by_id(database,bc[0][g]));
        }
    }
}

//Função auxliar que devolve o tamanho de uma const char
int utf8_strlen(const char *s) // fonte: https://stackoverflow.com/questions/32936646/getting-the-string-length-on-utf-8-in-c
{
    int count = 0;
    while (*s)
    {
        count += (*s++ & 0xC0) != 0x80;
    }
    return count;
}

//Trata da query 10, utilizando o utilizando o meta catalogo, o número desejado(int n) e um FILE
void query_10(MCatalog database, int n, FILE *O){
    if(O==NULL){
        FILE *f=fopen("cache.txt","w");
        fclose(f);
    }
    int k=0, j,sz,t1,t2,p;
    for (int x = 0; x < MAX_TABLE; x++){
        int y=0;
        int r_id = check_repos_id_by_position(database,x,y);
        while (r_id>=0){
            int bc[2][n];
            k = 0;
            int n_com=check_repos_n_coms_by_id(database,r_id);
            int *coms;
            coms=NULL;
            if(n_com>0)coms=check_repos_coms_by_id(database,r_id);
            p=0;
            while(p<n_com){
                int id=check_com_u_id(database,coms[p]);
                if(id>=0){
                    j=0;
                    char * msg=check_com_message_by_id(database,coms[p]);
                    sz=utf8_strlen(msg);
                    while (j < k)
                    {
                        if (sz>bc[1][j]){
                            t1=bc[0][j];
                            t2=bc[1][j];
                            bc[0][j]=id;
                            bc[1][j]=sz;
                            id=t1;
                            sz=t2;
                        }
                        j++;   
                    }
                    if (k < n){
                        bc[0][k]=id;
                        bc[1][k]=sz;
                        k++;
                    }
                }
                p++;
            }
            
            if(O==NULL){
                FILE *cache=fopen("cache.txt","a");
                for (int g = 0; g < k; g++){
                    fprintf(cache,"| %s | %s | %s | %s |\n", max_len_str(16, int_to_str(bc[0][g])), max_len_str(19, check_u_login_by_id(database, bc[0][g])), max_len_str(16, int_to_str(bc[1][g] - 1)), max_len_str(16, int_to_str(r_id)));
                }
                fclose(cache);
            }else{
                for (int g = 0; g < k; g++){
                    fprintf(O, "%d;%s;%d;%d\n", bc[0][g], check_u_login_by_id(database, bc[0][g]), bc[1][g] - 1, r_id);
                }
            }
            free(coms);
            y++;
            r_id = check_repos_id_by_position(database, x, y);
        }
    }
}

//Trata da query adicional 11, utilizando o meta catalogo, o número desejado(int n) e um FILE
void query_11(MCatalog database, int n, FILE *O){
    int k=0, p,j,sz,t1,t2;
    int bc[2][n];
    
    for (int x = 0; x < MAX_TABLE; x++){
        int y = 0;
        int r_id = check_repos_id_by_position(database, x, y);
        while (r_id >=0){
            int n_com=check_repos_n_coms_by_id(database,r_id);
            int *coms;
            coms=NULL;
            if(n_com>0)coms=check_repos_coms_by_id(database,r_id);
            p=0;
            while(p<n_com){
                int id=check_com_u_id(database,coms[p]);
                if(id>=0){
                    j=0;
                    char * msg=check_com_message_by_id(database,coms[p]);
                    sz=utf8_strlen(msg);
                    while (j < k)
                    {
                        if (sz>bc[1][j]){
                            t1=bc[0][j];
                            t2=bc[1][j];
                            bc[0][j]=id;
                            bc[1][j]=sz;
                            id=t1;
                            sz=t2;
                        }
                        j++;   
                    }
                    if (k < n){
                        bc[0][k]=id;
                        bc[1][k]=sz;
                        k++;
                    }
                    free(msg);
                }
                p++;
            }
            free(coms);
            y++;
            r_id = check_repos_id_by_position(database, x, y);
        }
    }

    if(O==NULL){
        FILE *cache=fopen("cache.txt","w");
        for (int g = 0; g < k; g++){
            fprintf(cache,"| %s | %s | %s |\n", max_len_str(16, int_to_str(bc[0][g])), max_len_str(38, check_u_login_by_id(database, bc[0][g])), max_len_str(16, int_to_str(bc[1][g] - 1)));
        }
        fclose(cache);
    }else{
        for (int g = 0; g < k; g++){
            fprintf(O, "%d;%s;%d\n", bc[0][g], check_u_login_by_id(database, bc[0][g]), bc[1][g] - 1);
        }
    }
}

//Trata da query 12, utilizando o meta catalogo e um FILE
void query_12 (MCatalog database, FILE *o) {
    int tot=get_n_total_users(database);
    if(o==NULL){
        printf("*~~~~*\n| 12 |  %d Utilizadores Validos\n*~~~~*\n", tot);
        char enter = 0;
        getchar();
        while (enter != '\r' && enter != '\n'){enter = getchar();}
    }else{
        fprintf(o,"Total Valid Users: %d",tot);
    }
}

//Trata da query 13, utilizando o meta catalogo e um FILE
void query_13 (MCatalog database, FILE *o) {
    int tot=get_n_total_commits(database);
    if(o==NULL){
        printf("*~~~~*\n| 13 |  %d Commits Validos\n*~~~~*\n", tot);
        char enter = 0;
        getchar();
        while (enter != '\r' && enter != '\n'){enter = getchar();}
    }else{
        fprintf(o,"Total Valid Commits: %d",tot);
    }
}

//Trata da query 14, utilizando o meta catalogo e um FILE
void query_14 (MCatalog database, FILE *o) {
    int tot=get_n_total_repos(database);
    if(o==NULL){
        printf("*~~~~*\n| 14 |  %d Repos Validos\n*~~~~*\n", tot);
        char enter = 0;
        getchar();
        while (enter != '\r' && enter != '\n'){enter = getchar();}
    }else{
        fprintf(o,"Total Valid Repos: %d",tot);
    }
}