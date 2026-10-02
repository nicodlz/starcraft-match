typedef unsigned char u8;
typedef unsigned long u32;
#if defined(_MSC_VER)
#define SC __stdcall
#define NOINLINE __declspec(noinline)
#else
#define SC __attribute__((stdcall))
#define NOINLINE __attribute__((noinline))
#endif
struct Node { u32 payload, value; u8 *unit; struct Node *previous,*next; };
extern void *SC sub_0041006A(u32,const char *,u32,u32);
#pragma code_seg(".scmatch")
static NOINLINE struct Node *SC sub_004CBEF0(u32 payload,u32 value,u8 *unit,struct Node *previous)
{
    struct Node *result;
    if (*(unsigned short *)(unit+0x64)!=0x86 || !value) return previous;
    result=(struct Node *)sub_0041006A(20,(const char *)0x0050292C,0x2F9,0);
    result->payload=payload;
    result->value=value;
    result->unit=unit;
    result->previous=previous;
    result->next=0;
    if (previous) previous->next=result;
    return result;
}
#pragma code_seg(".scctx")
/* Hypothetical compiler context, excluded from reconstructed target. */
struct Node *SC context(u32 a,u32 b,u8 *u,struct Node *p) { return sub_004CBEF0(a,b,u,p); }
#pragma code_seg()
