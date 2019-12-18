#include <stdio.h>
#include <stdlib.h>
#include "writer.h"

void assembly(FILE *out, token *token, int *labels, stack *ifStack)
{
	switch(token->type) {
		case DEFUN: //prologue
			fprintf(out, "%s\n", ".CODE");
			fprintf(out, ".FALIGN\n%s\n", token->str);
			fprintf(out, "ADD R6, R6, #-3\n");
			fprintf(out, "STR R7, R6, #1\n");
			fprintf(out, "STR R5, R6, #0\n");
			fprintf(out, "ADD R5, R6, #0\n");
			fprintf(out, "ADD R6, R6, #-2\n");
			break;
		case RETURN: //epilogue
			fprintf(out, "LDR R7, R6, #0\n");
			fprintf(out, "STR R7, R5, #2\n"); //
			fprintf(out, "ADD R6, R5, #0\n"); //
			fprintf(out, "LDR R7, R5, #1\n"); 
			fprintf(out, "LDR R5, R5, #0\n");
			fprintf(out, "ADD R6, R6, #2\n"); //
			fprintf(out, "RET\n");
			break;
		case IDENT:
			fprintf(out, "LEA R7 %s\n", token->str);
			fprintf(out, "JSRR R7\n");
			break;
		case AND:
			fprintf(out, "LDR R2, R6, #0\n");
			fprintf(out, "LDR R1, R6, #1\n");
			fprintf(out, "AND R2, R2, R1\n");
			fprintf(out, "ADD R6, R6, #1\n");
			fprintf(out, "STR R2, R6, #0\n");
			break;
		case OR:
			fprintf(out, "LDR R2, R6, #0\n");
			fprintf(out, "LDR R1, R6, #1\n");
			fprintf(out, "OR R2, R2, R1\n");
			fprintf(out, "ADD R6, R6, #1\n");
			fprintf(out, "STR R2, R6, #0\n");
			break;
		case NOT:
			fprintf(out, "LDR R2, R6, #0\n");
			fprintf(out, "NOT R2, R2\n");
			fprintf(out, "STR R2, R6, #0\n");
			break;
		case PLUS:
			fprintf(out, "LDR R2, R6, #0\n");
			fprintf(out, "LDR R1, R6, #1\n");
			fprintf(out, "ADD R2, R2, R1\n");
			fprintf(out, "ADD R6, R6, #1\n");
			fprintf(out, "STR R2, R6, #0\n");
			break;
		case MINUS:
			fprintf(out, "LDR R2, R6, #0\n");
			fprintf(out, "LDR R1, R6, #1\n");
			fprintf(out, "SUB R2, R2, R1\n");
			fprintf(out, "ADD R6, R6, #1\n");
			fprintf(out, "STR R2, R6, #0\n");
			break;
		case MUL:
			fprintf(out, "LDR R2, R6, #0\n");
			fprintf(out, "LDR R1, R6, #1\n");
			fprintf(out, "MUL R2, R2, R1\n");
			fprintf(out, "ADD R6, R6, #1\n");
			fprintf(out, "STR R2, R6, #0\n");
			break;
		case DIV:
			fprintf(out, "LDR R2, R6, #0\n");
			fprintf(out, "LDR R1, R6, #1\n");
			fprintf(out, "DIV R2, R2, R1\n");
			fprintf(out, "ADD R6, R6, #1\n");
			fprintf(out, "STR R2, R6, #0\n");
			break;
		case MOD:
			fprintf(out, "LDR R2, R6, #0\n");
			fprintf(out, "LDR R1, R6, #1\n");
			fprintf(out, "MOD R2, R2, R1\n");
			fprintf(out, "ADD R6, R6, #1\n");
			fprintf(out, "STR R2, R6, #0\n");
			break;
		case IF:
			push(ifStack, *labels);
			fprintf(out, "LDR R2, R6, #0\n");
			fprintf(out, "ADD R6, R6, #1\n");
			fprintf(out, "CMPI R2, #0\n");
			fprintf(out, "BRz else%d\n", (*labels)++);
			break;
		case ELSE:
			fprintf(out, "JMP endif%d\n", ifStack->top->num);
			fprintf(out, "else%d\n", ifStack->top->num);
			break;
		case ENDIF:
			fprintf(out, "endif%d\n", ifStack->top->num);
			pop(ifStack);
			break;
		case EQ:
			fprintf(out, "LDR R2, R6, #0\n");
			fprintf(out, "LDR R1, R6, #1\n");
			fprintf(out, "CMP R2, R1\n");
			fprintf(out, "BRz g%d\n", (*labels)++);
			fprintf(out, "CONST R2, #0\n");
			fprintf(out, "JMP g%d\n", (*labels)--);
			fprintf(out, "g%d\n", (*labels)++);
			fprintf(out, "CONST R2, #1\n");
			fprintf(out, "g%d\n", (*labels)++);
			fprintf(out, "ADD R6, R6, #1\n");
			fprintf(out, "STR R2, R6, #0\n");
			break;
		case GE:
			fprintf(out, "LDR R2, R6, #0\n");
			fprintf(out, "LDR R1, R6, #1\n");
			fprintf(out, "CMP R2, R1\n");
			fprintf(out, "BRzp g%d\n", (*labels)++);
			fprintf(out, "CONST R2, #0\n");
			fprintf(out, "JMP g%d\n", (*labels)--);
			fprintf(out, "g%d\n", (*labels)++);
			fprintf(out, "CONST R2, #1\n");
			fprintf(out, "g%d\n", (*labels)++);
			fprintf(out, "ADD R6, R6, #1\n");
			fprintf(out, "STR R2, R6, #0\n");
			break;
		case GT:
			fprintf(out, "LDR R2, R6, #0\n");
			fprintf(out, "LDR R1, R6, #1\n");
			fprintf(out, "CMP R2, R1\n");
			fprintf(out, "BRp g%d\n", (*labels)++);
			fprintf(out, "CONST R2, #0\n");
			fprintf(out, "JMP g%d\n", (*labels)--);
			fprintf(out, "g%d\n", (*labels)++);
			fprintf(out, "CONST R2, #1\n");
			fprintf(out, "g%d\n", (*labels)++);
			fprintf(out, "ADD R6, R6, #1\n");
			fprintf(out, "STR R2, R6, #0\n");
			break;
		case LT:
			fprintf(out, "LDR R2, R6, #0\n");
			fprintf(out, "LDR R1, R6, #1\n");
			fprintf(out, "CMP R2, R1\n");
			fprintf(out, "BRn g%d\n", (*labels)++);
			fprintf(out, "CONST R2, #0\n");
			fprintf(out, "JMP g%d\n", (*labels)--);
			fprintf(out, "g%d\n", (*labels)++);
			fprintf(out, "CONST R2, #1\n");
			fprintf(out, "g%d\n", (*labels)++);
			fprintf(out, "ADD R6, R6, #1\n");
			fprintf(out, "STR R2, R6, #0\n");
			break;
			break;
		case LE:
			fprintf(out, "LDR R2, R6, #0\n");
			fprintf(out, "LDR R1, R6, #1\n");
			fprintf(out, "CMP R2, R1\n");
			fprintf(out, "BRnz g%d\n", (*labels)++);
			fprintf(out, "CONST R2, #0\n");
			fprintf(out, "JMP g%d\n", (*labels)--);
			fprintf(out, "g%d\n", (*labels)++);
			fprintf(out, "CONST R2, #1\n");
			fprintf(out, "g%d\n", (*labels)++);
			fprintf(out, "ADD R6, R6, #1\n");
			fprintf(out, "STR R2, R6, #0\n");
			break;
		case DROP:
			fprintf(out, "ADD R6, R6, #1\n");
			break;
		case DUP:
			fprintf(out, "LDR R2, R6, #0\n");
			fprintf(out, "STR R2, R6, #-1\n");
			fprintf(out, "ADD R6, R6, #-1\n");
			break;
		case SWAP:
			fprintf(out, "LDR R2, R6, #0\n");
			fprintf(out, "LDR R1, R6, #1\n");
			fprintf(out, "STR R1, R6, #0\n");
			fprintf(out, "STR R2, R6, #1\n");
			break;
		case ROT:
			fprintf(out, "LDR R3, R6, #0\n");
			fprintf(out, "LDR R4, R6, #1\n");
			fprintf(out, "LDR R2, R6, #2\n");
			fprintf(out, "STR R2, R6, #0\n");
			fprintf(out, "STR R4, R6, #2\n");
			fprintf(out, "STR R3, R6, #1\n");
			break;
		case ARG:
			fprintf(out, "LDR R7, R5, #%d\n", token->arg_no + 2);
			fprintf(out, "STR R7, R6, #-1\n");
			fprintf(out, "ADD R6, R6, #-1\n");
			break;
		case LITERAL:
			fprintf(out, "ADD R6, R6, #-1\n");
			if (token->literal_value > 255 || token->literal_value < -256) {
				short bot = (unsigned short int) token->literal_value % 256;
				fprintf(out, "CONST R2, #%d\n", bot);
				short top = (unsigned short int) token->literal_value / 256;
				fprintf(out, "HICONST R2, #%d\n", top);
			}
			else {
				fprintf(out, "CONST R2, #%d\n", token->literal_value);
			}
			fprintf(out, "STR R2, R6, #0\n");
			break;
		default:
			exit(1);
		}	
	}
