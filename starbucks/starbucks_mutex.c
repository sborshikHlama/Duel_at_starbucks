#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define TH 500

//Shared source
uint64_t ledger = 0;
pthread_mutex_t	ledger_lock = PTHREAD_MUTEX_INITIALIZER;

void	*update_ledger(void *data)
{
	//Lock
	pthread_mutex_lock(&ledger_lock);
	ledger++;
	//Unlock
	pthread_mutex_unlock(&ledger_lock);
	return NULL;
}

int main(void)
{
	pthread_t waiters[TH];

	// pthread_mutex_init(&ledger_lock, NULL);

	for (int i = 0; i < TH; ++i)
	{
		pthread_create(waiters + i, NULL, update_ledger, NULL);
	}
	
	for (int i = 0; i < TH; ++i)
	{
		pthread_join(waiters[i], NULL);
	}
	printf("Resilt: %llu\n", ledger);
}
