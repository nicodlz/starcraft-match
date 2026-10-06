typedef unsigned int u32;
typedef unsigned short u16;
#pragma code_seg(".class")
static __declspec(noinline) u32 __stdcall sub_0046ED80(u16 kind) {
 switch(kind) {
 case 14:case 85:case 105:case 202:case 205:case 206:case 207:case 208:return 1;
 default:return 0;
 }
}
#pragma code_seg(".cctx")
u32 __stdcall context_0046ED80(u32 kind,u32 n) {
 u32 result=0;while(n--)result+=sub_0046ED80(kind++);return result;
}
