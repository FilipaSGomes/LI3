/**
 * @file Ficheiro com as várias funções relacionadas às queries
 */

#include <stdio.h>
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
    printf ("\n\nGitHub Stats Menu\n\n");
    printf ("+---+-------------------------------------------------------------------------------------+\n");
    printf ("| 1  |  ‌Quantidade ‌‌de ‌‌cada‌‌ tipo ‌‌de‌‌ utilizador‌ ‌                                            |\n");
    printf ("+---+-------------------------------------------------------------------------------------+\n");
    printf ("| 2  |  Número‌‌ médio‌‌ de‌‌ colaboradores‌‌ por‌‌ repositório                                     |\n");
    printf ("+---+-------------------------------------------------------------------------------------+\n");
    printf ("| 3  |  Quantidade‌‌ de‌‌ repositórios‌‌ com‌ bots                                               ‌|\n");
    printf ("+---+-------------------------------------------------------------------------------------+\n");
    printf ("| 4  |  Quantidade‌‌ média‌‌ de‌ c‌ommits‌‌‌ por‌‌ utilizador                                        |\n");
    printf ("+---+-------------------------------------------------------------------------------------+\n");
    printf ("| 5  |  Top‌‌ N‌‌ utilizadores‌‌ mais‌‌ ativos‌‌ num‌‌ determinado‌‌ intervalo‌‌ de‌‌ datas                 |\n");
    printf ("+---+-------------------------------------------------------------------------------------+\n");
    printf ("| 6  |  Top‌‌ N‌‌ utilizadores‌‌ com‌‌ mais‌‌ commits‌‌ em‌‌ repositórios‌‌ de‌‌ uma‌‌ determinada‌‌ linguagem  |\n");
    printf ("+---+-------------------------------------------------------------------------------------+\n");
    printf ("| 7  |  Repositórios‌‌ inativos‌‌ a‌‌ partir‌‌ de‌‌ uma‌‌ determinada‌‌ data                            |\n");
    printf ("+---+-------------------------------------------------------------------------------------+\n");
    printf ("| 8  |  Top‌‌ N‌‌ linguagens‌‌ mais‌‌ utilizadas‌‌ a‌‌ partir‌‌ de‌‌ uma‌‌ determinada‌‌ data                 |\n");
    printf ("+---+-------------------------------------------------------------------------------------+\n");
    printf ("| 9  |  Top‌‌ N‌‌ de‌‌ utilizadores‌‌ com‌‌ mais‌ c‌ommits‌ em‌‌ repositórios‌‌ cujo‌ owner‌‌‌ é‌‌ um‌‌ amigo‌‌ seu ‌ |\n");
    printf ("+---+-------------------------------------------------------------------------------------+\n");
    printf ("| 10 |  Top‌‌ N‌‌ de‌‌ utilizadores‌‌ com‌‌ as‌‌ maiores‌‌ mensagens‌‌ de‌ c‌ommit‌ por‌‌ r‌epositório          |\n");
    printf ("+---+-------------------------------------------------------------------------------------+\n");
    printf ("| M  |  Menu                                                                              |\n");
    printf ("+---+-------------------------------------------------------------------------------------+\n");
    printf ("| Q  |  Quit                                                                              |\n");
    printf ("+---+-------------------------------------------------------------------------------------+\n");

}

//Trata da query 1, utilizando uma struct GStats que contem várias estatistcas sobre os registos
char * query_1 (GStats gs) {
    char *o = malloc(sizeof(char)*64);
    sprintf(o,"Bot : %d; Organization : %d; User : %d", get_type_n(gs,0), get_type_n(gs,1), get_type_n(gs,2));
    return o;
}

//Trata da query 2, utilizando uma struct GStats que contem várias estatistcas sobre os registos
char * query_2 (GStats gs) {
    char *o=malloc(sizeof(char)*8);
    double t_colab = get_t_contribs(gs);
    double t_repos = get_t_repos(gs);
    double x = (t_colab)/(t_repos);
    sprintf(o,"%0.2f", x);
    return o;
}

//Trata da query 3, utilizando uma struct GStats que contem várias estatistcas sobre os registos
char * query_3 (GStats gs) {
    char *o = malloc(sizeof(char) * 12);
    sprintf(o,"%d", get_bot_repos(gs));
    return o;
}

//Trata da query 4, utilizando uma struct GStats que contem várias estatistcas sobre os registos
char * query_4 (GStats gs) {
    char *o = malloc(sizeof(char) * 12);
    double t_commits = get_t_comms(gs);
    double t_users = get_t_users(gs);
    double x = (t_commits)/(t_users);
    sprintf(o,"%0.2f", x);
    return o;
}

//Trata da query 5, utilizando o catálogo de commits(CatalogC), o catálogo de users(CatalogU), o número desejado(int n) e as duas datas desejadas(duas strings/char*)
char * query_5 (CatalogC cc, CatalogU cu, int n, char* date1, char* date2){
    char *o=malloc(sizeof(char)*(n*32));
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
    int top_n[2][n],k=0,t1,t2;
    UEntry ue;
    User u;
    Commit c;
    for(int i=0;i<MAX_TABLE;i++){
        ue=get_user_entry_by_pos(cu,i);
        while(ue!=NULL){
            u=get_entry_user(ue);
            int n_com=get_user_t_coms(u);
            int *coms;
            if(n_com>0)coms=get_user_coms(u);
            int j=0,tot_user=0,id=get_user_id(u);
            while(j<n_com){
                c=get_com_by_id(cc,coms[j]);
                int *d3=get_com_date(c);
                if(((d1[0]<d3[0])||(d1[0]==d3[0] && d1[1]<d3[1])||(d1[0]==d3[0] && d1[1]==d3[1] && d1[2]<d3[2])) && ((d2[0]>d3[0])||(d2[0]==d3[0] && d2[1]>d3[1])||(d2[0]==d3[0] && d2[1]==d3[1] && d2[2]>d3[2]))){
                    tot_user++;
                }
                j++;
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
            ue=get_user_next(ue);
        }
    }
    if (k==0)return NULL;
    for (int g = 0; g<k; g++)
    {

        if(g==0){
            char *temp = malloc(sizeof(char) * (32));
            sprintf(temp,"%d;%s;%d\n",top_n[0][g],check_user_login_by_id(cu,top_n[0][g]),top_n[1][g] );
            strcpy(o,temp); // get_user_coms(u) );
            free(temp);
        } else {
            char *temp = malloc(sizeof(char) * (32));
            sprintf(temp,"%d;%s;%d\n",top_n[0][g],check_user_login_by_id(cu,top_n[0][g]),top_n[1][g]);
            strcat(o,temp); // get_user_coms(u) );
            free(temp);
          }
    }
    return o;
}

//Trata da query 6, utilizando o catálogo de commits(CatalogC), o catálogo de users(CatalogU), o catálogo de repos(CatalogR),o número desejado(int n) e a linguagem pretendida(string/char*)
char * query_6 (CatalogC cc, CatalogU cu, CatalogR cr, int n, char* lng){
    char *o=malloc(sizeof(char)*(n*32));
    int top_n[2][n],k=0,t1,t2;
    UEntry ue;
    User u;
    Commit c;
    for(int i=0;i<MAX_TABLE;i++){
        ue=get_user_entry_by_pos(cu,i);
        while(ue!=NULL){
            u=get_entry_user(ue);
            int n_com=get_user_t_coms(u);
            int *coms;
            if(n_com>0)coms=get_user_coms(u);
            int j=0,tot_user=0,id=get_user_id(u);
            while(j<n_com){
                c=get_com_by_id(cc,coms[j]);
                char *cl=get_repos_language(get_repos_by_id(cr,get_com_r_id(c)));
                //printf("%s<->%s\n",lng,cl);
                if(strcasecmp(lng,cl)==0){
                    tot_user++;
                }
                j++;
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
            ue=get_user_next(ue);
        }
    }
    if (k==0)return NULL;
    for (int g = 0; g<k; g++)
    {

        if(g==0){
            char *temp = malloc(sizeof(char) * (32));
            sprintf(temp,"%d;%s;%d\n",top_n[0][g],check_user_login_by_id(cu,top_n[0][g]),top_n[1][g] );
            strcpy(o,temp); // get_user_coms(u) );
            free(temp);
        } else {
            char *temp = malloc(sizeof(char) * (32));
            sprintf(temp,"%d;%s;%d\n",top_n[0][g],check_user_login_by_id(cu,top_n[0][g]),top_n[1][g]);
            strcat(o,temp); // get_user_coms(u) );
            free(temp);
          }
    }
    return o;
}

//Trata da query 7, o catálogo de repos(CatalogR),e a data desejada(string/char*)
char * query_7 (CatalogR cr, char* date){
    char *o=malloc(sizeof(char)* 1024);
    int n=0,d1[3];
    REntry re;
    Repo r; 
    char * token = strtok(date,"- /");
    d1[0]=verify_int(token);
    token=strtok(NULL, "- /");
    d1[1] = verify_int(token);
    token = strtok(NULL, "- /");
    d1[2] = verify_int(token);

    for (int i = 0; i<MAX_TABLE; i++){
        re = get_repos_by_position(cr, i);
        while (re != NULL) {
            r = get_entry_repos(re);
            int *d3= get_repos_last_commit(r);
            if((d1[0]>d3[0])||(d1[0]==d3[0] && d1[1]>d3[1])||(d1[0]==d3[0] && d1[1]==d3[1] && d1[2]>d3[2])){
                n++;
                char *temp = malloc(sizeof(char) * (32));
                sprintf(temp,"%d;", get_repos_id(r));
                if(n==1){
                    strcpy(o,temp); // get_user_coms(u) );
                }else{
                    o=realloc(o,sizeof(char)*1024*(n+1));
                    strcat(o, temp); // get_user_coms(u) );
                }
                char *tde = get_desc_repo(r);
                strcat(o, tde);
                strcat(o, "\n");
                free(tde);
                free(temp);
            }
            re = get_repos_next(re);
        }
    }
    return o;
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

//Trata da query 8, utilizando o catálogo de commits(CatalogC), o catálogo de repos(CatalogR),o número desejado(int n) e a data desejada(string/char*)
char * query_8 (CatalogC cc,CatalogR cr, int n, char* date){
    char *o = malloc(sizeof(char)*(32*n));
    int dt[3];
    int k=0, j;
    char *token = strtok(date,"- /");
    dt[0]=verify_int(token);
    token=strtok(NULL, "- /");
    dt[1] = verify_int(token);
    token = strtok(NULL, "- /");
    dt[2] = verify_int(token);
    CEntry re;
    Commit r;
    LNG l = malloc(sizeof(struct language));
    
    for (int i = 0; i < MAX_TABLE; i++){
        re = get_com_entry(cc,i);
        while (re != NULL){
            j = 0;
            r = get_entry_commit(re);
            if(compare_dates_2(dt, get_com_date(r)))
            {
                char* lng_r = get_lg_by_id(cr,get_com_r_id(r));
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
            re= get_com_next(re);     
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
    for (int g = p-1; g>=0; g--)
    {

        if(g==p-1){
            char *temp = malloc(sizeof(char) * (32));
            sprintf(temp,"%s\n", result[g].name);
            strcpy(o,temp); // get_user_coms(u) );
            free(temp);
        } else {
            char *temp = malloc(sizeof(char) * (32));
            sprintf(temp,"%s\n", result[g].name);
            strcat(o,temp); // get_user_coms(u) );
            free(temp);
          }
    }
    return o;
}

//Função auxiliar á query 9, que verifica o número total de commits efetuados em repos de amigos de um determinado user
int check_f_com_tot(CatalogC cc, CatalogR cr, User u){
    int tot=0;
    int * fr = get_user_friends(u);
    int * coms = get_user_coms(u);
    if(fr!=NULL && coms!=NULL){
        int ft= get_user_t_fr(u);
        int ct= get_user_t_coms(u);
        int aux,n=0, m;
        while (n<ct){
            Commit c=get_com_by_id(cc,coms[n]);
            if(c!=NULL){
                aux=get_com_r_id(c);
                Repo r=get_repos_by_id(cr,aux);
                if(r!=NULL){
                    aux = get_repos_owner(r);
                    m=0;
                    while(m<ft){
                        if(aux==fr[m]){
                            tot++;
                            m=ft;
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

//Trata da query 9, utilizando o catálogo de users(CatalogU), o catálogo de commits(CatalogC), o catálogo de repos(CatalogR)e o número desejado(int n)
char *query_9(CatalogU cu,CatalogC cc, CatalogR cr, int n){
    char *o = malloc(sizeof(char)*(32*n));
    int k=0, j,id,sz,t1,t2;
    UEntry ue;
    User u;
    int bc[2][n];
    
    for (int i = 0; i < MAX_TABLE; i++){
        ue = get_user_entry_by_pos(cu,i);
        while (ue != NULL){
            j = 0;
            u = get_entry_user(ue);
            id=get_user_id(u);
            sz=check_f_com_tot(cc,cr,u);
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
            ue= get_user_next(ue);
        }
        for (int g = 0; g < k; g++){

            if (g == 0){
                char *temp = malloc(sizeof(char) * (32));
                sprintf(temp, "%d;%s\n",bc[0][g],check_user_login_by_id(cu,bc[0][g]));
                strcpy(o, temp); // get_user_coms(u) );
                free(temp);
            }
            else
            {
                char *temp = malloc(sizeof(char) * (32));
                sprintf(temp, "%d;%s\n", bc[0][g], check_user_login_by_id(cu, bc[0][g]));
                strcat(o, temp); // get_user_coms(u) );
                free(temp);
            }
        }
    }
    return o;
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

//Trata da query 10, utilizando o catálogo de users(CatalogU), o catálogo de commits(CatalogC), o catálogo de repos(CatalogR), o número desejado(int n) e um FILE
char *query_10(CatalogU cu, CatalogC cc, CatalogR cr, int n, FILE *f){
    int k=0, j,id,sz,t1,t2,p;
    char *o = malloc(sizeof(char) * (256 * n));
    REntry re;
    Repo rs;
    Commit r;
    
    for (int i = 0; i < MAX_TABLE; i++){
        re = get_repos_by_position(cr,i);
        while (re != NULL){
            int bc[2][n];
            k = 0;
            rs = get_entry_repos(re);
            int n_com=get_repos_n_coms(rs);
            int *coms;
            if(n_com>0)coms=get_repos_coms(rs);
            p=0;
            while(p<n_com){
                r=get_com_by_id(cc,coms[p]);
                if(cc!=NULL){
                    j=0;
                    id=get_com_u_id(r);
                    char * msg=get_com_message(r);
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
            for (int g = 0; g < k; g++){
                char *temp = malloc(sizeof(char) * (128));
                sprintf(temp, "%d;%s;%d;%d\n", bc[0][g], check_user_login_by_id(cu, bc[0][g]), bc[1][g] - 1, get_repos_id(rs));
                
                if(g==0){
                    strcpy(o,temp);
                }else{
                    strcat(o, temp);
                }
                free(temp);
            }
            if(k<=n)fprintf(f,"%s",o);
            free(coms);
            re= get_repos_next(re);
        }
    }
    return NULL;
}

//Trata da query adicional 11, utilizando o catálogo de users(CatalogU), o catálogo de commits(CatalogC), e o número desejado(int n)
char *query_11(CatalogU cu, CatalogC cc, int n){
    char *o = malloc(sizeof(char)*(32*n));
    int k=0, j,id,sz,t1,t2;
    CEntry re;
    Commit r;
    int bc[2][n];
    
    for (int i = 0; i < MAX_TABLE; i++){
        re = get_com_entry(cc,i);
        while (re != NULL){
            j = 0;
            r = get_entry_commit(re);
            id=get_com_u_id(r);
            char * msg=get_com_message(r);
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
            re= get_com_next(re);
        }
    }

    for (int g = 0; g < k; g++)
    {

        if (g == 0)
        {
            char *temp = malloc(sizeof(char) * (32));
            sprintf(temp, "%d;%s;%d\n", bc[0][g], check_user_login_by_id(cu, bc[0][g]), bc[1][g] - 1);
            strcpy(o, temp); // get_user_coms(u) );
            free(temp);
        }
        else
        {
            char *temp = malloc(sizeof(char) * (32));
            sprintf(temp, "%d;%s;%d\n", bc[0][g], check_user_login_by_id(cu, bc[0][g]), bc[1][g] - 1);
            strcat(o, temp); // get_user_coms(u) );
            free(temp);
        }
    }
    return o;
}