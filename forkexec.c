#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int spawn(char *program, char **arg_list) {
  pid_t child_pid;

  child_pid = fork();
  if (child_pid != 0)

    return child_pid;
  else {
    execvp(program, arg_list);
    printf("returning from execvp");
    abort();
  }
}
int main() {
  char *arg_list[] = {"ls\0", "-l\0", "/\0", NULL};
  spawn("lsad", arg_list);
  printf("done with main program\n");
  return 0;
}
