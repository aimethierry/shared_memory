
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


int create()
{
	return 0;
}
int main(int argc, char * argv[])
{
	int shmid;
	key_t key;
	key = 9976;
	char * shm;
	char * s;
	//shmid = shmget(key, SHSIZE,  0666| IPC_CREAT); shmget(key, SHSIZE , 0644|IPC_CREAT); 
  
  
   	shmid = shmget(key, SHSIZE, IPC_CREAT | 0666);
	
	//shmid = shm_open(shm_name, O_CREAT | O_EXCL | O_RDWR, 0600);
	
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
	
	memcpy(shm, "hello world", 11);
	s = shm;
	
	while(*shm != 'A')
	{
		/* int remove = shmctl(shmid, IPC_RMID, NULL);
		if(remove == -1)
		{
			perror("there was an error in removing \n");
		} */
		printf("removed successfully \n");
		sleep(1);
	}
		
	return 0;
}
