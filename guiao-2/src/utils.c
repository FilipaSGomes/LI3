/**
 * @file Ficheiro com as várias funções de utilidade
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"

size_t long_size(char* s){
	size_t i = 0;
	while(s[i++]!='\0');
	i+=1;
	return i;
}

//Modifica uma string para a sua versão minuscula (lowercase)
char* toLow(char* s){
	char * out = malloc(sizeof(char)*long_size(s)+1);
	int i=0;
	while(s[i]){
		out[i] = tolower(s[i]);
		i++;
	}
	return out;
}

//Verifica um int de uma string
int verify_int(char *c)
{
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

//Dada um data no formato string(char*), "transforma-a" numa data no formato de uma lista de int
void build_dt(char *dt, int *data) {
    int j = 0;
    while (dt != NULL && j < 3)
    {
        data[j] = verify_int(dt);
        if (data[j] == -1)
            j = 3;
        j++;
        dt = strtok(NULL, "- :");
    }
}

//Compara 3 datas
int compare_dates (int d1[3], int d2[3], int d3[3]){
    if ((d3[0] > d1[0] && d3[0] > d2[0]) || (d3[0] < d1[0] && d3[0] < d2[0]))
       return 0;

    else if ((d3[0] < d1[0] && d3[0] > d2[0]) || (d3[0] > d1[0] && d3[0] < d2[0]))
       return 1;

    if (d3[0] == d1[0] && d3[0] > d2[0]){
         if (d3[1]>d1[1])
              return 0;
         else if (d1[1]>d3[1])
              return 1;
         else if (d3[2]>d1[2])
              return 0;
         else if (d3[2]<d1[2])
              return 1;
         else
              return 0;
    }
    if (d3[0] == d2[0] && d3[0] > d1[0]){
         if (d3[1]>d2[1])
              return 0;
         else if (d2[1]>d3[1])
              return 1;
         else if (d3[2]>d2[2])
              return 0;
         else if (d3[2]<d2[2])
              return 1;
         else
              return 0;
    }
    return -500;
}

//Compara 2 datas
int compare_dates_2 (int d1[3], int d2[3]){
    if (d1[0]>d2[0])
       return 0;

    else if (d1[0]<d2[0])
       return 1;

    if (d1[0]==d2[0]){
         if (d2[1]>d1[1])
              return 1;
         else if (d1[1]>d2[1])
              return 0;
         else if (d2[2]>d1[2])
              return 1;
         else
              return 0;
    }
    return -500;
}

//Devolve os n ids mais frequentes
int* max_n_freq (int n, int* ids, int N) { ///retorna os n ids mais frequentes
     int fr[N];
     int *max_n=malloc(sizeof(int)*n);    
     int a = 0;
     int visited = -1;    
          
     for(int i = 0; i < N; i++){    
          int count = 1;    
          for(int j = i+1; j < N; j++){    
               if(ids[i] == ids[j]){    
                    count++;    
                    //Para evitar contar o mesmo elemento outra vez  
                    fr[j] = visited;    
               }    
          }    
          if(fr[i] != visited)    
               fr[i] = count;    
     }

     // storing the largest number to arr[0]
     for(int j = 0; j < n; j++) {
          for (int i = 0; i < N; ++i) {
               if (fr[i] > fr[i+1]) {
                    max_n[j] = fr[i];
                    a = i;
               }
          }
          N--;
          for (int k = a; k < n; k++){
               fr[k] = fr[k + 1];
          }
     }
     return max_n;
}

size_t hash(const size_t s)
{
    size_t hash = 0;
    hash = s;
    hash = hash % MAX_TABLE;
    return hash;
}
