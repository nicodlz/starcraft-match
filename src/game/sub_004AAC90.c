typedef unsigned char u8;
typedef unsigned short u16;
struct node { u8 pad[4]; struct node *next; u8 pad2[64]; u8 a; u8 b; u16 c; };
static __declspec(noinline) void *sub_004AAC90(u8 a, u8 b, u16 c)
{
    struct node *p = *(struct node **)0x0051a270;
    if ((int)p > 0) do {
        if (p->a == a && p->b == b && p->c == c)
            return &p->a;
        p = p->next;
        if ((int)p <= 0) break;
    } while (p);
    return (void *)0;
}
void *context_004AAC90(u8 a, u8 b, u16 c)
{
    return sub_004AAC90(a, b, c);
}
