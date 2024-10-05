#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define TH 500

//Shared source
uint64_t ledger = 0;

void	*update_ledger(void *data)
{
	ledger++;
	return NULL;
}

int main(void)
{
	pthread_t waiters[TH];

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

