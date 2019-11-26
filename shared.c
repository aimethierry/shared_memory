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


//#define SHSIZE 100
int create(char *name , int size);
int dele_file(char * s);
char * shm;
char * s;

int dele_file(char * s)
{
    int len;
    len = strlen (s);
    if (s [len - 1] == '\n')
    {
        s [len - 1] = '\0';
    }
    return 0;
}

int create(char * name, int SHSIZE)
{
	int shmid = -1;
	int cmpr;
   	shmid = shm_open(name, O_CREAT | O_EXCL | O_RDWR, 0600);
	if(shmid == -1)
	{
		perror ("ERROR: shm_open() failed \n");
		exit(1);
	}
	
	cmpr =  ftruncate(shmid, SHSIZE);
	shm = (char *) mmap (NULL, SHSIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0);
	
	
	if(shm == MAP_FAILED)
	{
		perror ("shmat \n");
		exit(1);
	}
	memcpy(shm, "hello world", 11); 
	return 0;
}

int main(int argc, char * argv[])
{	
	/* int tryid = -1;
	key_t key;
	key = 9976;
    memcpy(shm, "hello world", 11);
	s = shm;
	 */
	 
	char name[80];
	int size = 0;
	
	int val=1;
	while(val)
	{
		printf("Enter a name to create a file \n");
		fgets(name, sizeof (name), stdin);
        dele_file(name);
        printf ("Enter size: ");
        scanf("%d \n", &size);
		create(name, size);
        s = shm;
        for(s = shm; *s != 0 ; s++)
		{
		printf("%c", *s);
		}
        if(*shm == 'A')
        {
			printf("stop the program \n");
			val = 0;
		}
	}	
	return 0;
}
