#if defined(_MSC_VER)
#define NI __declspec(noinline)
#define SC __stdcall
#else
#define NI __attribute__((noinline))
#define SC __attribute__((stdcall))
#endif
typedef unsigned int u32;
extern void * SC dependency_0041006A(u32 size,const char *file,u32 line,u32 flags);
typedef struct { u32 active,unknown; void *buffer; u32 cursor,size,used,sentinel,other; } Object;
#pragma code_seg(".scmatch")
static NI Object *sub_004CDF50(Object *p)
{
    p->size=50000;
    p->buffer=dependency_0041006A(50000,(const char *)0x0050286C,334,0);
    p->cursor=0;
    p->used=0;
    p->sentinel=0xffffffffu;
    p->active=1;
    p->other=0;
    return p;
}
#pragma code_seg(".scctx")
Object *context(Object *p) { return sub_004CDF50(p); }
