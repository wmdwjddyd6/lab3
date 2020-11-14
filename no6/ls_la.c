#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	if(argc == 1){
		printf("Please write more parameters\n");
		return 1;
	}
	pid_t pid = fork();
	if(pid < 0){
		perror("fork error");
		return 1;
	}
	if(pid == 0) wait(0);
	else{
		execvp(argv[1], argv+1);
		return 0;
	}
}
