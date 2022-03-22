/**
 * @file Ficheiro que contêm a função principal do programa
 */

#include <string.h>
#include <stdio.h>
#include "catalog_u.h"
#include "catalog_c.h"
#include "catalog_r.h"
#include "stats.h"
#include "parser.h"
#include "intrepeter.h"

//Função principal do guião 2
int main(int argc, char *argv[]){
    if (argc >= 2) {
        CatalogU u;
        CatalogC c;
        CatalogR r;
        GStats s;
        u=cat_u_init();
        c=cat_c_init();
        r=cat_r_init();
        s=init_stats();
        parse_hash_user(u, "entrada/users-g2.csv", s);
        parse_hash_repo(r, "entrada/repos-g2.csv", s);
        parse_hash_comm(c,r,u,"entrada/commits-g2.csv", s);
        int n = 1;
        while (n<argc){
            interpete_query_file(argv[n],u, r, c, s);
            n++;
        }
        free_stats(s);
        free_catalog_u(u);
        free_catalog_c(c);
        free_catalog_r(r);
    } else {
        printf("One argument expected.\n");

    }
    return 0;
}