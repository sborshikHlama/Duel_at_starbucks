//concuting programmin
// thread exceution is not actually parallel because system core don't have so many threads as our code uses
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void	*make_coffee(void *barista)
{
	//printf("Barista is preparing coffe\n");
	sleep(2);
	//printf("Your coffee is ready!\n");
	return NULL;
}

int	main(void)
{
	pthread_t	baristas[500];

	//when we pass funtion to another funtion we don't need to use &
	for (int i = 0; i < 500; ++i)
	{
		if (pthread_create(baristas + i, NULL, make_coffee, NULL))
			exit(1);
	}

	for (int i = 0; i < 500; ++i)
	{
		printf("Thread id: %lu\n", baristas[i]);
		// printf("\n");
	}

	for (int i = 0; i < 500; ++i)
	{
		pthread_join(baristas[i], NULL);
	}
}

// lets imagine that our threads need to access same memory
// two or more threads are racing 