/**
 * @file Ficheiro com as várias funções de utilidade
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"

//Limpa o terminal
void cls(){
    system("@cls||clear");
}

//Transforma um int numa string
char *int_to_str(int x){
    int length = snprintf(NULL, 0, "%d", x);
    char *str = malloc(length + 1);
    snprintf(str, length + 1, "%d", x);
    return str;    
}

char *max_len_str(int f, char *s){
    char *final=malloc(sizeof(char)*(f+1));
    int i;
    for(i=0;i<f;i++){
        final[i]=' ';
    }
    i=0;
    while (*s&&i<f){
        final[i]=*s;
        s++;
        i++;
    }
    if(*s && i==f){
        final[f-1]='.';
        final[f-2]='.';
        final[f-3]='.';
    }
    while(i<f){
        final[i]=' ';
        i++;
    }
    final[f]='\0';
    return final;
}

//Verifica um int de uma string
int verify_int(char *c)
{
     if(c==NULL)return -1;
     int n = -1, l = -1;
     char *s = malloc(sizeof(char) * (strlen(c) + 4));
     strcpy(s, c);
     strcat(s, " 1");
     sscanf(s, "%d %d", &n, &l);
     if (l == -1 || n < 0)
     {
         n = -1;
     }
     free(s);
     return n;
}

//Funçao de hash
size_t hash(const size_t s)
{
    size_t hash = 0;
    hash += s;
    hash = hash % MAX_TABLE;
    return hash;
}

//Verifica uma data
int verify_date(char *dt) {
     int data[6];
     int j = 0, f = 0;
     while (dt != NULL && j < 6)
     {
        data[j] = verify_int(dt);
        if (data[j] == -1)
            j = 6;
        j++;
        dt = strtok(NULL, "- :");
     }
     if ( data[0] < 2005 || data[0] > 2022 || (data[0] == 2005 && data[1] < 4) || (data[0] == 2005 && data[1] == 4 && data[2] < 7) || (data[0] == 2022 && data[1] > 1) || (data[0] == 2021 && data[1] == 1 && data[2] > 23) || j != 6){
        f = 1;
     }
     return f;
}
