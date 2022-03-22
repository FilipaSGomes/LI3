/**
 * @file Ficheiro que contêm a função principal do programa relacionado com a execucao dos testes
 */

#include <string.h>
#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#include "meta_catalog.h"
#include "parser.h"
#include "intrepeter.h"

#define TOTAL_TESTS 14

//Compara os resultados obtidos com os esperados, contando o numero de erros
int verify_result(int n, char *out){
    char *op = malloc(sizeof(char) * 64);
    sprintf(op, "testes/quality_tests/expected_outputs/expected_output%d.txt", n);
    FILE *exp = fopen(op, "r");
    FILE *act = fopen(out, "r");
    if (exp==NULL || act==NULL){
        return -1;
    }

    char c1 = getc(exp);
    char c2 = getc(act);
    int errors=0;
    while(c1!=EOF && c2!=EOF && errors==0){
        if(c1!=c2){
            errors++;
        }
        c1=getc(exp);
        c2=getc(act);
    }

    if(errors>0){
        char *ef = malloc(sizeof(char) * 64);
        sprintf(ef, "testes/quality_tests/error_outputs/error_query%d.txt", n);
        char *e = malloc(sizeof(char) * 256);
        sprintf(e, "diff -a --suppress-common-lines -y %s %s > %s", out, op, ef);
        system(e);

        errors=0;

        FILE *efile=fopen(ef,"r");
        char c3;
        for (c3 = getc(efile); c3 != EOF; c3 = getc(efile))
            if (c3 == '\n') // Increment count if this character is newline
                errors = errors + 1;

        fclose(efile);
    }
    free(op);
    fclose(exp);
    fclose(act);
    return errors;
}
//Executa o tipo de testes requisitados pelo o utilizador (controlado por uma flag)
void do_tests(char * f_name, MCatalog database, double *times, int* verf, int flag){
    char* aux;
    aux = strdup(f_name);
    FILE *f = fopen(f_name, "r");
    char *tok = strtok(aux,".");
    char *buff = malloc(sizeof(char) * 500000);
    int n=1;
    double timeused;
    clock_t begin,end;
    if (f == NULL){
        printf("Error when opening %s! \n", f_name);
    }
    while (fgets(buff, 500000, f)){
        char *out = malloc(sizeof(char)*64);
        strcpy(out,tok);
        char *op=malloc(sizeof(char)*24);
        if(flag)
            sprintf(op,"_command%d_qtests.txt",n);
        else
            sprintf(op,"_command%d_ptests.txt",n);
        strcat(out,op);
        FILE *o = fopen(out,"w");
        char *temp = strdup(buff);
        begin = clock();
        do_query_from_line(temp,database,o);
        end = clock();
        timeused = (double)(end - begin) / CLOCKS_PER_SEC;
        fclose(o);
        times[(n-1)] = timeused;
        if(flag)verf[(n-1)]= verify_result(n,out);
        free(temp);
        n++;
        remove(out);
        free(op);
    }
    free(buff);
    fclose(f);
    free(aux);
}

//Calcula o tempo total de execuçao
double get_tot_time(double *res){
    double final=0;
    int i;
    for (i=0;i<TOTAL_TESTS;i++){
        final+= res[i];
    }
    return final;
}

//Imprime os resultados de um teste de performance
void print_test_results_p(double *res,int n, int m){
    while(n<=m && n<TOTAL_TESTS){
        if (res[n] > 0.0){
            if (res[n] < 5.0) {
                printf("| => Query %d\t: Demorou %f segundos a executar!\t                       |\n|      => Executada %f segundos a baixo do tempo util.\t               |\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n", n + 1, res[n], 5.0 - res[n]);
            }else {
                printf("| !! Query %d\t: Demorou %f segundos a executar!\t                       |\n|      !! Executada %f segundos a cima do tempo util.\t                |\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n", n + 1, res[n], res[n] - 5.0);
            }
        }
        n++;
    }     
}

//Imprime os resultados de um teste de qualidade
void print_test_results(double *res, int *verfs,int n, int m){
    while(n<=m && n<TOTAL_TESTS){
        if (res[n] > 0.0){
            if (res[n] < 5.0 && verfs[n]==0) {
                printf("| => Query %d\t: Demorou %f segundos a executar!\t                       |\n|      => Executada %f segundos a baixo do tempo util.\t               |\n|      => Os resultados obtidos correspondem ao esperado.                      |\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n", n + 1, res[n], 5.0 - res[n]);
            }else if (res[n] < 5.0) {
                printf("| => Query %d\t: Demorou %f segundos a executar!\t                       |\n|      => Executada %f segundos a baixo do tempo util.\t               |\n|      !! Os resultados obtidos nao correspondem ao esperado -> ERROS:%s  |\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n", n + 1, res[n], 5.0 - res[n], max_len_str(7, int_to_str(verfs[n])));
            }else if (verfs[n]==0) {
                printf("| => Query %d\t: Demorou %f segundos a executar!\t                       |\n|      !! Executada %f segundos a cima do tempo util.\t                |\n|      => Os resultados obtidos correspondem ao esperado.                      |\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n", n + 1, res[n], 5.0 - res[n]);
            }else {
                printf("| !! Query %d\t: Demorou %f segundos a executar!\t                       |\n|      !! Executada %f segundos a cima do tempo util.\t                |\n|      !! Os resultados obtidos nao correspondem ao esperado -> ERROS:%s  |\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n", n + 1, res[n], res[n] - 5.0, max_len_str(7,int_to_str(verfs[n])));
            }
        }
        n++;
    }     
}
//Executa os testes, calculando o tempo de execuçao e/ou o numero de erros obtidos dos resultados de cada query. No fim, apresenta um menu interativo e executa os comandos inseridos pelo utilizador
void tests(int flag){
    int verifications[TOTAL_TESTS];
    double times[TOTAL_TESTS];
    clock_t begin, end;
    begin = clock();
    MCatalog database = m_cat_init();
    if(flag){
        parse_hash_user(database, "testes/quality_tests/entrada/users.csv");
        parse_hash_repo(database, "testes/quality_tests/entrada/repos.csv");
        parse_hash_comm(database, "testes/quality_tests/entrada/commits.csv");
    }else{
        parse_hash_user(database, "testes/performance_tests/entrada/users.csv");
        parse_hash_repo(database, "testes/performance_tests/entrada/repos.csv");
        parse_hash_comm(database, "testes/performance_tests/entrada/commits.csv");
    }
    clean_repos(database);
    end=clock();
    double timeused = (double)(end - begin) / CLOCKS_PER_SEC;
    if(flag)
        do_tests("testes/quality_tests/quality_tests.txt",database,times, verifications,flag);
    else
        do_tests("testes/performance_tests/performance_tests.txt",database,times, verifications,flag);
    int i = 0, max = TOTAL_TESTS/(4-flag);
    double t_qtime = get_tot_time(times);
    while (i>-1){
        cls();
        printf("*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n|                                                                              |\n|                          TESTES : TEMPO DE EXECUCAO                          |\n|                                                                              |\n");
        printf("*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Page %d / %d ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n| => Boot Time: %f seconds!\t                                       |\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n",i+1, max+1, timeused);
        if(flag)
            print_test_results(times, verifications, i * 3, (i * 3) + 2);
        else
            print_test_results_p(times, i * 4, (i * 4) + 3);
        printf("| => Total Run Time: %f seconds!\t                                       |\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n", timeused+t_qtime);
        printf("            P -> Previous    N -> Next   Q -> Quit   # -> Go to page\n");
        char * buf= malloc(sizeof(char)*16);
        scanf("%s", buf);
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
    free_m_cat(database);
}

//Imprime a secçao de about do programa
void about(){
    cls();
    printf("*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n|                                                                              |\n|                           SOBRE O MODULO DE TESTES                           |\n|                                                                              |\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
    printf("|                                                                              |\n| Este modulo encontra-se dividio em duas seccoes, sendo elas 'Performance' e  |\n| 'Qualidade'. Na primeira o programa e sujeito a uma quantidade de dados mais |\n| mais elevada, de modo a verificar o tempo de boot e de execucao das querys.  |\n| Ja na segunda parte do modulo e testada a 'Qualidade' dos testes. Recorrendo |\n");
    printf("| a uma base de dados menor e controlada, de maneira a assegurar o bom         |\n| funcionamento das querys presentes no programa.                              |\n| Nesta parte, a ocurrencia de um erro de valor '-1' significa a falta do      |\n| ficheiro de verificacao dessa query.                                         |\n|                                                                              |\n");
    printf("| Em ambos os casos podem ser observados os tempos de execucao das querys,     |\n| totais e de tempo de boot dos catalogos                                      |\n|                                                                              |\n|                    (Carregue 'enter' para voltar ao menu)                    |\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
    char enter = 0;
    getchar();
    while (enter != '\r' && enter != '\n'){enter = getchar();}
}

//Funçao principal do modulo de testes
int main(){
    int i=1;
    int ver;
    while(i){
        cls();
        printf("*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n|                                                                              |\n|                                MENU DE TESTES                                |\n|                                                                              |\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
        printf("|                                                                              |\n| 1) Testes de Performance                                                     |\n|                                                                              |\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
        printf("|                                                                              |\n| 2) Testes de Qualidade                                                       |\n|                                                                              |\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
        printf("|                                                                              |\n| 3) Sobre os Testes                                                           |\n|                                                                              |\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
        printf("|                                                                              |\n| 0) Sair                                                                      |\n|                                                                              |\n*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");

        char * buf= malloc(sizeof(char)*16);
        scanf("%s", buf);
        if (isdigit(buf[0])){
            int temp = atoi(buf);
            switch (temp){
            case 1:
                cls();
                FILE *f1 = fopen("testes/performance_tests/entrada/users.csv","r");
                FILE *f2 = fopen("testes/performance_tests/entrada/repos.csv","r");
                FILE *f3 = fopen("testes/performance_tests/entrada/commits.csv","r");
                FILE *f4 = fopen("testes/performance_tests/performance_tests.txt","r");
                if(f1!=NULL&&f2!=NULL&&f3!=NULL&&f4!=NULL){
                    ver=0;
                    fclose(f1);
                    fclose(f2);
                    fclose(f3);
                    fclose(f4);
                }
                else ver=1;
                if (ver){
                    printf("FICHEIROS EM FALTA:\n\nPOR FAVOR VERIFIQUE QUE TODOS OS FICHEIROS ESTAO PRESENTES!!!\n\nFICHEIROS NECESSARIOS:\n\t-> \"testes/performance_tests/entrada/users.csv\"\n\t-> \"testes/performance_tests/entrada/repos.csv\"\n\t-> \"testes/performance_tests/entrada/commits.csv\"\n\t-> \"testes/performance_tests/performance_tests.txt\"\n\nAprenda mais sobre este erro na opcao 'SOBRE'\n\nPressione 'Enter' para continuar...");
                    char enter = 0;
                    getchar();
                    while (enter != '\r' && enter != '\n'){enter = getchar();}
                }else
                    tests(0);
                break;
            case 2:
                cls();
                FILE *f5 = fopen("testes/quality_tests/entrada/users.csv","r");
                FILE *f6 = fopen("testes/quality_tests/entrada/repos.csv","r");
                FILE *f7 = fopen("testes/quality_tests/entrada/commits.csv","r");
                FILE *f8 = fopen("testes/quality_tests/quality_tests.txt","r");
                if(f5!=NULL&&f6!=NULL&&f7!=NULL&&f8!=NULL){
                    ver=0;
                    fclose(f5);
                    fclose(f6);
                    fclose(f7);
                    fclose(f8);
                }
                else ver=1;
                if (ver){
                    printf("FICHEIROS EM FALTA:\n\nPOR FAVOR VERIFIQUE QUE TODOS OS FICHEIROS ESTAO PRESENTES!!!\n\nFICHEIROS NECESSARIOS:\n\t-> \"testes/quality_tests/entrada/users.csv\"\n\t-> \"testes/quality_tests/entrada/repos.csv\"\n\t-> \"testes/quality_tests/entrada/commits.csv\"\n\t-> \"testes/quality_tests/quality_tests.txt\"\n\nAprenda mais sobre este erro na opcao 'SOBRE'\n\nPressione 'Enter' para continuar...");
                    char enter = 0;
                    getchar();
                    while (enter != '\r' && enter != '\n'){enter = getchar();}
                }else
                    tests(1);
                break;
            case 3:
                cls();
                about();
                break;
            case 0:
                i=0;
                cls();
                break;

            default:
                break;
            }
        }
        free(buf);  
    }
    return 0;
}