/*
 * stack.c
 */

#include "stack.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


void init (stack *s){
	s->top = NULL;
}

void push (stack *s, int num){
	elt *e = malloc(sizeof(e)*2);
	e->num = num;
	e->prev = s->top;
	s->top = e;
}

int pop (stack *s){
	elt *e;
	e = s->top;
	int popped = e->num;
	if (!s->top->prev) {
		s->top = NULL;
	} else {
		s->top = e->prev;
	}
	free(e);
	return popped;
}

void clear (stack *s){
	while (s->top)
    	pop (s);
}
