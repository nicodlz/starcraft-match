#if defined(_MSC_VER)
#define NI __declspec(noinline)
#define FC __fastcall
#else
#define NI __attribute__((noinline))
#define FC __attribute__((fastcall))
#endif
typedef unsigned int u32;
typedef unsigned char u8;
extern void FC dependency_00474400(u8 *,u8);
#pragma code_seg(".scmatch")
static NI u8 *sub_00468970(u8 *owner)
{
    u8 *current=*(u8 **)(owner+0xd4);
    u8 *found=(u8 *)0;
    while(current) {
        if (!(*(u32 *)(current+0xdc)&0x400) && !current[0x117] && !current[0x119] && !current[0x124] && (current[0x4d]==0x52 || current[0x4d]==0x56)) found=current;
        current=*(u8 **)(current+0xd8);
    }
    if(found) {
        u8 *prev=*(u8 **)(found+0xd4);
        if(prev) *(u8 **)(prev+0xd8)=*(u8 **)(found+0xd8);
        else *(u8 **)(owner+0xd4)=*(u8 **)(found+0xd8);
        current=*(u8 **)(found+0xd8);
        if(current) *(u8 **)(current+0xd4)=*(u8 **)(found+0xd4);
        *(u32 *)(found+0xd4)=0;
        *(u32 *)(found+0xd8)=0;
        *(u32 *)(found+0xd0)=0;
        dependency_00474400(found,0x59);
    }
    return found;
}
#pragma code_seg(".scctx")
u8 *context(u8 *owner) { return sub_00468970(owner); }
