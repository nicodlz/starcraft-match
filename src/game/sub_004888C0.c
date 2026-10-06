typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#define B(a) (*(volatile u8 *)(a))
#define W(a) (*(volatile u16 *)(a))
#define D(a) (*(volatile u32 *)(a))
#pragma code_seg(".h8c0")
static __declspec(noinline) u32 __stdcall sub_004888C0(u8 category,u8 player) {
 switch(category) {
 case 0:return D(0x582174u+(u32)player*4);
 case 1:return D(0x582204u+(u32)player*4);
 case 2:return D(0x582294u+(u32)player*4);
 default:return 0;
 }
}

#pragma code_seg(".context")
u32 __stdcall context_004888C0(u8 category,u8 player) {return sub_004888C0(category,player);}
