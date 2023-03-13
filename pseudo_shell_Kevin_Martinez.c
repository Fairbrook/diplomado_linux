#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]){
    if(argc<2){
        printf("No input command detected\n");
        return EXIT_FAILURE;
    }
     
}

char **get_extra_args(int argc, char *argv[]){
    int extra_len = argc-2+1;
    char **args = (char**) malloc(extra_len * sizeof(char*));
    int argi = 0;
    for (int i=2;i<argc;i++, argi++){
        args[argi] = argv[i];
    }
    args[argi] = NULL;
    return args;
}

char **append(char *append,int len, char *vector[]){
    char *item = vector[0];
    char **result_vector = (char**) malloc(len+1 *sizeof(char*));
    result_vector[0] = append;
    for (int i=0;i<len;i++){
        result_vector[i+1] = vector[i];
    }
    return result_vector;
}

char** psuedo_to_real(int argc, char *argv[]){
    char *psuedo = argv[1];
    if(strcmp(psuedo, "fecha")==0){
        return append("date", argc-1, get_extra_args(argc,argv));
    }
    if(strcmp(psuedo, "quiensoy")==0){
        return append("whoiam", argc-1, get_extra_args(argc,argv));
    }
    if(strcmp(psuedo, "tiempo")==0){
        return append("uptime", argc-1, get_extra_args(argc,argv));
    }
}
