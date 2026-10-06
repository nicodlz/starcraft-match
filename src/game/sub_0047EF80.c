/* Whole prioritized BYTE-input / unsigned-DWORD comparison selector. */
typedef unsigned char u8;
typedef unsigned int u32;
extern u8 g_00658AC0;
extern u32 g_00658ABC,g_0062848C,g_00658AA0,g_006284A8;
extern u8 g_00596A39[];
#pragma code_seg(".select")
static __declspec(noinline) void __stdcall sub_0047EF80(u32 *second,u32 *first) {
 u8 mode=g_00658AC0;
 *first=0;*second=0;
 if(mode) {
  if(g_00658ABC<g_0062848C)*second=0xffffffffu;
  else if(g_00658ABC>g_0062848C)*second=1;
  if(g_00658AA0<g_006284A8)*first=0xffffffffu;
  else if(g_00658AA0>g_006284A8)*first=1;
  return;
 }
 if(g_00596A39[0x42] || g_00596A39[1]) {*first=1;*second=1;return;}
 if(g_00596A39[0x40] || g_00596A39[2]) {*first=1;*second=0xffffffffu;return;}
 if(g_00596A39[0x46] || g_00596A39[3]) {*first=0xffffffffu;*second=0xffffffffu;return;}
 if(g_00596A39[0x48] || g_00596A39[0]) {*first=0xffffffffu;*second=1;return;}
 if(g_00596A39[7] || g_00596A39[0x41])*first=1;
 else if(g_00596A39[5] || g_00596A39[0x47])*first=0xffffffffu;
 if(g_00596A39[6] || g_00596A39[0x45])*second=1;
 else if(g_00596A39[4] || g_00596A39[0x43])*second=0xffffffffu;
}
#pragma code_seg(".context")
void __stdcall context_0047EF80(u32 *first,u32 *second) {sub_0047EF80(second,first);}
