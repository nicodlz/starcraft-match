typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
#pragma code_seg(".update")
static __declspec(noinline) void __stdcall sub_00495240(u8 *p,s32 x,s32 y) {
 if(x!=*(s16*)(p+16)||y!=*(s16*)(p+18)) {
  u8 flags=*(u8*)(p+32);
  u32 packed;
  flags=(flags&0xfb)|1;
  *(u16*)(p+16)=(u16)x;*(u16*)(p+18)=(u16)y;*(u8*)(p+32)=flags;
  packed=*(u32*)(p+16);*(u32*)(p+20)=0;*(u32*)(p+24)=packed;
 }
 if(x!=*(s16*)(p+28)||y!=*(s16*)(p+30)) {
  *(u16*)(p+28)=(u16)x;*(u16*)(p+30)=(u16)y;
 }
}
#pragma code_seg(".uctx")
void __stdcall context_00495240(u8 *p,s32 x,s32 y,u32 n) {
 while(n--)sub_00495240(p,x,y);
}
