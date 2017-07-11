#include <stdio.h>

//numbers , no-repeat , in base[] which can be added to equal to <num>;
//all posibilities

static int base[] = {1,3,4,5,6,8,9};

void count(int num,int kinds_of_base)
{
	if(num == 0){
		//success
		printf(" success\n");
		return;
	}else if(num < 0){
		printf(" fail");
		return;
	}else if(kinds_of_base == 0)
	{
		printf(" fail");
		return;
	}
	
	--kinds_of_base;
	printf(" %d",base[kinds_of_base]);
	count((num - base[kinds_of_base]),kinds_of_base);
	count(num,kinds_of_base);
}

int main(int argc,char *argv[])
{
	count(13,sizeof(base)/sizeof(int));
}
