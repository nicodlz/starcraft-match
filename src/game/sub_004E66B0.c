typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#define B(a) (*(volatile u8 *)(u32)(a))
#define W(a) (*(volatile u16 *)(u32)(a))
#define D(a) (*(volatile u32 *)(u32)(a))
#pragma code_seg(".helper2")
__declspec(noinline) static u32 __stdcall sub_004E66B0(u32 unit) {
 u32 other;
 if(B(unit+0xa6)==37 && (B(unit+0xdc)&2) && (other=D(unit+0xec)) && !(B(other+0xdc)&1))return 1;
 return 0;
}
#pragma code_seg(".anchor")
u32 compiler_anchor_004E66B0(u32 unit) {return sub_004E66B0(unit);}
