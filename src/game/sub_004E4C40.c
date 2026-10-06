typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#define B(a) (*(volatile u8 *)(u32)(a))
#define W(a) (*(volatile u16 *)(u32)(a))
#define D(a) (*(volatile u32 *)(u32)(a))
#pragma code_seg(".helper1")
__declspec(noinline) static u32 __stdcall sub_004E4C40(u32 unit) {
 u32 other;
 if(B(unit+0x4d)==31 && (B(unit+0xdc)&2) && (other=D(unit+0x5c)) && !(B(other+0xdc)&1))return 1;
 return 0;
}
#pragma code_seg(".anchor")
u32 compiler_anchor_004E4C40(u32 unit) {return sub_004E4C40(unit);}
