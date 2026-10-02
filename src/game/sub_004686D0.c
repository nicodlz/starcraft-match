typedef unsigned int u32;
struct Node {
    unsigned char untouched[0xD0];
    u32 state;
    struct Node *previous;
    struct Node *next;
};
typedef char check_u32[(sizeof(u32) == 4) ? 1 : -1];
typedef char check_pointer[(sizeof(void *) == 4) ? 1 : -1];
typedef char check_node_size[(sizeof(struct Node) == 0xDC) ? 1 : -1];
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
static NOINLINE void STDCALL sub_004686D0(struct Node *node, struct Node *owner)
{
    if (node->previous)
        node->previous->next = node->next;
    else
        owner->previous = node->next;
    if (node->next)
        node->next->previous = node->previous;
    node->previous = 0;
    node->next = 0;
    node->state = 0;
}
/* Compiler context only: this helper is not an original reconstructed function. */
void context_004686D0(struct Node *node, struct Node *owner)
{
    sub_004686D0(node, owner);
}
