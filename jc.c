#include "writer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc, char **argv){ 
	FILE *in, *out;
	char *string = strchr(argv[1], '.');
	if(string != NULL && !strcmp(string, ".j")){
		in = fopen(argv[1], "r");
		char outname[200];
		strcpy(string, "");
		strcpy(outname, argv[1]);
		strcat(outname,".asm");
		out = fopen(outname, "w");
	} else{
		printf("bad file name");
		return(-1);
	}

	int labels = 0;
	stack *ifStack = malloc(sizeof(stack));
	init(ifStack);

	char ch = fgetc(in);
	token *newToken = malloc(sizeof(token));
	while (ch != EOF) {
		if (ch == ';')
			while (ch != '\n') 
				ch = fgetc(in);
		if (!isspace(ch)) {
			char str[MAX_TOKEN_LENGTH] = "";
			while (!isspace(ch) && ch != EOF) {
				strncat(str, &ch, 1);
				ch = fgetc(in);
			}
			strcpy(newToken->str, str);
			read_token(newToken, in);
			assembly(out, newToken, &labels, ifStack);
			
		}
		ch = fgetc(in);
	}	
	free(newToken);
	free(ifStack);
	fclose(in);
	fclose(out);		
}
