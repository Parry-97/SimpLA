#include <stdlib.h>
#include "string.h"
#include "def.h"
#include <stdio.h>

struct Ostack_node newONode()
{
    struct Ostack_node *stackNode = (struct Ostack_node *)malloc(sizeof(struct Ostack_node));
    stackNode->size = 0;
    stackNode->val.ival = 0;
    return *stackNode;
}

struct Ostack *createOStack(unsigned capacity)
{
    struct Ostack *stack = (struct Ostack *)malloc(sizeof(struct Ostack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->stack = (struct Ostack_node *)malloc(stack->capacity * sizeof(struct Ostack_node));
    return stack;
}

int isOFull(struct Ostack *stack)
{
    return stack->top == stack->capacity - 1;
}


int opush_batch(struct Ostack *istack, int batch_size) {

    Value val;
    for (int i = 0; i < batch_size; i++)
    {
        opush(istack, val, 1);
    }
    return istack->top - batch_size + 1;
}

void opush(struct Ostack *ostack, Value val, int size)
{
    struct Ostack_node stackNode = newONode();
    stackNode.val = val;
    stackNode.size = size;
    if (isOFull(ostack)) {
        fprintf(stderr,"FATAL ERROR: Object Stack Overflow\n");
        exit(-1);
    }

    ostack->stack[++ostack->top] = stackNode;
    
}

void opush_t(struct Ostack *ostack, Value val, int size, s_type stipo)
{
    struct Ostack_node stackNode = newONode();
    stackNode.val = val;
    stackNode.size = size;
    stackNode.tipo = stipo;

    if (isOFull(ostack))
    {
        fprintf(stderr, "FATAL ERROR: Object Stack Overflow\n");
        exit(-1);
    }

    ostack->stack[++ostack->top] = stackNode;
    
}

int isOEmpty(struct Ostack *stack)
{
    return stack->top == -1;
}

struct Ostack_node opeek(struct Ostack *ostack)
{
    if (isOEmpty(ostack)) {
        fprintf(stderr, "FATAL ERROR: Empty Object Stack(Invalid OPEEK)\n");
        exit(-1);
    }
    return ostack->stack[ostack->top];
}

struct Ostack_node opop(struct Ostack *ostack)
{
    if (isOEmpty(ostack)) {
        fprintf(stderr, "FATAL ERROR: Empty object Stack (Invalid OPOP)\n");
        exit(-1);
    }

    return ostack->stack[ostack->top--];
}