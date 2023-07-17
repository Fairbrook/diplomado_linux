#include "kamv_linked_list.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#define NODE_PATH "/dev/linked_list"

int main(int argc, char *argv[]) {
  if (argc < 2)
    return -EINVAL;
  char *cmd = argv[1];
  char *path = NODE_PATH;
  int fd;
  if (argc >= 3)
    path = argv[2];

  fd = open(path, O_RDWR | O_NONBLOCK);
  if (fd < 0) {
    printf("Could not open device file: %s ", path);
    perror("");
    return errno;
  }

  unsigned int action = 0;

  if (strcmp(cmd, "pop") == 0)
    action = LINKED_LIST_POP;
  if (strcmp(cmd, "sum") == 0)
    action = LINKED_LIST_SUM;

  long int ret = ioctl(fd, action);
  close(fd);
  if (ret < 0) {
    printf("Error while ioctl command: %s\n", strerror(errno));
    return ret;
  }

  if (action == LINKED_LIST_SUM) {
    printf("%li\n", ret);
  }

  return 0;
}
