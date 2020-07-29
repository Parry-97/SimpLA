#include <stdlib.h>
#include "string.h"
#include "def.h"

struct Astack_node newANode()
{
    struct Astack_node *stackNode = (struct Astack_node *)malloc(sizeof(struct Astack_node));
    stackNode->num_objs = 0;
    stackNode->ret_addr = 0;
    stackNode->objects = NULL;
    return *stackNode;
}

int isAFull(struct Astack *astack)
{
    return astack->top == astack->capacity - 1;
}

void apush(struct Astack *astack, struct Ostack *objects, int num_objs, int ret_addr)
{
    struct Astack_node stackNode = newANode();
    stackNode.objects = objects;
    stackNode.num_objs = num_objs;
    stackNode.ret_addr = ret_addr;

    if (isAFull(astack)) {
        fprintf(stderr, "Activation Stack Overflow\n");
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
        fprintf(stderr, "Empty activation Stack\n");
        exit(-1);
    }

    return astack->stack[astack->top--];
}

struct Astack_node apeek(struct Astack *astack)
{
    if (isAEmpty(astack))
    {
        fprintf(stderr, "Empty Activation Stack\n");
        exit(-1);
    }
    return astack->stack[astack->top];
}