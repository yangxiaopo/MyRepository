#include <stdio.h>
#include <stdlib.h>
void copy(char *origin,char *video_mem_start,int num)
{
	__asm__("cld\n\t"
		"rep\n\t"
		"movsl\n\t"
		::"c"(num>>2),
		"D"(video_mem_start),
		"S"(origin)
		:"0","1"//"cx","di","si"
		);
}

int main()
{
	char *s="yangxiaopopo";
	char *d=malloc(12*sizeof(char));
	copy(s,d,12);
	printf("%s\n",d);
	free(d);
}
