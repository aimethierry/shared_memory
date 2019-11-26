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
int shmid = -1;


int openfile(int mykey, int size);

int openfile(int mykey, int size)
{
	
	key_t key;
	key = mykey;
	
	shmid = shmget(key, size, 0666);
	
	if(shmid < 0)
	{
		perror ("ERROR: shm_open() failed \n");
		exit(1);
	}
	shm = shmat(shmid, NULL, 0);
	if(shm == (char *) -1)
	{
		perror ("shmat \n");
		exit(1);
	}
	return 0;
}


int main(int argc, char * argv[])
{
	int key;
	int size;
	printf("enter a location to read \n");
	scanf("%d", &key);
	
	printf("enter size  \n");
	scanf("%d", &size);
	
	openfile(key, size);
	for(s = shm; *s != 0 ; s++)
	{
		printf("%c", *s);
	}
	printf("\n");
	*shm = 'A';
	return 0;
}
