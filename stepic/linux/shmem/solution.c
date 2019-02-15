#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	key_t shmkey_1 = atoi(argv[1]);
	key_t shmkey_2 = atoi(argv[2]);

	int shmid_1 = shmget(shmkey_1, 1000, 0600);
	int shmid_2 = shmget(shmkey_2, 1000, 0600);
	int *shmaddr_1 = shmat(shmid_1, NULL, SHM_RDONLY);
	int *shmaddr_2 = shmat(shmid_2, NULL, SHM_RDONLY);

	key_t key = ftok("/tmp/ter", 'S');
	int shmid_3 = shmget(key, 1000, 0666 | IPC_CREAT);
	printf("%d\n", key);
	int *shmaddr_3 = shmat(shmid_3, NULL, 0);

	for(int i = 0; i < 100; i++)
	{
		shmaddr_3[i] = shmaddr_1[i] + shmaddr_2[i];
	}

	return 0;
}
