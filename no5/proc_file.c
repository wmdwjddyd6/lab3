#include <unistd.h> 
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

int main() { 
	int fd; pid_t pid; 
	char buf[10];

	if ((fd = open ("data", O_RDONLY)) == -1) 
		fatal("open failed");

	read (fd, buf, 10);

	printpos ("Before fork", fd); 

	switch (pid = fork()){
		case -1: 
		fatal ("folk failed"); 
		break; 

		case 0: 
		printpos ("Child before read", fd); 
		read (fd, buf, 10); 
		printpos ("Child after read", fd); 
		break; 

		default: 
		wait ((int *) 0); 
		printpos ("Parent after wait", fd); 
	}
}

int printpos (const char *string, int filedes) { 
	off_t pos; 
	if ((pos = lseek (filedes, 0, SEEK_CUR)) == -1) 
		fatal ("lseek failed"); 
	printf("%s:%ld\n", string, pos); 
}
