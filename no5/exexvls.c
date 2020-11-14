#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() { 
	char *const argv[] = {"ls", "-l", (char *)0};
	printf("executing execv.\n");
	execv("/bin/ls", argv); 
	perror("execv failed to run ls"); 
	exit(1); 
}
