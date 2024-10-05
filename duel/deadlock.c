#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

//This code recreates situation when deadlock happens
//Two proccesses are waiting for each other

typedef struct s_cowboy
{
	char *		name;
	pthread_t	thread;
}				t_cowboy;

pthread_mutex_t	ugly_gun_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t	bad_gun_lock = PTHREAD_MUTEX_INITIALIZER;

void	*action(void *data)
{
	t_cowboy	cowboy;

	cowboy = *(t_cowboy *)data;
	if (!strcmp(cowboy.name, "ugly"))
		pthread_mutex_lock(&ugly_gun_lock);
	else
		pthread_mutex_lock(&bad_gun_lock);
	printf("%s, has taken his own gun\n", cowboy.name);

	if (!strcmp(cowboy.name, "ugly"))
		pthread_mutex_lock(&bad_gun_lock);
	else
		pthread_mutex_lock(&ugly_gun_lock);

	return NULL;
}

int main()
{
	t_cowboy ugly = {"ugly"};
	t_cowboy bad = {"bad"};

	pthread_create(&ugly.thread, NULL, action, &ugly);
	pthread_create(&bad.thread, NULL, action, &bad);

	pthread_join(ugly.thread, NULL);
	pthread_join(bad.thread, NULL);
}
