#include <stdio.h>
#include <stdlib.h>
int main()
{
	char *buffer = "hello world!!!\n";
	char *p = malloc(28*sizeof(char));
	FILE *fi = fopen("/dev/my_cdev","rt+");
	fwrite(buffer,1,16,fi);
	fread(p,sizeof(char),16,fi);
	printf("%s  %d\n",p,sizeof(buffer));
	fclose(fi);
	free(p);
}
