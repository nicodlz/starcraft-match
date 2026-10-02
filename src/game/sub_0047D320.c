typedef struct node { unsigned long unknown[2]; struct node *next; struct node *prev; unsigned char a; unsigned char b; } node;
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
static NOINLINE void sub_0047D320(node *p)
{
    unsigned long hash = (17UL * p->b + p->a) & 1023UL;
    node **head = (node **)(0x00658B10UL + 4UL * hash);
    if (p == *head) *head = p->next;
    if (p->next) p->next->prev = p->prev;
    if (p->prev) p->prev->next = p->next;
    p->next = 0;
    p->prev = 0;
}
node * experiment_context(node *p)
{
    sub_0047D320(p);
    return p;
}
