/**
 * @file Ficheiro com as várias funções relacionadas à interpretação dos ficheiros de entrada
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intrepeter.h"


char acOpen[]  = {"\"<{"};
char acClose[] = {"\">}"};

//Divide uma string em vários tokens(strings)
char *strmbtok ( char *input, char *delimit, char *openblock, char *closeblock) {    
    static char *token = NULL;    
    char *lead = NULL;    
    char *block = NULL;    
    int iBlock = 0;    
    int iBlockIndex = 0;    
     
    if ( input != NULL) {    
        token = input;    
        lead = input;    
    }    
    else {    
        lead = token;    
        if ( *token == '\0') {    
            lead = NULL;    
        }    
    }    
     
    while ( *token != '\0') {    
        if ( iBlock) {    
            if ( closeblock[iBlockIndex] == *token) {    
                iBlock = 0;    
            }    
            token++;    
            continue;    
        }    
        if ( ( block = strchr ( openblock, *token)) != NULL) {    
            iBlock = 1;    
            iBlockIndex = block - openblock;    
            token++;    
            continue;    
        }    
        if ( strchr ( delimit, *token) != NULL) {    
            *token = '\0';    
            token++;    
            break;    
        }    
        token++;    
    }    
    return lead;    
}

//Divide uma string no carater "del"
char** split_at(char* string,char* del){
        char ** value = (char **)calloc(1,10 * sizeof(char*));
        for(int i = 0; i < 10; i++) value[i] = (char *)calloc(1,100 * sizeof(char)+1);
        char* tok;
        int i = 0;
        tok = strmbtok ( string, del, acOpen, acClose);    
        strcpy(value[i],tok);    
        i++;    
        while ( ( tok = strmbtok ( NULL, del, acOpen, acClose)) != NULL){
                strcpy(value[i],tok);
                i++;
        }
        return value;
}

//Função que, dependendo da string de entrada, decide qual a query a executar
void loop (CatalogU cu, CatalogR cr, CatalogC cc, GStats gs){
    int flag = 1;
    char line[50];

    while (flag){
        menu();
        scanf("%s", line);
        char*out;
        char** comands = split_at(line," ");
        if( !(strcmp(comands[0], "1"))) out=query_1 (gs);
        if( !(strcmp(comands[0], "2"))) out=query_2 (gs);
        if( !(strcmp(comands[0], "3"))) out=query_3 (gs);
        if( !(strcmp(comands[0], "4"))) out=query_4 (gs);
        if( !(strcmp(comands[0], "5"))) out=query_5 (cc, cu, verify_int(comands[1]), comands[2] ,comands[3]);
        if( !(strcmp(comands[0], "6"))) out=query_6 (cc, cu, cr, verify_int(comands[1]), comands[2]);
        if( !(strcmp(comands[0], "7"))) out=query_7 (cr, comands[1]);
        if( !(strcmp(comands[0], "8"))) out=query_8 (cc, cr, verify_int(comands[1]), comands[2]);
        if( !(strcmp(comands[0], "9"))) out=query_9 (cu,cc,cr,verify_int(comands[1]));
        if( !(strcmp(comands[0], "10"))) out=query_11(cu,cc,verify_int(comands[1]));
        if( !(strcmp(comands[0], "Q"))) flag = 0;
        printf("\n\n\nOutput:\n%s",out);
    }
}

//Conforme a linha de entrada e output da loop, exectua a query pretendida
char *do_query_from_line(char *line, CatalogU u, CatalogR r, CatalogC c, GStats s,FILE *f){
    char *token = strtok(line," ");
    int query = verify_int(token),n;
    char *out;
    switch (query){
    case 0:
        out=strdup("Menu Opened");
        loop(u,r,c,s);
        break;
    case 1:
        out = query_1(s);
        break;
    case 2:
        out = query_2(s);
        break;
    case 3:
        out = query_3(s);
        break;
    case 4:
        out = query_4(s);
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
                    out = query_5(c, u, n, d1, d2);
                }else{out=strdup("Error Parsing Queue 5");}
            }else{out=strdup("Error Parsing Queue 5");}
        }else{out=strdup("Error Parsing Queue 5");}
        break;
    case 6:
        token=strtok(NULL," ");
        if(token!=NULL){
            n=verify_int(token);
            token = strtok(NULL, " \n");
            if(token!=NULL){
                char *ln=strdup(token); 
                out = query_6(c,u,r,n,ln);
            }else{out=strdup("Error Parsing Queue 6");}
        }else{out=strdup("Error Parsing Queue 6");}
        break;
    case 7:
        token = strtok(NULL, " ");
        if (token!=NULL){
            char *d3=strdup(token); 
            out = query_7(r,d3);
        }else{out=strdup("Error Parsing Queue 7");}
        break;
    case 8:
        token=strtok(NULL," ");
        if(token!=NULL){
            n=verify_int(token);
            token = strtok(NULL, " ");
            if(token!=NULL){
                char *d4=strdup(token); 
                out = query_8(c,r,n,d4);
            }else{out=strdup("Error Parsing Queue 8");}
        }else{out=strdup("Error Parsing Queue 8");}
        break;
    case 9:
        token = strtok(NULL, " ");
        if (token!=NULL){
            int tp=verify_int(token); 
            out = query_9(u,c,r,tp);
        }else{out=strdup("Error Parsing Queue 9");}
        break;
    case 10:
        token = strtok(NULL, " ");
        if (token!=NULL){
            n=verify_int(token); 
            out = query_10(u,c,r,n,f);
        }else{out=strdup("Error Parsing Queue 10");}
        break;
    case 11:
        token = strtok(NULL, " ");
        if (token!=NULL){
            n=verify_int(token); 
            out = query_11(u,c,n);
        }else{out=strdup("Error Parsing Queue 11");}
        break;
    default:
        out=strdup("Unable to parse query!");
        break;
    }
    return out;
}

//Conforme os comandos existentes no ficheiro de entrada, interepreta-os, executa as queries pretendidas, e escreve os resultados, cada um no seu próprio ficheiro output
void interpete_query_file(char * f_name, CatalogU u, CatalogR r, CatalogC c,GStats s){
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
        char *line;
        char *temp = strdup(buff);
        line = do_query_from_line(temp,u,r,c,s,o);
        free(temp);
        if(line!=NULL)fprintf(o,"%s",line);
        fclose(o);
        n++;
    }
    free(buff);
    fclose(f);
}
