typedef unsigned char u8;
typedef unsigned int u32;
#define B(a) (*(volatile u8 *)(u32)(a))
#define D(a) (*(volatile u32 *)(u32)(a))
#pragma code_seg(".helper")
__declspec(noinline) u32 __fastcall sub_004D4B20(u32 unused,u32 input) {
 u32 index=8,value;u32 cursor=0x0051299c;
 do {value=D(cursor-20);cursor-=20;--index;if(input==value)return index;}while(cursor!=0x005128fc);
 return 0;
}
