#if defined(_MSC_VER)
#define SC_NOINLINE __declspec(noinline)
#else
#define SC_NOINLINE __attribute__((noinline))
#endif
typedef struct Node { struct Node *next,*previous; } Node;
#if defined(_MSC_VER)
#define SC_OFFSET(type, member) ((unsigned int)&(((type *)0)->member))
#else
#define SC_OFFSET(type, member) __builtin_offsetof(type, member)
#endif
typedef char sc_link_offset[(sizeof(void *) != 4 || SC_OFFSET(Node, previous) == 4) ? 1 : -1];

static SC_NOINLINE void sub_0049DE00(Node *p) {
    Node *neighbor;
    if(*(Node **)0x00628438u==p)
        *(Node **)0x00628438u=p->previous;
    if(*(Node **)0x0062843cu==p)
        *(Node **)0x0062843cu=p->next;
    neighbor=p->next;
    if(neighbor) neighbor->previous=p->previous;
    neighbor=p->previous;
    if(neighbor) neighbor->next=p->next;
    p->next=0;
    p->previous=0;
}
/* Source-only compiler context, not a reconstructed game function. */
void source_context_0049DE00(Node *p) { sub_0049DE00(p); }
