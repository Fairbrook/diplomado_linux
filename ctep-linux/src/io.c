#include <stdio.h>

void getInput(char *text, int *opt) {
	printf("%s", text);
	scanf("%d", opt);
}

void putOutput(char *buff) {
	printf("%s\n", buff);
}
