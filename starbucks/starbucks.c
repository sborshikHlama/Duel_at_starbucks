#include <stdio.h>
#include <unistd.h>

void	make_cofee(char *name)
{
	printf("Barista %s is making a coffee...\n", name);
	sleep(3);
	printf("cofee is ready!\n");
}

int	main(void)
{
	make_cofee("Luca");
	make_cofee("Paoblo");
}
