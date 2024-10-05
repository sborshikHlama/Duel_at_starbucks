#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

//This code is an attempt to fix deadlock with using rand functio

typedef struct s_cowboy
{
	char *			name;
	unsigned long	reaction_time;
	pthread_t		thread;
}				t_cowboy;

pthread_mutex_t	ugly_gun_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t	bad_gun_lock = PTHREAD_MUTEX_INITIALIZER;

void	*action(void *data)
{
	t_cowboy	cowboy;

	cowboy = *(t_cowboy *)data;
	printf("%s has reaction time %lu\n", cowboy.name, cowboy.reaction_time);
	//How fast is cowboy
	//usleep is using microseconds, sleep uses seconds
	usleep(cowboy.reaction_time);
	//usleep doesn't really protect from deadlock 

	if (!strcmp(cowboy.name, "ugly"))
		pthread_mutex_lock(&ugly_gun_lock);
	else
		pthread_mutex_lock(&bad_gun_lock);
	printf("%s, has taken his own gun\n", cowboy.name);

	if (!strcmp(cowboy.name, "ugly"))
		pthread_mutex_lock(&bad_gun_lock);
	else
		pthread_mutex_lock(&ugly_gun_lock);
	printf("%s has taken others gun\n", cowboy.name);
	printf("%s killed the other\n", cowboy.name);
	exit(0);
	return NULL;
}

int main()
{
	srand(time(NULL) * getpid());

	t_cowboy ugly = {"ugly", rand() % 10000};
	t_cowboy bad = {"bad", rand() % 10000};

	// set RNG seed to be more random using current time multiplied by random process id
	// RNG formula is new number=(seed×1031+7)mod10000

	pthread_create(&ugly.thread, NULL, action, &ugly);
	pthread_create(&bad.thread, NULL, action, &bad);

	pthread_join(ugly.thread, NULL);
	pthread_join(bad.thread, NULL);
}
