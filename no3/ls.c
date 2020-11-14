#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	void        read_dir(DIR *, char *);
	void        fatal(char *);
	DIR        *dir;
	char        file[1024];
	struct      dirent *directory;

	if(argc == 1) strcpy(file, ".");
	else strcpy(file, argv[1]);

	if((dir = opendir(file)) == NULL) fatal("opendir");

	read_dir(dir, file);
}

void read_dir(DIR *dir, char *file)
{
	void        fatal(char *);
	DIR        *imsi_dir;
	struct        dirent  *directory;
	struct        stat    file_stat;
	char        buff[1024];

	while(directory = readdir(dir)) {
		if(!strncmp(directory->d_name, ".", 1) || !strcmp(directory->d_name, ".."))
			continue;

		if(directory->d_ino == 0) continue;

		sprintf(buff, "%s/%s", file, directory->d_name);
		puts(buff);

		if(lstat(buff, &file_stat) < 0) fatal("stat");

		if(S_ISDIR(file_stat.st_mode)) {
			printf("[%s/%s]:\n", file, directory->d_name);
			imsi_dir = opendir(buff);
			read_dir(imsi_dir, buff);
		}
	}
	closedir(dir);
}

void fatal(char *error)
{
	perror(error);
	exit(1);
}
