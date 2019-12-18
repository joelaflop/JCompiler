#include <stdbool.h>


typedef struct elt_tag {
  int num;
  struct elt_tag *prev;
} elt;

typedef struct {
  elt *top;
} stack;

void init (stack *s);
void push (stack *s, int num);
int pop (stack *s);
void clear (stack *s);
