/* Reviewed i386 reference conversions; opaque fields retain their observed widths. */
#define SC_SHARED_ENCODE_COMPONENT
#include "sub_00479EC0.c"
extern u8 g_0064B2E8[];
#pragma code_seg(".link")
static u32 pack_link(u32 p) {if(!p)return 0;return (p-(u32)g_0064B2E8)/112u+1u;}
#pragma code_seg(".record")
__declspec(noinline) static void __stdcall sub_0048A9A0(u8 *node,u32 links) {
 sub_00479EC0(node);
 *(u32*)(node+100)=encode_unit(*(u8**)(node+100));
 *(u32*)(node+104)=encode_unit(*(u8**)(node+104));
 if(links) {*(u32*)node=pack_link(*(u32*)node);*(u32*)(node+4)=pack_link(*(u32*)(node+4));}
}
#pragma code_seg(".anchor")
void __stdcall compiler_anchor_0048A9A0(u8 *node,u32 links) {sub_0048A9A0(node,links);}
