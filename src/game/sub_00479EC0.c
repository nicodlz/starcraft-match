/* Reviewed i386 reference conversions; opaque fields retain their observed widths. */
typedef unsigned int u32;
typedef unsigned char u8;
extern u8 g_0059CCA8[],g_00629D98[];
#pragma code_seg(".unit")
static __forceinline u32 encode_unit(u8 *p) {
 u32 index;
 if (!p) return 0;
 index=((u32)p-(u32)g_0059CCA8)/336u+1;
 if(index>1700) return 0;
 return ((u32)p[0xa5]<<11)|index;
}
#pragma code_seg(".sprite")
static __forceinline u32 encode_sprite(u8 *q) {if(!q)return 0;return ((u32)q-(u32)g_00629D98)/36u+1;}
#pragma code_seg(".encode")
static __declspec(noinline) void sub_00479EC0(u8 *p) {
 u32 out,q;
 *(u32 *)(p+0x5c)=encode_unit(*(u8 **)(p+0x5c));
 out=encode_unit(*(u8 **)(p+0x14));
 q=*(u32 *)(p+0xc);
 *(u32 *)(p+0x14)=out;
 *(u32 *)(p+0xc)=encode_sprite((u8 *)q);
}

#ifndef SC_SHARED_ENCODE_COMPONENT
#pragma code_seg(".anchor")
u32 compiler_anchor_00479EC0(u8 *p) {sub_00479EC0(p);return *(u32 *)(p+0x64);}
#endif
