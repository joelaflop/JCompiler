/*
 * token.h
 */

#define MAX_TOKEN_LENGTH 250

#include <stdio.h>

typedef struct {
  enum { DEFUN, IDENT, RETURN, 
         PLUS, MINUS, MUL, DIV, MOD, 
         AND, OR, NOT, 
         LT, LE, EQ, GE, GT,
         IF, ELSE, ENDIF, 
         DROP, DUP, SWAP, ROT,
		 ARG,
         LITERAL,
         BROKEN_TOKEN } type;
  int literal_value;    // this field used to store the value of literal tokens
  int arg_no;           // this field used to store the index of argument literals argN
  char str[MAX_TOKEN_LENGTH]; //token string!
} token;

void read_token (token *theToken, FILE *theFile);


