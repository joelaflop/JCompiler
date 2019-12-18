#include "token.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void read_token(token *token, FILE *file){	
  	if(token->str[0] == '0' && tolower(token->str[1]) == 'x') {
   		token->type = LITERAL;
   		token->literal_value = (int) strtol(token->str, NULL, 16);
 	}else if((token->str[0] == '-' && strlen(token->str) > 1) || isdigit(token->str[0])) {
  		token->type = LITERAL;
  		token->literal_value = (int) strtol(token->str, NULL, 10);
  	} else if(strcmp(token->str, "or") == 0) {
  	  	token->type = OR;
  	} else if(strcmp(token->str, "and") == 0) {
   	 	token->type = AND;
  	} else if(strcmp(token->str, "not") == 0) {
  	  	token->type = NOT;
  	} else if(strcmp(token->str, "+") == 0) {
   	 	token->type = PLUS;
  	} else if(strcmp(token->str, "-") == 0) {
   	 	token->type = MINUS;
  	} else if(strcmp(token->str, "*") == 0) {
   	 	token->type = MUL;
	} else if(strcmp(token->str, "/") == 0) {
   	 	token->type = DIV;
  	} else if(strcmp(token->str, "%") == 0) {
   	 	token->type = MOD;
  	} else if(strcmp(token->str, "eq") == 0) {
		token->type = EQ;
  	} else if(strcmp(token->str, "ge") == 0) {
		token->type = GE;
	} else if(strcmp(token->str, "gt") == 0) {
		token->type = GT;
  	} else if(strcmp(token->str, "lt") == 0) {
   	 	token->type = LT;
  	} else if(strcmp(token->str, "le") == 0) {
   	 	token->type = LE;
  	} else if(token->str[0] == 'a' && token->str[1] == 'r' && token->str[2] == 'g') {
  		char number[4] = "";
  		for(int i = 3; isdigit(token->str[i]) && i < 6; i++){
  			number[i-3] = token->str[i];
  		}
  		token->arg_no = (int) strtol(number, NULL, 10);
  		token->type = ARG;
  	} else if(strcmp(token->str, "if") == 0) {
    	token->type = IF;
  	} else if(strcmp(token->str, "else") == 0) {
    	token->type = ELSE;
  	} else if(strcmp(token->str, "endif") == 0) {
    	token->type = ENDIF;
  	} else if(strcmp(token->str, "defun") == 0) {
    	token->type = DEFUN;
    	char ch = fgetc(file);
    	while (isspace(ch)) {
      		ch = fgetc(file);
    	}
    	token->str[0] = ch;
    	int i = 0;
    	while (!isspace(ch)) {
      		token->str[i] = ch;
      		ch = fgetc(file);
      		i++;
    	}
    	token->str[i] = '\0';
  	} else if(strcmp(token->str, "return") == 0) {
    	token->type = RETURN;
  	}  else if (strcmp(token->str, "drop") == 0) {
  	  	token->type = DROP;
  	} else if(strcmp(token->str, "dup") == 0) {
   	 	token->type = DUP;
  	} else if(strcmp(token->str, "swap") == 0) {
   	 	token->type = SWAP;
  	} else if(strcmp(token->str, "rot") == 0) {
  	  	token->type = ROT;
  	}  else{
    	token->type = IDENT;
  	}
}

