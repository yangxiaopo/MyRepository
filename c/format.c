#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024*1024
#pragma warning(disable: 4996)

void to_win_newline(char *buff, size_t read_number, FILE *fw, char *fmt_buff)
{
	char *cp;
	size_t after_format_number;

	after_format_number = read_number;

	if (*buff == '\n') {
		*fmt_buff++ = '\r';
		*fmt_buff++ = '\n';
		after_format_number++;
	}else
		*fmt_buff++ = *buff;
	read_number--;
	cp = buff++;
	while (read_number--){
		if (*buff == '\n'&& *cp != '\r') {
			*fmt_buff++ = '\r';
			*fmt_buff++ = '\n';
			after_format_number++;
		}else
			*fmt_buff++ = *buff;
		buff++;
		cp++;
	}
	fmt_buff -=	after_format_number;
	fwrite(fmt_buff, sizeof(char), after_format_number, fw);
}

int format(char *path_to_dictionary,char *path_to_format_dictionary)
{
	FILE *fo,*fw;
	size_t rdn,last_rdn;
	char *buff,*fmt_buff;
	
	buff = (char *)malloc(BUFFER_SIZE * sizeof(char));
	fmt_buff = (char *)malloc(2 * BUFFER_SIZE * sizeof(char));
	memset(buff,0, BUFFER_SIZE);
	memset(fmt_buff,0,2* BUFFER_SIZE);
	fo = fopen(path_to_dictionary,"r");
	fw = fopen(path_to_format_dictionary,"ab");
 	while ((rdn = fread(buff, sizeof(char), BUFFER_SIZE, fo))) {
		last_rdn = rdn;
		if (rdn != BUFFER_SIZE)
			if (*(buff + rdn - 1) != '\n')
				*(buff + rdn++) = '\n';
		to_win_newline(buff,rdn,fw, fmt_buff);
	}
	if (last_rdn == BUFFER_SIZE)
		if(*(buff + last_rdn - 1) != '\n'){
			*buff = '\n';
			to_win_newline(buff, 1, fw, fmt_buff);
		}
	free(buff);
	free(fmt_buff);
	fclose(fo);
	fclose(fw);
	return 0;
}

int main(int argc,char **argv)
{
	/*FILE *fw;
	int i;
	char *cp = "this is a test!\n";
	char *chrp = "again,this is a test!\n";

	fw = fopen("test.dict", "ab");
	for (i = 0; i < 5; i++) {
		fputs(cp, fw);
		fputs(chrp, fw);
	}
	fclose(fw);*/

	format(argv[1],argv[2]);
}