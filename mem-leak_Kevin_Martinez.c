#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  char *path = NULL;

  // Even though the program will not leak memory it will still consume a lot of
  // CPU as the loop is infinite
  while (1) {
    // This will allocate 100 bytes
    path = malloc(100);
    // Free malloc space before losing the reference to strdup
    free(path);
    // And this another 6 bytes
    path = strdup("STRING");
    // Free strdup (internally malloc) before losing the reference to NULL
    free(path);
    // We can safetly assign NULL
    path = NULL;
  }

  return 0;
}
