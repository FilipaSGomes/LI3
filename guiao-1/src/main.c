/**
 * @file Ficheiro que contêm a função principal do programa
 */
#include <string.h>
#include <stdio.h>
#include "exercicio-1.h"
#include "exercicio-2.h"

/**
 * \brief Função main (função principal do programa)
 *
 * @param int
 * 
 * @param char*
 * 
 * @returns int
 */
int main(int argc, char *argv[]){

    if (argc == 2) {
        if (strcmp(argv[1],"exercicio-1")==0){
            exercicio_1();
        }
        if (strcmp(argv[1],"exercicio-2")==0){
            exercicio_2();
        }  
    } else if (argc > 2) {
        printf("Too many arguments supplied.\n");

    } else {
        printf("One argument expected.\n");

    }
    return 0;
}