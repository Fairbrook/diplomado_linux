#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MEM_SLEEP_PATH "/sys/power/mem_sleep"
#define POWER_STATE_PATH "/sys/power/state"
#define MEM_SLEEP "deep"
#define POWER_STATE "mem"

int main(int argc, char **argv) {
  int fd;
  struct input_event ev;

  fd = open(argv[1], O_RDONLY);

  for (int i = 0; i < 100; ++i) {
    read(fd, &ev, sizeof(struct input_event));
    printf("############## Entry %d ##########\n", i);
    printf("value=%u\n", ev.value);
    printf("time=%li\n", ev.time.tv_sec);
    printf("type=%u\n", ev.type);
    printf("code=%u\n", ev.code);
  }

  char mem_sleep[4] = MEM_SLEEP;
  char power_state[3] = POWER_STATE;

  int mem_sleep_fd = open(MEM_SLEEP_PATH, O_WRONLY);
  if (mem_sleep_fd < 0) {
    int err = errno;
    perror("Error opening mem_sleep file");
    return err;
  }
  write(mem_sleep_fd, mem_sleep, sizeof(mem_sleep));
  close(mem_sleep_fd);

  int power_sleep_fd = open(POWER_STATE_PATH, O_WRONLY);
  if (power_sleep_fd < 0) {
    int err = errno;
    perror("Error opening mem_sleep file");
    return err;
  }
  write(power_sleep_fd, power_state, sizeof(power_state));
  close(power_sleep_fd);
  return EXIT_SUCCESS;
}
