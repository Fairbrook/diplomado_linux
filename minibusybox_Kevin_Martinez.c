#include <stdlib.h>
#include <stdio.h>
#include <libgen.h>
#include <string.h>

int main(int argc, char *argv[]){
    char *basename_dup = strdup(argv[0]);
    char *dirname_dub = strdup(argv[0]);
    char *basename = basename(basename_dup);
    char *dirname = dirname(dirname_dub);
    printf("%s", argv[0]);
} 
