#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#define DEVICE_LABEL "custom:red:pwm0"
#define PWM_CLASS_PATH "/sys/class/leds/"
#define DEVICE_DIR PWM_CLASS_PATH DEVICE_LABEL
void help();
int on();
int off();
int get_max_brightness(char *buff, int n);
int set_brightness(char *buff);
int set_trigger(char *buff);
int get_triggers();
int is_file(char *path);

int main(int argc, char *argv[]) {
  if (argc == 1) {
    help();
    return EXIT_SUCCESS;
  }

  if (is_file(DEVICE_DIR) != 1) {
    printf("Device not found \n");
    return EXIT_FAILURE;
  }

  if (strcmp(argv[1], "on") == 0)
    return on();
  if (strcmp(argv[1], "off") == 0)
    return off();
  if (strcmp(argv[1], "bright") == 0)
    if (argc == 3)
      return set_brightness(argv[2]);
  if (strcmp(argv[1], "trigger") == 0) {
    if (argc == 3)
      return set_trigger(argv[2]);
    return get_triggers();
  }

  printf("Comando no reconocido\n");
  help();
  return EXIT_FAILURE;
}

void help() {
  printf("CLI for controlling PWM LED %s\n", DEVICE_DIR);
  printf("Available commands: \n");
  printf("\t- on: Lights on the LED\n");
  printf("\t- off: Lights off the LED\n");
  printf("\t- bright <level>: Sets the brightness level of the LED\n");
  printf("\t- trigger: Lists all the available triggers \n");
  printf("\t- trigger <trigger-name>: Configures a trigger for the LED\n");
}

int on() {
  char max_value[5];
  if (get_max_brightness(max_value, 4) == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }
  max_value[3] = '\0';
  return set_brightness(max_value);
}

int off() { return set_brightness("0"); }

int get_max_brightness(char *buff, int n) {
  char *max_path = DEVICE_DIR "/max_brightness";
  FILE *max = fopen(max_path, "r");
  if (max == NULL) {
    printf("File %s could not be open for lecuture", max_path);
    return EXIT_FAILURE;
  }
  fgets(buff, n, max);
  fclose(max);
  return EXIT_SUCCESS;
}

int set_brightness(char *buff) {
  char *bright_path = DEVICE_DIR "/brightness";
  FILE *brigthness = fopen(bright_path, "w");
  if (brigthness == NULL) {
    printf("File %s could not be open for writing", bright_path);
    return EXIT_FAILURE;
  }
  if (fputs(buff, brigthness) < 0) {
    printf("Bad value %s", buff);
    return EXIT_FAILURE;
  }
  fclose(brigthness);
  return EXIT_SUCCESS;
}

int set_trigger(char *buff) {
  char *trigger_path = DEVICE_DIR "/trigger";
  FILE *brigthness = fopen(trigger_path, "w");
  if (brigthness == NULL) {
    printf("File %s could not be open for writing", trigger_path);
    return EXIT_FAILURE;
  }
  if (fputs(buff, brigthness) < 0) {
    printf("Bad value %s", buff);
    return EXIT_FAILURE;
  }
  fclose(brigthness);
  return EXIT_SUCCESS;
}

int get_triggers() {
  char *trigger_path = DEVICE_DIR "/trigger";
  FILE *brigthness = fopen(trigger_path, "r");
  if (brigthness == NULL) {
    printf("File %s could not be open for writing", trigger_path);
    return EXIT_FAILURE;
  }
  char buff[1024];
  fgets(buff, 1024, brigthness);
  fclose(brigthness);
  char *trigger = strtok(buff, " ");

  printf("Available Triggers: \n");
  while (trigger != NULL) {
    printf("%s\n", trigger);
    trigger = strtok(NULL, " ");
  }
  return EXIT_SUCCESS;
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
