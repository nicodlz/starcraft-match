/* Independently reconstructed pointer-link leaf; EAX, EDX, ECX inputs. */
typedef struct Sub0047A070Node {
    struct Sub0047A070Node *next;
    struct Sub0047A070Node *previous;
} Sub0047A070Node;
#if defined(__i386__)
#define SC_EAX_EDX_ECX __attribute__((regparm(3)))
_Static_assert(__builtin_offsetof(Sub0047A070Node, previous) == 4,
               "observed second DWORD slot");
#else
#define SC_EAX_EDX_ECX
#endif

SC_EAX_EDX_ECX void sub_0047A070(Sub0047A070Node *node,
                                Sub0047A070Node **head,
                                Sub0047A070Node *old)
{
    if (*head == old)
        *head = node;
    node->next = old->next;
    node->previous = old;
    /* Retain the second observed read after both stores, including alias cases. */
    Sub0047A070Node *next = *(Sub0047A070Node *volatile *)&old->next;
    if (next)
        next->previous = node;
    old->next = node;
}
