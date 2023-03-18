#include <dirent.h>
#include <errno.h>
#include <grp.h>
#include <libgen.h>
#include <pwd.h>
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
int cp_link(char *, char *);
int is_dir_empty(char *);
int parent_is_dir(char *);
int get_mode(char *);
int cp_dir(char *, char *);
int custom_sleep(int, char **);
int ls(int, char **);
int cat(int, char **);
int custom_mkdir(int, char **);
int custom_chown(int, char **);
char *concat_path(char *, char *);

int main(int argc, char *argv[]) {
  // Retrieves the basename of the invocation path
  // I dup the string according to the basename documentation
  char *basename_dup = strdup(argv[0]);
  char *command = basename(basename_dup);
  char **arguments = argv;
  int arg_counter = argc;

  // I can bypass the path name passing a - as the first argument
  // So i dont need to make the symlink to test
  if (argc > 1 && strcmp("-", argv[1]) == 0) {
    arg_counter -= 2;
    arguments = &argv[2];
    command = argv[2];
  }

  // Finds the command to execute and runs it
  int command_return = command_executor(command, arg_counter, arguments);
  int command_error = errno;

  // We can finally free the path dup
  free(basename_dup);
  // If no command matched the call
  if (command_return == EXIT_NOT_FOUND) {
    printf("Invalid command\n");
    return EXIT_FAILURE;
  }

  // Handle the command error
  if (command_return != EXIT_SUCCESS) {
    errno = command_error;
    perror("Error");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

// Compares the given first argument as the name of the command
// And finds a match with the supported commands
// If finds it, call the corresponding function with the argc
// and argv as if it was the main
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
  if (strcmp("chown", command) == 0) {
    return custom_chown(argc, argv);
  }
  return EXIT_NOT_FOUND;
}

// Copy  command function
int cp(int argc, char *argv[]) {
  // Checks if the -r flag is set
  int r_option = strcmp("-r", argv[1]) == 0;
  // Validates the number of arguments
  if (argc < 3 || argc > 4 || (argc == 4 && !r_option)) {
    errno = EINVAL;
    return EXIT_FAILURE;
  }
  // Depending on if -r is set calls to diferent functions
  if (r_option) {
    return cp_dir(argv[2], argv[3]);
  }
  return cp_file(argv[1], argv[2]);
}

// Sleep command function
int custom_sleep(int argc, char *argv[]) {
  // Validates the number of arguments
  if (argc != 2) {
    errno = EINVAL;
    return EXIT_FAILURE;
  }
  // Tries to convert the input to integer
  errno = 0;
  char *rest;
  int seconds = strtol(argv[1], &rest, 10);
  if (errno != 0) {
    return EXIT_FAILURE;
  }
  // If the input could not be converted as a whole then mark the input as
  // invalid
  if (rest != NULL && rest[0] != '\0') {
    errno = EINVAL;
    return EXIT_FAILURE;
  }
  sleep(seconds);
  return EXIT_SUCCESS;
}

// ls command function
int ls(int argc, char *argv[]) {
  // Default source path
  char *source = ".";
  if (argc > 2) {
    errno = EINVAL;
    return EXIT_FAILURE;
  }
  // If a param was send, use it as the source path
  if (argc == 2) {
    source = argv[1];
  }
  // Validate that the path is a directory
  int is_source_dist = is_dir(source);
  if (is_source_dist == -1) {
    return EXIT_FAILURE;
  }
  if (is_source_dist == 0) {
    errno = ENOTDIR;
    return EXIT_FAILURE;
  }

  // Open the directory file and read its entries
  DIR *dir = opendir(source);
  struct dirent *file;
  while ((file = readdir(dir)) != NULL) {
    // Ignores the self and parent paths
    if (strcmp(".", file->d_name) == 0 || strcmp("..", file->d_name) == 0) {
      continue;
    }
    printf("%s\n", file->d_name);
  }
  closedir(dir);
  return EXIT_SUCCESS;
}

// cat command function
int cat(int argc, char *argv[]) {
  if (argc != 2) {
    errno = EINVAL;
    return EXIT_FAILURE;
  }

  // Validates the first input is a file
  char *input = argv[1];
  int is_input_file = is_file(input);
  if (is_input_file == -1) {
    return EXIT_FAILURE;
  }
  if (is_input_file == 0) {
    errno = ENOENT;
    return EXIT_FAILURE;
  }

  // Opens the file
  char buffer[4096];
  // Probably open, read and write are better for this
  FILE *finput = fopen(input, "r");
  if (finput == NULL) {
    return EXIT_FAILURE;
  }
  int bytes_read = 0;
  while (feof(finput) == 0) {
    int bytes_read = fread(buffer, sizeof(char), sizeof(buffer), finput);
    // fread does not distinguish between EOF and error check needed
    if (ferror(finput) != 0) {
      // fread does not set errno
      errno = EIO;
      return EXIT_FAILURE;
    }
    // Could use printf but it does not behave the same with non printable
    // characters
    fwrite(buffer, sizeof(char), bytes_read, stdout);
  }
  fclose(finput);
  return EXIT_SUCCESS;
}

// mkdir command function
int custom_mkdir(int argc, char *argv[]) {
  if (argc != 2) {
    errno = EINVAL;
    return EXIT_FAILURE;
  }

  // Validates the input does not exists
  char *input = argv[1];
  int is_input_dir = is_dir(input);
  if (is_input_dir != -1) {
    errno = EEXIST;
    return EXIT_FAILURE;
  }

  // Get the upper folder from the input path
  char *path_dup = strdup(input);
  char *parent = dirname(path_dup);

  // Validates the upper folder exists
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
  // Makes the directory with the same mode as the parent
  return mkdir(input, parent_mode);
}

// chown command function
int custom_chown(int argc, char *argv[]) {
  if (argc != 3) {
    errno = EINVAL;
    return EXIT_FAILURE;
  }

  // Validates the path exists
  struct stat file_stat;
  char *input = argv[2];
  if (stat(input, &file_stat) == -1) {
    return EXIT_FAILURE;
  }
  // Set the defaults group id
  gid_t group_id = file_stat.st_gid;

  // Gets the user name from the given argument
  char *user_name = strtok(argv[1], ":");
  if (user_name == NULL) {
    errno = EINVAL;
    return EXIT_FAILURE;
  }

  // Retrieves the user id from /etc/passwd
  struct passwd *user;
  if ((user = getpwnam(user_name)) == NULL) {
    printf("User '%s' does not exists\n", user_name);
    errno = EINVAL;
    return EXIT_FAILURE;
  }
  uid_t user_id = user->pw_uid;

  // If group name was given it retrieves the group id
  char *group_name = strtok(NULL, ":");
  if (group_name != NULL) {
    struct group *grp;
    if ((grp = getgrnam(group_name)) == NULL) {
      printf("Group '%s' does not exists\n", group_name);
      errno = EINVAL;
      return EXIT_FAILURE;
    }
    group_id = grp->gr_gid;
  }

  // Change the ownership of the input file
  return chown(input, user_id, group_id);
}

// Copy function when using -r flag
int cp_dir(char *source, char *dest) {
  // Validate sthe source is a directory
  int source_is_dir = is_dir(source);
  if (source_is_dir == -1) {
    printf("'%s' does not exists\n", source);
    return EXIT_FAILURE;
  }
  if (source_is_dir == 0) {
    printf("'%s' is not a directory\n", source);
    errno = ENOTDIR;
    return EXIT_FAILURE;
  }

  // Validates the destination is a directory
  int dest_is_dir = is_dir(dest);
  if (dest_is_dir == 1) {
    if (is_dir_empty(dest) == 0) {
      errno = ENOTEMPTY;
      return EXIT_FAILURE;
    }
  }

  // If the destination exists but is not a file
  // return error
  if (dest_is_dir == 0) {
    errno = EEXIST;
    return EXIT_FAILURE;
  }

  // If the destinatin does not exists makes the directory
  if (dest_is_dir == -1) {
    if (parent_is_dir(dest) != 1) {
      return EXIT_FAILURE;
    }
    if (mkdir(dest, get_mode(source)) == -1) {
      return EXIT_FAILURE;
    }
  }

  // Open the source directory file and read its entries
  struct dirent *dir_entry;
  DIR *dir = opendir(source);
  while ((dir_entry = readdir(dir)) != NULL) {
    // Ignores the self and parent paths
    if (strcmp(".", dir_entry->d_name) == 0 ||
        strcmp("..", dir_entry->d_name) == 0) {
      continue;
    }

    int cp_return = 0;
    int cp_error = 0;
    // Get the full path of the directory entry
    char *full_path = concat_path(source, dir_entry->d_name);
    // If the entry is a directory makes the new destination and call cp_dir
    // recursively
    if (dir_entry->d_type == DT_DIR) {
      char *dest_with_folder = concat_path(dest, dir_entry->d_name);
      cp_return = cp_dir(full_path, dest_with_folder);
      cp_error = errno;
      free(dest_with_folder);
    } else if (dir_entry->d_type == DT_LNK) {
      // If the entry is a link makes sym link to the the same path in the new
      // destination
      cp_return = cp_link(full_path, dest);
      cp_error = errno;
    } else {
      // If is any other type of file copy the contents of the file
      cp_return = cp_file(full_path, dest);
      cp_error = errno;
    }

    free(full_path);

    // Handles any of the cp errors
    if (cp_return == EXIT_FAILURE) {
      closedir(dir);
      errno = cp_error;
      return cp_return;
    }
  }
  closedir(dir);
  return EXIT_SUCCESS;
}

// Copy function if -f flag is not set
int cp_file(char *source, char *dest) {
  // Validates the source is a file
  int source_is_file = is_file(source);
  if (source_is_file == -1) {
    return EXIT_FAILURE;
  }
  if (source_is_file == 0) {
    errno = ENONET;
    return EXIT_FAILURE;
  }

  // Checks if the destination is a directory
  int dest_is_dir = is_dir(dest);
  if (dest_is_dir == -1) {
    // If the destination is dos not exists checks the rest of the path exists
    if (parent_is_dir(dest) != 1) {
      errno = ENONET;
      return EXIT_FAILURE;
    }
  }
  // If the destination is a directory
  if (dest_is_dir == 1) {
    char *file_dup = strdup(source);
    char *file_name = basename(file_dup);
    // Concats the name of the source file to the destination path
    char *full_path = concat_path(dest, file_name);
    free(file_dup);
    // Copy the contents of the source to the destination path
    int copy_return = copy_file(source, full_path);
    int copy_errno = errno;
    free(full_path);
    errno = copy_errno;
    return copy_return;
  }

  // If destination is a file just copy the contents
  return copy_file(source, dest);
}

// Copy command for sym links (only called when copying directories)
int cp_link(char *source, char *dest) {
  // Creates a buffer for the path
  // (Probably there is a better way of allocating this)
  char buffer[PATH_MAX];
  int bytes_read = 0;
  // Reads the path that the sym link points to
  if ((bytes_read = readlink(source, buffer, sizeof(buffer))) == -1) {
    return EXIT_FAILURE;
  }
  // readlink does not add the end of string character
  // so it needs to be added manually
  buffer[bytes_read] = '\0';

  // Concats the filename to the destination path
  char *source_dup = strdup(source);
  char *file_name = basename(source_dup);
  char *full_dest = concat_path(dest, file_name);
  free(source_dup);

  // Creates the sym link in the destination
  if (symlink(buffer, full_dest) == -1) {
    return EXIT_FAILURE;
  }
  free(full_dest);
  return EXIT_SUCCESS;
}

// Copy the contents of source in dest
int copy_file(char *source, char *dest) {
  // Buffer chunk
  char buffer[4096];

  // Opens the source file in read mode
  FILE *fsource = fopen(source, "r");
  if (fsource == NULL) {
    return EXIT_FAILURE;
  }

  // Opens the destination file in write mode
  // Creates the file if id does not exists
  FILE *fdest = fopen(dest, "w");
  if (fdest == NULL) {
    return EXIT_FAILURE;
  }

  // Reads the size of the buffer until the source EOF is reached
  while (feof(fsource) == 0) {
    size_t written = fread(buffer, sizeof(char), sizeof(buffer), fsource);
    // Need to check for ferror as fread does not set it
    if (ferror(fsource) != 0) {
      errno = EIO;
      return EXIT_FAILURE;
    }
    fwrite(buffer, sizeof(char), written, fdest);
    if (ferror(fdest) != 0) {
      errno = EIO;
      return EXIT_FAILURE;
    }
  }

  // Close the files
  fclose(fsource);
  fclose(fdest);

  // Tries to set the same owner and mode than the original file
  struct stat source_stat;
  stat(source, &source_stat);
  if (chmod(dest, source_stat.st_mode) == -1) {
    return EXIT_FAILURE;
  }
  if (chown(dest, source_stat.st_uid, source_stat.st_gid) == -1) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

// Gets the mode from the inode entry of a file
int get_mode(char *path) {
  struct stat file_stat;
  if (stat(path, &file_stat) == -1) {
    return -1;
  }
  return file_stat.st_mode;
}

// Checks it a path is a file
// Return 1 if it is a file, 0 if it is not and -1 in case of error
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

// Checks it a path is a directory
// Return 1 if it is a file, 0 if it is not and -1 in case of error
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

// Checks if a directory is empty
// Returns 1 if it is empty, 0 if it is not and -1 in cas of error
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

// Checks if the parent directory is a directory
// Same as is_dir but use direname as the path
int parent_is_dir(char *path) {
  char *dir_dup = strdup(path);
  char *dir_name = dirname(dir_dup);
  int dir_name_is_dir = is_dir(dir_name);
  free(dir_dup);
  return dir_name_is_dir;
}

// Concatenates to paths and return the pointer to the combined
// As the lenght of the path is variable, a new char* is allocated with malloc
// So free should be called on the returned pointer
char *concat_path(char *path_a, char *path_b) {
  // Gets the length of both paths
  long dir_len = strlen(path_a);
  long base_len = strlen(path_b);

  // Allocates the memory for the combined path
  // The extra 2 characters are for \0 and /
  char *full_path = malloc((dir_len + base_len + 2) * sizeof(char));
  if (full_path == NULL) {
    return NULL;
  }

  // Initialize the full path with string termination character
  full_path[0] = '\0';

  // Concatenates both pats (could have done this easier with sprintf)
  strcat(full_path, path_a);
  // Concatenates the path separator
  full_path[dir_len] = '/';
  full_path[dir_len + 1] = '\0';
  strcat(full_path, path_b);
  return full_path;
}
