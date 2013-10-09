#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int addr = 0;
int value[1024];
int debug = 0;

//Translation code function
void Translation(char ope)
{
	switch (ope) {
		case '>':
			addr++;
			break;
		case '<':
			addr--;
			break;
		case '+':
			value[addr]++;
			break;
		case '-':
			value[addr]--;
			break;
		case '.': 
			if(debug == 1)printf("%d, ASCII:(%s)\n", value[addr], &value[addr]);
			else printf("%s", &value[addr]);
			break;
		case ',':
			//printf("\nvalue[%d] = ", addr),
			value[addr] = getchar();
			break;
		default:
			break;
	}	
}
int search(char *code, int offset, int codelen){
	int n, block = 1;

	for(n = offset+1; n < codelen ; n++){
		if(code[n] == '[')block++;
		if((code[n] == ']') && (block--) && (block == 0))break;
	}
	return (n + 1);
}
int search_r(char *code, int offset){
	int n, block = 1;

	for(n = offset-1; n > 0 ; n--){
		if(code[n] == ']')block++;
		if((code[n] == '[') && (block--) && (block == 0))break;
	}
	return (n + 1);
}
//file open and read first line
int ReadLine(char *FileName, char *code, size_t bfsize){
	FILE *fp = fopen(FileName, "r" );
	if( fp == NULL ) return -1;
	fgets(code, bfsize, fp );
	return 0;
}
int main(int argc ,char *argv[])
{
	int n = 0, len = 0, opt;
	char code[1024], FileName[256];
	
	while((opt=getopt(argc,argv,"dhf:e:"))!=-1){
		switch (opt)
		{
			case 'f':
				strcpy(FileName, optarg);
				ReadLine(FileName, code, sizeof(code));
				break;
			case 'e':
				strcpy(code, optarg);
				break;
			case 'h':
				printf("bf Usage:\n"
					"   -f <bf file>\n"
					"   -e <script>\n");
				break;
			case 'd':
				debug = 1;
				break;
			default:
				break;
		}
	}//get arg options
	
	len = strlen(code);
	for(n = 0;n<len;n++){
		if(debug == 1){
			printf("%d mem:%d code:%d\n",addr, value[addr], code[n]);
		}
		if((code[n] == '[') && (value[addr] == 0)) n = search(code, n, len);
		if((code[n] == ']') && (value[addr] != 0)) n = search_r(code, n);
		Translation(code[n]);
	}//running block
	return 0;
}
