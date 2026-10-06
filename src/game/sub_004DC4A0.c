typedef unsigned int u32;
extern u32 g_006D11C8;
extern u32 g_0051C610[];
extern u32 g_0051CA18;
extern u32 g_0051CA14;
#pragma code_seg(".random")
static __declspec(noinline) u32 __stdcall sub_004DC4A0(u32 index) {
 if(!g_006D11C8)return 0;
 ++g_0051C610[index];
 ++g_0051CA18;
 g_0051CA14=g_0051CA14*0x015a4e35u+1;
 return (g_0051CA14>>16)&0x7fff;
}
#pragma code_seg(".rctx")
u32 __stdcall context_004DC4A0(u32 index){return sub_004DC4A0(index);}
