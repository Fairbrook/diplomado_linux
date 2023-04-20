#include <stdio.h>
#include "include/libarith.h"
#include "io.h"

int main(int argc, char **argv) {
	int opt;
	int a, b;

//	printf("Starting main function...\n");

	getInput("Select option: ", &opt);

	switch(opt){
	case 0:
		getInput("Operand a: ", &a);
		getInput("Operand b: ", &b);
		printf("Add result: %d\n", add(a, b));

	break;
	case 1:
                getInput("Operand a: ", &a);
                getInput("Operand b: ", &b);
                printf("Sub result: %d\n", sub(a, b));
	break;
	default:
		printf("Option not recognized\n");
		return -1;
	}

	return 0;
 }
