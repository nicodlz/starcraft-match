#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
typedef int I32;
extern int sub_00409CBE(const char *a, const char *b);
#pragma code_seg(".scmatch")
static NOINLINE I32 sub_004A6A30(const char *name)
{
    I32 head = *(I32 *)0x0051A27C;
    I32 node = head > 0 ? head : 0;
    while (node > 0) {
        if (sub_00409CBE((const char *)((unsigned int)node + 0x269u), name) == 0)
            return node;
        if (!node) node = 0x0051A278;
        node = *(I32 *)((unsigned int)node + 4u);
    }
    return 0;
}
#pragma code_seg(".scctx")
I32 context_004A6A30(const char *name) { return sub_004A6A30(name); }
