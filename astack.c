#include <stdlib.h>
#include "string.h"
#include "def.h"
#include <stdio.h>

struct Astack_node newANode()
{
    struct Astack_node *stackNode = (struct Astack_node *)malloc(sizeof(struct Astack_node));
    stackNode->num_objs = 0;
    stackNode->ret_addr = 0;
    stackNode->call_oid = 0;
    stackNode->local_mem = NULL;
    stackNode->objects = NULL;
    //stackNode->vec_elems = NULL;
    return *stackNode;
}

int isAFull(struct Astack *astack)
{
    return astack->top == astack->capacity - 1;
}

void apush(struct Astack *astack, struct Ostack *objects, int call_oid ,struct data_mem *local_mem,int num_objs, int ret_addr)
{
    struct Astack_node stackNode = newANode();
    stackNode.objects = objects;
    stackNode.call_oid = call_oid;
    stackNode.num_objs = num_objs;
    stackNode.ret_addr = ret_addr;
    stackNode.local_mem = local_mem;
    //stackNode.vec_elems = vec_elems;

    if (isAFull(astack)) {
        fprintf(stderr, "FATAL ERROR: Activation Stack Overflow\n");
        exit(-1);
    }

    astack->stack[++astack->top] = stackNode;

}

int isAEmpty(struct Astack *astack)
{
    return astack->top == -1;
}

struct Astack *createAStack(unsigned capacity)
{
    struct Astack *stack = (struct Astack *)malloc(sizeof(struct Ostack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->stack = (struct Astack_node *)malloc(stack->capacity * sizeof(struct Astack_node));
    return stack;
}

struct Astack_node apop(struct Astack *astack)
{
    if (isAEmpty(astack)) {
        fprintf(stderr, "FATAL ERROR: Empty activation Stack (Invalid APOP)\n");
        exit(-1);
    }

    return astack->stack[astack->top--];
}

struct Astack_node apeek(struct Astack *astack)
{
    if (isAEmpty(astack))
    {
        fprintf(stderr, "FATAL ERROR: Empty Activation Stack (Invalid APEEK)\n");
        exit(-1);
    }
    return astack->stack[astack->top];
}