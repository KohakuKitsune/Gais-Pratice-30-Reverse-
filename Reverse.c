#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>


int main(int argc, char**argv){
	int fd;
	int file_size;
	int i;
	char *front = (char*) malloc(sizeof(char)*2);
	char *back = (char*) malloc(sizeof(char)*2);
	fd = open(*(argv+1), O_RDWR);

	struct stat file_stats;
	stat(*(argv+1),&file_stats);

	file_size = file_stats.st_size;

	for(i = 0; i < (file_size / 2); i++){
		lseek(fd, i, SEEK_SET);
		read(fd, front, 1);
		
		lseek(fd, -1 * i - 1 ,SEEK_END);
		read(fd, back, 1);

		lseek(fd, i, SEEK_SET);
		write(fd, back, 1);

		lseek(fd, -1 * i - 1,SEEK_END);
		write(fd, front, 1);	
	}

	close(fd);
	free(front);
	free(back);

	return 0;
}

