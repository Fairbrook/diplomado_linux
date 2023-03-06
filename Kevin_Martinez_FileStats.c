#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>

#define permissions_str_len 11

char mode_to_type(mode_t);
void mode_to_permissions(mode_t, char*);
unsigned count_alphanumeric(char *);

int main(int argc, char *argv[]){
    if (argc <2) {
        fprintf(stderr, "No file path provided\n");
        return EXIT_FAILURE;
    }
    
    struct stat fileInfo;
    char *path = argv[1];
    int exit_value = stat(path, &fileInfo);
    if(exit_value != EXIT_SUCCESS){
        perror("Error while opening the file");
        return EXIT_FAILURE;
    }
    printf("%c", mode_to_type(fileInfo.st_mode));
    char permissions[permissions_str_len];
    mode_to_permissions(fileInfo.st_mode, permissions);
    printf("%s",permissions);
    struct passwd *user = getpwuid(fileInfo.st_uid);
    printf(" %s",user->pw_name);
    struct group *group = getgrgid(fileInfo.st_gid);
    printf(" %s", group->gr_name);
    printf(" %libytes", fileInfo.st_size);
    printf("\n");
    printf("inode number: %li\n", fileInfo.st_ino);
    char datestr[30];
    struct tm *time = localtime(&fileInfo.st_ctime);
    strftime(datestr, sizeof(datestr), "%02d/%02m/%02Y %H:%M:%S", time);
    printf("Creation (last change to inode): %s\n", datestr);
    if (S_ISREG(fileInfo.st_mode) && !(S_IXUSR & fileInfo.st_mode)){
        unsigned int count = count_alphanumeric(path);
        printf("Alphanumeric characters: %u\n", count);
    }
    return EXIT_SUCCESS;
}

unsigned count_alphanumeric(char*path){
    FILE *fd = fopen(path, "r");
    int character = getc(fd);
    unsigned int counter = 0;
    while (character != EOF){
        if((character >= 'A' && character <='Z')||
        (character>='a' && character<='z')||
        (character>='0' && character<='9')){
            counter++;
        }
        character = getc(fd);
    }
    return counter;
}

char mode_to_type(mode_t mode){
    if (S_ISREG(mode)){
        return '-';
    }
    if (S_ISDIR(mode)){
        return 'd';
    }
    if (S_ISCHR(mode)){
        return 'c';
    }
    if (S_ISBLK(mode)){
        return 'b';
    }
    if (S_ISLNK(mode)){
        return 'l';
    }
    return 's';
}

void mode_to_permissions(mode_t mode, char *buffer){
    *buffer='\0';
    char permission='-';
    if (mode & S_IRUSR){
        permission = 'r';
    }
    strncat(buffer, &permission, 1);
    permission='-';
    if (mode & S_IWUSR){
        permission = 'w';
    }
    strncat(buffer, &permission, 1);
    permission='-';
    if (mode & S_IXUSR){
        permission = 'x';
    }
    strncat(buffer, &permission, 1);

    permission='-';
    if (mode & S_IRGRP){
        permission = 'r';
    }
    strncat(buffer, &permission, 1);
    permission='-';
    if (mode & S_IWGRP){
        permission = 'w';
    }
    strncat(buffer, &permission, 1);
    permission='-';
    if (mode & S_IXGRP){
        permission = 'x';
    }
    strncat(buffer, &permission, 1);

    permission='-';
    if (mode & S_IROTH){
        permission = 'r';
    }
    strncat(buffer, &permission, 1);
    permission='-';
    if (mode & S_IWOTH){
        permission = 'w';
    }
    strncat(buffer, &permission, 1);
    permission='-';
    if (mode & S_IXOTH){
        permission = 'x';
    }
    strncat(buffer, &permission, 1);
}