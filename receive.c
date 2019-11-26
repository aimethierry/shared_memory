#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

char * shm;
char * s;

int openfile(char * name);

int openfile(char * name)
{
	int shmid = -1;
	int size;
	shmid = shm_open (name, O_RDWR, 0600);
	if(shmid == -1){
		perror("error when opening \n");
	}
	size = lseek(shmid, 0, SEEK_END);
	shm = (char *) mmap (NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0);
	
	if (shm == MAP_FAILED)
	{
        perror ("ERROR: mmap() failed");
    }
	return 0;
}


int main(int argc, char * argv[])
{
	char name[80];
	
	printf("enter a file u want to open \n");
	fgets(name, sizeof (name), stdin);
	openfile(name);
	
	/*
	for(s = shm; *s != 0 ; s++)
	{
		printf("%c", *s);
	}
	*shm = 'A';*/
	printf("address of the file %d", &shm);
	return 0;
}
