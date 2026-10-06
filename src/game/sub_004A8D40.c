typedef unsigned long u32;
typedef unsigned char u8;
#define D(a) (*(volatile u32 *)(u32)(a))
#define B(a) (*(volatile u8 *)(u32)(a))
extern volatile u32 g_0057EEC0[8],g_0057EE7C[8];
#pragma code_seg(".helper")
__declspec(noinline) static void __stdcall sub_004A8D40(u32 selected) {
 int offset;u32 cursor,index,name;
 D(0x00512684)=0xffffffff;D(0x00512688)=0xffffffff;offset=0;index=8;
 do {offset-=4;*(volatile u32 *)((volatile u8 *)&g_0057EEC0+32+offset)=8;*(volatile u32 *)((volatile u8 *)&g_0057EE7C+32+offset)=8;}while(offset!=-32);
 cursor=0x0057F004;
 do {
  u8 kind=B(cursor-32);cursor-=36;--index;
  if(kind==2) {
   name=D(cursor);D(0x0057EEC0+name*4)=index;D(0x0057EE7C+name*4)=index;
   if(name==selected){D(0x00512684)=index;D(0x00512688)=index;}
  }
 }while(cursor!=0x0057EEE4);
}

#pragma code_seg(".anchor")
u32 compiler_anchor_004A8D40(u32 selected){sub_004A8D40(selected);return selected+1;}
