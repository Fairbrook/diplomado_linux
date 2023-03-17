#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
char** psuedo_to_real(int, char *[]);

int main(int argc, char *argv[]){
    if(argc<2){
        printf("No input command detected\n");
        return EXIT_FAILURE;
    }
    char **command = psuedo_to_real(argc, argv);
    if(command[0]==NULL){
        printf("Invalid command '%s'\n", argv[1]);
        printf("Try fecha, quiensoy, tiempo or personal\n");
        return EXIT_FAILURE;
    }
    int pid = fork();
    if(pid!=0){
        int child_status;
        waitpid(pid, &child_status, 0);
        return child_status;
    }
    int exec_return = execvp(command[0], command);
    if(exec_return == -1){
        perror("Error al ejecutar el comando");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

char **allocate_array(unsigned int len){
    char **array = (char**)malloc(len);
    for(int i=0;i<len;i++){
        array[i] = NULL;
    }
    return array;
}

char** psuedo_to_real(int argc, char *argv[]){
    char *psuedo = argv[1];
    if(strcmp(psuedo, "fecha")==0){
        char **date = allocate_array(2);
        date[0] = "date";
        return date;
    }
    if(strcmp(psuedo, "quiensoy")==0){
        char **whoami = allocate_array(2);
        whoami[0] = "whoami";
        return whoami;
    }
    if(strcmp(psuedo, "tiempo")==0){
        char **uptime = allocate_array(3);
        uptime[0] = "uptime";
        uptime[1] = "-p";
        return uptime;
    }
    if(strcmp(psuedo, "personal")==0){
        char **personal = allocate_array(3);
        personal[0] = "./out/Kevin_Martinez_FileStats";
        personal[1] = "./brun.sh";
        return personal;
    }
    return allocate_array(1);
}
