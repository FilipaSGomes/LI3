#ifndef PAGINATION_H
#define PAGINATION_H

#define ENTRY_PER_PAGE 20

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


/*

Legacy Code

#include <math.h>

void set_query (Output, int);
void set_string (Output, char*);
void set_id (Output, int);
void set_n (Output, int);
void set_repo (Output, int);
void set_N (Out, int);
void set_used (Out, int);
void set_output (Out, Output*);
int get_query (Output);
char* get_string (Output);
int get_id (Output);
int get_n (Output);
int get_repo (Output);
int get_N (Out);
int get_used (Out);
Output* get_output (Out);

Output create(int, int, char*, int, int);
Out init ();
void push (Output, Out );
void pop (Out);
void print(int, Out);

*/

void loop_pages();
void clean_cache();

#endif