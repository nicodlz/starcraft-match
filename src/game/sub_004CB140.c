#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
typedef unsigned int U32;
typedef struct Node { U32 value; void *item; U32 second; struct Node *previous, *next; } Node;
extern void *STDCALL sub_0041006A(U32 size, const char *file, U32 line, U32 flags);
#pragma code_seg(".scmatch")
static NOINLINE Node *STDCALL sub_004CB140(Node *tail, void *item, U32 second, U32 value)
{
    Node *node;
    if (!item) return tail;
    node = (Node *)sub_0041006A(20, (const char *)0x0050292C, 0x2F9, 0);
    node->value = value;
    node->item = item;
    node->second = second;
    node->previous = tail;
    node->next = 0;
    if (tail) tail->next = node;
    return node;
}
#pragma code_seg(".scctx")
Node *STDCALL context_004CB140(Node *tail, void *item, U32 second, U32 value)
{ return sub_004CB140(tail,item,second,value); }
