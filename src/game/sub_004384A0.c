/* Independently authored complete body; ordinary context selects private ABI. */
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
#if defined(_MSC_VER)
#define STDCALL __stdcall
#define NI __declspec(noinline)
#else
#define STDCALL __attribute__((stdcall))
#define NI __attribute__((noinline))
#endif
extern u8 ** STDCALL sub_00430B50(u32 region);
#pragma code_seg(".scmatch")
static NI u32 sub_004384A0(u32 region,u32 player,u32 kind)
{
    u8 **list = sub_00430B50(region);
    u32 found = 0;
    while (*list) {
        if (*(u16 *)(*list + 0x64) == kind && (*list)[0x4c] == player) {
            found = 1;
            break;
        }
        ++list;
    }
    {
        u32 depth = *(u32 *)0x006bee6c - 1u;
        *(u32 *)0x006bee6c = depth;
        *(u32 *)0x006bee64 = *(u32 *)(0x006bee70u + depth * 4u);
    }
    return found;
}
#pragma code_seg(".scctx")
u32 compilation_context(u32 region,u32 kind,u32 player)
{
    return sub_004384A0(region,player,kind);
}
