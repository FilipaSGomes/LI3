/**
 * @file Ficheiro com as várias funções relacionadas à interpretação dos ficheiros de entrada
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intrepeter.h"

//Torna o programa interativo, atraves de um menu. Executa os commandos inseridos pelo utilizador.
int loop (MCatalog database){
    char buf[25];
    int query;
    int flag = 1;
    int n;
    char *d_i = calloc(1, 11), *d_f = calloc(1, 11), *l = calloc(1, 11), *d = calloc(1, 11);
    while (flag){
        query = 100000;
        menu();
        printf( "Insira opção:\n");
        scanf("%s", buf);
        cls();
        if(!isdigit(buf[0])){
            switch (buf[0]){
            case 'R':
            case 'r':
                return 1;
                break;
            case 'H':
            case 'h':
                help();
                break;
            case 'Q':
            case 'q':
                flag=0;
                break;
            default:
                break;
            }
        }
        else query = atoi(buf);
        switch (query) {
            case 0:
                printf("Nome do ficheiro:\n");
                scanf("%s", d);
                interpete_query_file(d,database);
                break;
            case 1:
                query_1(database,NULL);
                break;

            case 2:
                query_2(database,NULL);
                break;

            case 3:
                query_3(database,NULL);
                break;
            
            case 4:
                query_4(database,NULL);
                break;

            case 5:
                printf("Número desejado de users:\n");
                scanf("%d", &n);
                printf("Data início (yyyy-mm-dd):\n");
                scanf("%s", d_i);
                printf("Data fim (yyyy-mm-dd):\n");
                scanf("%s", d_f);
                query_5(database, n, d_i, d_f, NULL);
                loop_pages();
                clean_cache();
                break;
            
            case 6:
                printf("Número desejado de users:\n");
                scanf("%d", &n);
                printf("Linguagem:\n");
                scanf("%s", l);
                query_6(database, n, l, NULL);
                loop_pages();
                clean_cache();
                break;
            
            case 7:
                printf("Data (yyyy-mm-dd):\n");
                scanf("%s", d);
                query_7(database, d, NULL);
                loop_pages();
                clean_cache();
                break;
            
            case 8:
                printf("Número desejado de linguagens:\n");
                scanf("%d", &n);
                printf("Data (yyyy-mm-dd):\n");
                scanf("%s", d);
                query_8(database, n, d, NULL);
                loop_pages();
                clean_cache();
                break;

            case 9:
                printf("Número desejado de utilizadores:\n");
                scanf("%d", &n);
                query_9(database, n, NULL);
                loop_pages();
                clean_cache();
                break;
            
            case 10:
                printf("Número desejado de utilizadores:\n");
                scanf("%d", &n);
                query_10(database, n, NULL);
                loop_pages();
                clean_cache();
                break;
            case 11:
                printf("Número desejado de utilizadores:\n");
                scanf("%d", &n);
                query_11(database, n, NULL);
                loop_pages();
                clean_cache();
                break;
            case 12:
                query_12(database,NULL);
                break;

            case 13:
                query_13(database,NULL);
                break;

            case 14:
                query_14(database,NULL);
                break;
            
            default:
                break;
        }
    }
    return 0;
}

//Conforme a linha de entrada e output da loop, exectua a query pretendida
void do_query_from_line(char *line, MCatalog database ,FILE *o){
    char *token = strtok(line," ");
    int query = verify_int(token),n;
    switch (query){
    case 1:
        query_1(database,o);
        break;
    case 2:
        query_2(database,o);
        break;
    case 3:
        query_3(database,o);
        break;
    case 4:
        query_4(database,o);
        break;
    case 5:
        token=strtok(NULL," ");
        if(token!=NULL){
            n=verify_int(token);
            token = strtok(NULL, " ");
            if(token!=NULL){
                char *d1=strdup(token); 
                token=strtok(NULL," ");
                if(token!=NULL){
                    char *d2 =strdup( token);
                    query_5(database, n, d1, d2,o);
                    free(d2);
                }else{printf("Error Parsing Queue 5");}
                free(d1);
            }else{printf("Error Parsing Queue 5");}
        }else{printf("Error Parsing Queue 5");}
        break;
    case 6:
        token=strtok(NULL," ");
        if(token!=NULL){
            n=verify_int(token);
            token = strtok(NULL, " \n");
            if(token!=NULL){
                char *ln=strdup(token); 
                query_6(database,n,ln,o);
                free(ln);
            }else{printf("Error Parsing Queue 6");}
        }else{printf("Error Parsing Queue 6");}
        break;
    case 7:
        token = strtok(NULL, " ");
        if (token!=NULL){
            char *d3=strdup(token); 
            query_7(database,d3,o);
            free(d3);
        }else{printf("Error Parsing Queue 7");}
        break;
    case 8:
        token=strtok(NULL," ");
        if(token!=NULL){
            n=verify_int(token);
            token = strtok(NULL, " ");
            if(token!=NULL){
                char *d4=strdup(token); 
                query_8(database,n,d4,o);
                free(d4);
            }else{printf("Error Parsing Queue 8");}
        }else{printf("Error Parsing Queue 8");}
        break;
    case 9:
        token = strtok(NULL, " ");
        if (token!=NULL){
            int tp=verify_int(token); 
            query_9(database,tp,o);
        }else{printf("Error Parsing Queue 9");}
        break;
    case 10:
        token = strtok(NULL, " ");
        if (token!=NULL){
            n=verify_int(token); 
            query_10(database,n,o);
        }else{printf("Error Parsing Queue 10");}
        break;
    case 11:
        token = strtok(NULL, " ");
        if (token!=NULL){
            n=verify_int(token); 
            query_11(database,n,o);
        }else{printf("Error Parsing Queue 11");}
        break;
    case 12:
        query_12(database,o);
        break;
    case 13:
        query_13(database,o);
        break;
    case 14:
        query_14(database,o);
        break;
    default:
        printf("Unknown query request!");
        break;
    }
}

//Conforme os comandos existentes no ficheiro de entrada, interepreta-os, executa as queries pretendidas, e escreve os resultados, cada um no seu próprio ficheiro output
void interpete_query_file(char * f_name, MCatalog database){
    FILE *f = fopen(f_name, "r");
    char *tok = strtok(f_name,".");
    char *buff = malloc(sizeof(char) * 500000);
    int n=1; 
    if (f == NULL){
        printf("Error when opening %s! \n", f_name);
    }
    while (fgets(buff, 500000, f)){
        char *out = malloc(sizeof(char)*64);
        strcpy(out,tok);
        char *op=malloc(sizeof(char)*24);
        sprintf(op,"_command%d_output.txt",n);
        strcat(out,op);
        FILE *o = fopen(out,"w");
        char *temp = strdup(buff);
        do_query_from_line(temp,database,o);
        free(temp);
        fclose(o);
        printf("Ficheiro %s gerado!\n",out);
        n++;
    }
    free(buff);
    fclose(f);
}

