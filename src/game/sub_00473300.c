typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
extern int g_0066FF7C[];
extern int g_006769BC[];
#define DWORD(p,o) (*(u32 *)((p)+(o)))
/* Pinned MSVC/i386 SHL masks the runtime BYTE shift count; see private note. */
#pragma code_seg(".root")
static __declspec(noinline) u32 __stdcall sub_00473300(u8 **list, u8 *source, int x, int y, u8 allow, u8 hidden) {
    u8 *unit=*list;
    while(unit) {
        u32 blocked=source && (DWORD(unit,0xdc)&0x300) && !(DWORD(unit,0xe4)&(1u<<source[0x4c]));
        if ((allow || !(DWORD(unit,0xdc)&0x20000)) && unit!=source &&
            !(unit[0xdc]&6) && *(u16 *)(unit+0x64)!=0xca && *(u16 *)(unit+0x64)!=0x69 &&
            (!blocked || hidden) && !((*(u8 **)(unit+0xc))[0xe]&0x20) &&
            g_0066FF7C[DWORD(unit,0x13c)*2] < (int)((u32)x*32u+32u) &&
            g_0066FF7C[DWORD(unit,0x140)*2] > (int)((u32)x*32u) &&
            g_006769BC[DWORD(unit,0x144)*2] < (int)((u32)y*32u+32u) &&
            g_006769BC[DWORD(unit,0x148)*2] > (int)((u32)y*32u))
            return blocked ? 1 : 4;
        unit=*++list;
    }
    return 0;
}
#pragma code_seg(".anchor")
u32 __stdcall compiler_anchor_00473300(u8 **list, u8 *source, int x, int y, u8 allow, u8 hidden) {
    return sub_00473300(list,source,x,y,allow,hidden);
}
