

#include "fir.h"
#include <stdio.h>


int main()
{
	uint8_t in = 'a';
	uint8_t out;
	printf("\nOutput: ");
	for(int i = 0; i < 20; i++)
	{
		uint8_t out;
		fir(in++, &out);
		if(in == 'd') in = 'a';
		printf("%c", (char)out);
	}
	printf("\n");
	return 0;
}
