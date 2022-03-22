/**
 * @file Ficheiro que contêm a função principal do programa
 */

#include <string.h>
#include <stdio.h>
#include "meta_catalog.h"
#include "parser.h"
#include "intrepeter.h"

//Função principal do guião 2
int main(int argc, char *argv[]){
    MCatalog database = m_cat_init();
    parse_hash_user(database, "entrada/users-g3.csv");
    parse_hash_repo(database, "entrada/repos-g3.csv");
    parse_hash_comm(database, "entrada/commits-g3.csv");
    clean_repos(database);
    if (argc >= 2) {
        int n = 1;
        while (n<argc){
            interpete_query_file(argv[n],database);
            n++;
        }
    } else {
        while(loop(database)){
            free_m_cat(database);
            database = m_cat_init();
            parse_hash_user(database, "entrada/users-g3.csv");
            parse_hash_repo(database, "entrada/repos-g3.csv");
            parse_hash_comm(database, "entrada/commits-g3.csv");
            clean_repos(database);
        }
    }
    free_m_cat(database);
    return 0;
}