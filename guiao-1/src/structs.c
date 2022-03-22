/**
 * @file Ficheiro com as várias funções relacionadas as structs
 */
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exercicio-1.h"
#include "structs.h"
#include <time.h>

int verify_int(char *c){
    int n=-1,l=-1;
    char *s = malloc(sizeof(char)*(strlen(c) + 4));
    strcpy(s,c);
    strcat(s," 1");
    sscanf(s,"%d %d",&n, &l);
    if (l==-1||n<0){n=-1;}
    free(s);
    return n;
}

int verify_type(char *type) {
    int flag = 0;
    if ((strcmp(type, "User")) == 0||(strcmp(type, "Organization")) == 0||(strcmp(type, "Bot")) == 0) flag = 1;
    return flag;
}

int build_date(char *dt, int *data) {
    int j = 0, f = 0;
    struct tm tm2;
    char *tst = calloc(1,sizeof(char) * 25);
    while (dt != NULL && j < 6)
    {
        data[j] = verify_int(dt);
        if (data[j] == -1)
            j = 6;
        j++;
        dt = strtok(NULL, "- :");
    }
    sprintf(tst, "%d-%d-%d %d:%d:%d", data[0], data[1], data[2], data[3], data[4], data[5]);
    if (strptime(tst, "%Y-%m-%d %H:%M:%S", &tm2) == NULL || data[0] < 2005 || data[0] > 2021 || (data[0] == 2005 && data[1] < 4) || (data[0] == 2005 && data[1] == 4 && data[2] < 7) || (data[0] == 2021 && data[1] > 11) || (data[0] == 2021 && data[1] == 11 && data[2] > 10) || j != 6 || dt != NULL){
        f = 1;
    }
    return f;
}
