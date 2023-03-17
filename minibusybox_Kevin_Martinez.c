#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define EXIT_NOT_FOUND 404

int cp(int, char *[]);
int command_executor(char *, int, char *[]);
int is_file(char *);
int is_dir(char *);
int copy_file(char *, char *);
int cp_file(char *, char *);
int is_dir_empty(char *);
int parent_is_dir(char *);
int get_mode(char *);
int cp_dir(char *, char *);
int custom_sleep(int, char **);
int ls(int, char **);
int cat(int, char **);
int custom_mkdir(int, char **);
char *concat_path(char *, char *);

int main(int argc, char *argv[]) {
  char *basename_dup = strdup(argv[0]);
  char *command = basename(basename_dup);
  char **arguments = argv;
  int arg_counter = argc;
  if (argc > 1 && strcmp("-", argv[1]) == 0) {
    arg_counter -= 2;
    arguments = &argv[2];
    command = argv[2];
  }
  int command_return = command_executor(command, arg_counter, arguments);
  int command_error = errno;
  free(basename_dup);
  if (command_return == EXIT_NOT_FOUND) {
    printf("Invalid command\n");
    return EXIT_FAILURE;
  }
  if (command_return != EXIT_SUCCESS) {
    errno = command_error;
    perror("Error");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int command_executor(char *command, int argc, char *argv[]) {
  if (strcmp("cp", command) == 0) {
    return cp(argc, argv);
  }
  if (strcmp("sleep", command) == 0) {
    return custom_sleep(argc, argv);
  }
  if (strcmp("ls", command) == 0) {
    return ls(argc, argv);
  }
  if (strcmp("cat", command) == 0) {
    return cat(argc, argv);
  }
  if (strcmp("mkdir", command) == 0) {
    return custom_mkdir(argc, argv);
  }
  return EXIT_NOT_FOUND;
}

int cp(int argc, char *argv[]) {
  int r_option = strcmp("-r", argv[1]) == 0;
  if (argc < 3 || argc > 4 || (argc == 4 && !r_option)) {
    errno = EINVAL;
    return EXIT_FAILURE;
  }
  if (r_option) {
    return cp_dir(argv[2], argv[3]);
  }
  return cp_file(argv[1], argv[2]);
}

int custom_sleep(int argc, char *argv[]) {
  if (argc != 2) {
    errno = EINVAL;
    return EXIT_FAILURE;
  }
  errno = 0;
  char *rest;
  int seconds = strtol(argv[1], &rest, 10);
  if (errno != 0) {
    return EXIT_FAILURE;
  }
  if (rest != NULL && rest[0] != '\0') {
    errno = EINVAL;
    return EXIT_FAILURE;
  }
  sleep(seconds);
  return EXIT_SUCCESS;
}

int ls(int argc, char *argv[]) {
  char *source = ".";
  if (argc > 2) {
    errno = EINVAL;
    return EXIT_FAILURE;
  }
  if (argc == 2) {
    source = argv[1];
  }
  int is_source_dist = is_dir(source);
  if (is_source_dist == -1) {
    return EXIT_FAILURE;
  }
  if (is_source_dist == 0) {
    errno = ENOTDIR;
    return EXIT_FAILURE;
  }
  DIR *dir = opendir(source);
  struct dirent *file;
  while ((file = readdir(dir)) != NULL) {
    if (strcmp(".", file->d_name) == 0 || strcmp("..", file->d_name) == 0) {
      continue;
    }
    printf("%s\n", file->d_name);
  }
  return EXIT_SUCCESS;
}

int cat(int argc, char *argv[]) {
  if (argc != 2) {
    errno = EINVAL;
    return EXIT_FAILURE;
  }
  char *input = argv[1];
  int is_input_file = is_file(input);
  if (is_input_file == -1) {
    return EXIT_FAILURE;
  }
  if (is_input_file == 0) {
    errno = ENOENT;
    return EXIT_FAILURE;
  }
  char buffer[4096];
  FILE *finput = fopen(input, "r");
  if (finput == NULL) {
    return EXIT_FAILURE;
  }
  while (feof(finput) == 0) {
    fread(buffer, sizeof(char), sizeof(buffer), finput);
    printf("%s", buffer);
  }
  fclose(finput);
  return EXIT_SUCCESS;
}

int custom_mkdir(int argc, char *argv[]) {
  if (argc != 2) {
    errno = EINVAL;
    return EXIT_FAILURE;
  }
  char *input = argv[1];
  int is_input_dir = is_dir(input);
  if (is_input_dir == 0) {
    return EXIT_SUCCESS;
  }
  char *path_dup = strdup(input);
  char *parent = dirname(path_dup);
  int is_parent_dir = is_dir(parent);
  mode_t parent_mode = get_mode(parent);
  free(path_dup);
  if (is_parent_dir == -1) {
    return EXIT_FAILURE;
  }
  if (is_parent_dir == 0) {
    errno = ENOENT;
    return EXIT_FAILURE;
  }
  return mkdir(input, parent_mode);
}

int cp_dir(char *source, char *dest) {
  int source_is_dir = is_dir(source);
  if (source_is_dir == -1) {
    return EXIT_FAILURE;
  }
  if (source_is_dir == 0) {
    errno = ENOTDIR;
    return EXIT_FAILURE;
  }
  int dest_is_dir = is_dir(dest);
  if (dest_is_dir == 1) {
    if (is_dir_empty(dest) == 0) {
      errno = ENOTEMPTY;
      return EXIT_FAILURE;
    }
  }
  if (dest_is_dir == -1) {
    if (parent_is_dir(dest) != 1) {
      return EXIT_FAILURE;
    }
    if (mkdir(dest, get_mode(source)) == -1) {
      return EXIT_FAILURE;
    }
  }

  DIR *dir = opendir(source);
  struct dirent *file;
  while ((file = readdir(dir)) != NULL) {
    if (strcmp(".", file->d_name) == 0 || strcmp("..", file->d_name) == 0) {
      continue;
    }
    int cp_return = 0;
    int cp_error = 0;
    char *full_path = concat_path(source, file->d_name);
    if (file->d_type == DT_DIR) {
      char *dest_with_folder = concat_path(dest, file->d_name);
      cp_return = cp_dir(full_path, dest_with_folder);
      cp_error = errno;
      free(dest_with_folder);
    } else {
      cp_return = cp_file(full_path, dest);
      cp_error = errno;
    }
    free(full_path);
    if (cp_return == EXIT_FAILURE) {
      errno = cp_error;
      return cp_return;
    }
  }
  closedir(dir);
  return EXIT_SUCCESS;
}

int cp_file(char *source, char *dest) {
  int source_is_file = is_file(source);
  if (source_is_file == -1) {
    return EXIT_FAILURE;
  }
  if (source_is_file == 0) {
    errno = EISDIR;
    return EXIT_FAILURE;
  }
  int dest_is_dir = is_dir(dest);
  if (dest_is_dir == -1) {
    if (parent_is_dir(dest) != 1) {
      return EXIT_FAILURE;
    }
  }
  if (dest_is_dir == 1) {
    char *file_dup = strdup(source);
    char *file_name = basename(file_dup);
    char *full_path = concat_path(dest, file_name);
    free(file_dup);
    int copy_return = copy_file(source, full_path);
    int copy_errno = errno;
    free(full_path);
    errno = copy_errno;
    return copy_return;
  }
  return copy_file(source, dest);
}

int copy_file(char *source, char *dest) {
  char buffer[4096];
  FILE *fsource = fopen(source, "r");
  if (fsource == NULL) {
    return EXIT_FAILURE;
  }
  FILE *fdest = fopen(dest, "w");
  if (fdest == NULL) {
    return EXIT_FAILURE;
  }
  while (feof(fsource) == 0) {
    size_t written = fread(buffer, sizeof(char), sizeof(buffer), fsource);
    fwrite(buffer, sizeof(char), written, fdest);
  }
  fclose(fsource);
  fclose(fdest);
  struct stat source_stat;
  stat(source, &source_stat);
  chmod(dest, source_stat.st_mode);
  chown(dest, source_stat.st_uid, source_stat.st_gid);
  return EXIT_SUCCESS;
}

int get_mode(char *path) {
  struct stat file_stat;
  if (stat(path, &file_stat) == -1) {
    return -1;
  }
  return file_stat.st_mode;
}

int is_file(char *path) {
  struct stat file_stat;
  if (lstat(path, &file_stat) == -1) {
    return -1;
  }
  if (S_ISREG(file_stat.st_mode) || S_ISBLK(file_stat.st_mode) ||
      S_ISCHR(file_stat.st_mode) || S_ISFIFO(file_stat.st_mode) ||
      S_ISLNK(file_stat.st_mode)) {
    return 1;
  }
  return 0;
}

int is_dir(char *path) {
  struct stat file_stat;
  if (lstat(path, &file_stat) == -1) {
    return -1;
  }
  if (S_ISDIR(file_stat.st_mode)) {
    return 1;
  }
  return 0;
}

int is_dir_empty(char *path) {
  struct dirent *file;
  DIR *dir = opendir(path);
  readdir(dir);
  readdir(dir);
  if (readdir(dir) != NULL) {
    closedir(dir);
    return 0;
  }
  closedir(dir);
  return 1;
}

int parent_is_dir(char *path) {
  char *dir_dup = strdup(path);
  char *dir_name = dirname(dir_dup);
  int dir_name_is_dir = is_dir(dir_name);
  free(dir_dup);
  return dir_name_is_dir;
}

char *concat_path(char *path_a, char *path_b) {
  long dir_len = strlen(path_a);
  long base_len = strlen(path_b);
  char *full_path = malloc((dir_len + base_len + 2) * sizeof(char));
  full_path[0] = '\0';
  strcat(full_path, path_a);
  full_path[dir_len] = '/';
  full_path[dir_len + 1] = '\0';
  strcat(full_path, path_b);
  return full_path;
}
