#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "pagination.h"
#include "utils.h"

//Imprime os resultados da pagina atual
void print_page(int n){
    FILE *cache = fopen("cache.txt", "r");
    long int offset=n*ENTRY_PER_PAGE*81;
    fseek(cache,offset,SEEK_SET);
    char line[81];
    int i=0;
    while(i<2*ENTRY_PER_PAGE && fgets(line,81,cache)){
        printf(("%s"),line);
        i++;
    }
    
    fclose(cache);
}

//Calcula o numero de paginas necessarias para apresentar os resultados, imprime tais paginas e executa os comandos inseridos pelo o utilizador
void loop_pages(){
    FILE *cache=fopen("cache.txt","r");
    char c;
    int line_count=0;
    for (c = getc(cache); c != EOF; c = getc(cache))
        if (c == '\n') 
            line_count = line_count + 1;
    fclose(cache);
    int i = 0,max = (line_count/ENTRY_PER_PAGE);
    while(i>-1){
        cls();
        printf("*~~~~~~~~~~~~~~~~~~~~~~~~~ Page %s / %s ~~~~~~~~~~~~~~~~~~~~~~~~~*\n", max_len_str(9, int_to_str(i + 1)), max_len_str(9, int_to_str(max + 1)));
        print_page(i);
        printf("*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n            P -> Previous    N -> Next   Q -> Quit   # -> Go to page\n");
        char *buf = malloc(sizeof(char) * 16);
        scanf("%s",buf);
        if (isdigit(buf[0])){
            int temp = atoi(buf);
            temp--;
            if (temp<=max && temp >=0) i=temp;
        }else{
            switch (buf[0]){
            case 'P':
            case 'p':
                i--;
                if(i<0)i=max;
                break;
            case 'N':
            case 'n':
                i++;
                if(i>max)i=0;
                break;
            case 'Q':
            case 'q':
                i=-1;
                cls();
                break;
            default:
                break;
            }
        }
        free(buf);
    }
}

//Elimina o ficheiro cache.txt
void clean_cache(){
    remove("cache.txt");
}

/*

LEGACY CODE

typedef struct output {
    int query;
    int id;
    char* string;
    int n;
    int repo;
} *Output;

typedef struct out {
    Output* o;
    int N;
    int used;
} *Out;

void set_query (Output o, int query){
    o->query = query;
}

void set_string (Output o, char* string){
    o->string = strdup(string);
}

void set_id (Output o, int id){
    o->id = id;
}

void set_n (Output o, int n){
    o->n = n;
}

void set_repo (Output o, int repo){
    o->repo = repo;
}

void set_N (Out o, int N){
    o->N = N;
}

void set_used (Out o, int used){
    o->used = used;
}

void set_output (Out o, Output *output){
    o->o = output;
}

int get_query (Output o){
    return o->query;
}

char* get_string (Output o){
    return o->string;
}

int get_id (Output  o){
    return o->id;
}

int get_n (Output o){
    return o->n;
}

int get_repo (Output o){
    return o->repo;
}

int get_N (Out o){
    return o->N;
}

int get_used (Out o){
    return o->used;
}

Output create(int query, int id, char* string, int n, int repo) {
    Output o = malloc(sizeof (struct output));
    set_query(o, query);
    set_id(o, id);
    set_string(o, string);
    set_n(o, n);
    set_repo(o, repo);
    return o;
}

Out init (){
    Out o = malloc(sizeof (struct out));
    set_N(o, 1);
    set_used(o, 0);
    o->o = malloc (sizeof (struct output));
    return o;
}

void push (Output in, Out o){
    if(get_N(o) <= get_used(o)){
        set_N(o, get_N(o)*2);
        o->o = realloc(o->o, get_N(o)*sizeof(struct output));
    }
    Output* send = o->o;
    send[get_used(o)] = in;
    set_used(o, get_used(o)+1);
    set_output(o, send);
   
}

void pop (Out o){
    Output *send = o->o;
    send[get_used(o)] = NULL;
    set_used(o, get_used(o)-1);
}

void print(int cur, Out o){
    Output *arr = o->o;
    cur*=ENTRY_PER_PAGE;
    int id, repo, n;
    for(int i = cur;i<(cur+ENTRY_PER_PAGE) && i < get_used(o);i++){
        id = get_id(arr[i]);
        n = get_n(arr[i]);
        repo = get_repo(arr[i]);
        switch (get_query(arr[i])){
            case 5:
                printf("| %s | %s | %s |\n", max_len_str(16, int_to_str(id)), max_len_str(38,get_string(arr[i])), max_len_str(16, int_to_str(n)));
                break;

            case 6:
                printf("| %s | %s | %s |\n", max_len_str(16, int_to_str(id)), max_len_str(38, get_string(arr[i])), max_len_str(16, int_to_str(n)));
                break;

            case 7:
                printf("| %s | %s |\n", max_len_str(16, int_to_str(repo)), max_len_str(57, get_string(arr[i])));
                break;

            case 8:
                printf("| %s |\n", max_len_str(76, get_string(arr[i])));
                break;

            case 9:
                printf("| %s | %s |\n", max_len_str(16, int_to_str(id)), max_len_str(57,get_string(arr[i])));
                break;

            case 10:
                printf("| %s | %s | %s | %s |\n", max_len_str(16, int_to_str(id)), max_len_str(19,get_string(arr[i])), max_len_str(16, int_to_str(n)), max_len_str(16, int_to_str(repo)));
                break;

            default:
                break;
        }
    }
}

*/
