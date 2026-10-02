typedef unsigned int U32;
typedef unsigned char U8;
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
extern void __fastcall sub_004E1BC0(U8 *object,U8 *event);
#pragma code_seg(".scmatch")
static NOINLINE void sub_004908E0(U8 *object,U8 *event)
{
    int type;
    U32 owner,node,table;
    U8 index;
    sub_004E1BC0(object,event);
    type=*(short *)(object+0x20);
    switch(type) {
    case 3: *(U8 *)0x0063FF70=9; return;
    case 2: *(U8 *)0x0063FF70=8; return;
    case 1:
        owner=*(U32 *)(object+0x32);
        if (*(unsigned short *)(owner+0x22U)) owner=*(U32 *)(owner+0x32U);
        node=*(U32 *)(owner+0x42U);
        if (node) do {
            if (*(unsigned short *)(node+0x20U)==4) goto found;
            node=*(U32 *)node;
        } while(node);
        node=0;
found:
        index=*(U8 *)(node+0x46U) ? *(U8 *)(node+0x48U) : 255U;
        table=*(U32 *)(node+0x42U);
        *(U8 *)0x0063FF70=*(U8 *)(table+index*4U);
    }
}
#pragma code_seg(".scctx")
void context_004908E0(U8 *object,U8 *event) { sub_004908E0(object,event); }
