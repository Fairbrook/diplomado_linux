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

// Length for the char* containing the file permissions
#define permissions_str_len 11
// Length for the char* containing the date string
#define date_str_len 20

char mode_to_type(mode_t);
void mode_to_permissions(mode_t, char*);
unsigned count_alphanumeric(char *);

int main(int argc, char *argv[]){
    // Checks if an argument was provided
    if (argc < 2) {
        fprintf(stderr, "No file path provided\n");
        return EXIT_FAILURE;
    }
    
    // Retrieves the stats from the path and 
    // stops the program in case of error
    struct stat fileInfo;
    char *path = argv[1];
    int stat_exit_value = lstat(path, &fileInfo);
    if(stat_exit_value != EXIT_SUCCESS){
        perror("Error while opening the file");
        return EXIT_FAILURE;
    }

    // Transforms the st_mode to a type character (like ls)
    printf("%c", mode_to_type(fileInfo.st_mode));

    // Transform the st_mode to a ls-like string of permissions
    char permissions[permissions_str_len];
    mode_to_permissions(fileInfo.st_mode, permissions);
    printf("%s",permissions);

    // Gets the corresponding user from the passwords file
    struct passwd *user = getpwuid(fileInfo.st_uid);
    printf(" %s",user->pw_name);
    
    // Gets the corresponding group from the group file
    struct group *group = getgrgid(fileInfo.st_gid);
    printf(" %s", group->gr_name);

    // Prints the size of the file
    printf(" %libytes", fileInfo.st_size);
    printf("\n");

    // Prints the inode number of the file
    printf("inode number: %li\n", fileInfo.st_ino);
    char datestr[date_str_len];

    // Parse and print the time of the last change to inode
    // Note: In standard UNIX there is no such thing as creating time directly
    // in the inode intance so ctime is the best replacement
    struct tm *time = localtime(&fileInfo.st_ctime);
    strftime(datestr, sizeof(datestr), "%02d/%02m/%02Y %H:%M:%S", time);
    printf("Creation (last change to inode): %s\n", datestr);

    // Checks if the file is a regular file, in wich case counts the number
    // of alphanumeric characters and prints the total
    if (S_ISREG(fileInfo.st_mode)){
        unsigned int count = count_alphanumeric(path);
        printf("Alphanumeric characters: %u\n", count);
    }
    return EXIT_SUCCESS;
}

/*
 * Counts the alphanumeric values in the file
 * The function takes as alphanumeric just the ascii characters between A-z and 0-9
 * */
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
    fclose(fd);
    return counter;
}

/*
 * Determines the type of file given a mode_t variable
 * The type of the file is returned as a char in ls-like fashion
 * - regular file
 * d directory
 * c character
 * b block
 * l link
 * p pipe
 * s socket
 * ! unkwon
 * */
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
    if(S_ISFIFO(mode)){
        return 'p';
    }
    if(S_ISSOCK(mode)){
        return 's';
    }
    return '!';
}

/*
 * Transfors the mode_t variable from the file stats into a string of ls-like
 * permissions
 * In the same way ls does, the funcion orders the permissions as follows
 * rwxrwxrwx
 * ─┬─
 *  │ ─┬─
 *  │  │ ─┬─
 *  │  │  └ Other users permissions
 *  │  └ Group permissions
 *  └ User premissions
 *  Where each position corresponds to wrx in that order and a - means the lack 
 *  of that permission
 * */
void mode_to_permissions(mode_t mode, char *buffer){
    // So that the strncat works as expected
    *buffer='\0';
    // Could have done this witha loop but i wanted to use the S_ macros :/
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
