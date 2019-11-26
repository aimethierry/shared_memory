
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

#define SHSIZE 100
#include <unistd.h>

int v = 5;
int main(int argc, char * argv[])
{
	int shmid;
	key_t key;
	key = 9976;
	char * shm;
	char * s;
	//shmid = shmget(key, SHSIZE,  0666| IPC_CREAT); shmget(key, SHSIZE , 0644|IPC_CREAT); 
	shmid = shmget(key, SHSIZE, IPC_CREAT | 0666);
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
	
	if(s)
	for(s = shm; *s != 0 ; s++)
	{
		printf("%c", *s);
	}
	printf("\n");
	
	*shm = '*';
	return 0;
}
