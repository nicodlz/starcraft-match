#ifdef _MSC_VER
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
typedef unsigned int u32;
#define PTR(p,o) (*(unsigned char **)((p)+(o)))
static NOINLINE void sub_004371D0(unsigned char *node, unsigned char *owner)
{
    unsigned char *q;
    unsigned char *pool;
    if (!(PTR(node,0x0c)[0xdc] & 4))
        --*(unsigned short *)(owner+0x0a);
    if (PTR(owner,0x30) == node)
        PTR(owner,0x30) = PTR(node,0);
    q = PTR(node,4);
    if (q) PTR(q,0) = PTR(node,0);
    q = PTR(node,0);
    if (q) PTR(q,4) = PTR(node,4);
    pool = PTR(owner,0x2c);
    PTR(node,4) = 0;
    PTR(node,0) = PTR(pool,0x4e20);
    q = PTR(pool,0x4e20);
    if (q) PTR(q,4) = node;
    PTR(pool,0x4e20) = node;
}
void context_004371D0(unsigned char *node,unsigned char *owner) { sub_004371D0(node,owner); }
