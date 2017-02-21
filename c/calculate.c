#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)
#define MAXLINE 1024
#define MAXLENGTH 12
struct line{
	int number;
	int littleCase;
	int upperCase;
	int special;
/*****************************/
	unsigned long total;
	unsigned long buff[MAXLENGTH];
};

struct line arr[] = {{1,0,0,0,0,{0}},
					 {0,1,0,0,0,{0}},
					 {0,0,1,0,0,{0}},
					 {0,0,0,1,0,{0}},
					 {1,1,0,0,0,{0}},
					 {1,0,1,0,0,{0}},
					 {1,0,0,1,0,{0}},
					 {0,1,1,0,0,{0}},
					 {0,1,0,1,0,{0}},
					 {0,0,1,1,0,{0}},
					 {1,1,1,0,0,{0}},
					 {1,1,0,1,0,{0}},
					 {1,0,1,1,0,{0}},
					 {0,1,1,1,0,{0}},
					 {1,1,1,1,0,{0}}};

static void _printf(struct line *line,FILE *fw,int n) {
	int i,index;
	unsigned long all = 0;
	while (n--) {
		char *buff = (char*)malloc(2*MAXLINE * sizeof(char));
		index = sprintf(buff, "[%s%s%s%s]总计为:%lu\r\n", line->number == 1?"数":"", line->littleCase == 1 ? "小" : "", line->upperCase == 1 ? "大" : "", line->special == 1 ? "特殊字符" : "",line->total);
		all += line->total;
		for (i = 1; i < MAXLENGTH; i++)
			if(line->buff[i])
				index += sprintf(buff+index,"长度为%d的个数为%lu\r\n",i,line->buff[i]);
		sprintf(buff + index,"\r\n");
		fputs(buff, fw);
		line++;
		free(buff);
	}
	char *buff = (char*)malloc(2 * MAXLINE * sizeof(char));
	sprintf(buff, "*********************************总数为%lu*****************************************\r\n", all);
	fputs(buff, fw);
	free(buff);
}

void calculate(char *filename)
{
	FILE *fr;
	int count;
	unsigned short index;
	char *c;
	char buff[MAXLINE];
	struct line *t;
	fr = fopen(filename,"r");

	while((fgets(buff,MAXLINE,fr))!=NULL){
		index = 0x7FFF;
		count = 0;
		c = buff;
		while(*c != '\n'){
			if ('0' <= *c&&*c <= '9')
				index &= 0x5C71;
			else if ('a' <= *c&&*c <= 'z')
				index &= 0x6D92;
			else if ('A' <= *c&&*c <= 'Z')
				index &= 0x76A4;
			else
				index &= 0x7B48;
			count++;
			c++;
		}

		if (index & 0x1)
			index = 0;
		else if (index & 0x2)
			index = 1;
		else if (index & 0x4)
			index = 2;
		else if (index & 0x8)
			index = 3;
		else if (index & 0x10)
			index = 4;
		else if (index & 0x20)
			index = 5;
		else if (index & 0x40)
			index = 6;
		else if (index & 0x80)
			index = 7;
		else if (index & 0x100)
			index = 8;
		else if (index & 0x200)
			index = 9;
		else if (index & 0x400)
			index = 10;
		else if (index & 0x800)
			index = 11;
		else if (index & 0x1000)
			index = 12;
		else if (index & 0x2000)
			index = 13;
		else if (index & 0x4000)
			index = 14;
		t = &arr[index];
		t->total++;
		t->buff[count]++;
	}
	fclose(fr);
}

int main(int argc,char *argv[])
{
	int i;
	FILE *fw;
	for(i = 1;i < argc-1;i++)
		calculate(argv[i]);
	fw = fopen(argv[i], "w");
	_printf(arr, fw, 15);
	fclose(fw);
}
