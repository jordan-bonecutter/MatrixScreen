#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

char available[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
				'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '!', '@', '#', '$', '%', '^', '&', '*'};
unsigned char QUIT = 0;
unsigned char HASQUIT = 0;

void *printRand(void *vargp)
{
	while(1)
	{
		if(QUIT)
		{
			HASQUIT = 1;
			return NULL;
		}
		printf("%c", available[rand()%sizeof(available)]);
		fflush(stdout);
		usleep(100000);
	}
}

void sigintHandler(int signum)
{
	QUIT = 1;
	signal(SIGINT, sigintHandler);
	printf("\x1B[0m\n");
	fflush(stdout);
	while(!HASQUIT);
	exit(0);
}

int main()
{
	signal(SIGINT, sigintHandler);
	srand(clock());
	printf("\x1B[32m");

	pthread_t thread;
	pthread_create(&thread, NULL, printRand, NULL);
	pthread_join(thread, NULL);

	return 0;
}

