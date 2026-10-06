/* Complete74-byte leaf: ECX source stride, EDX source, EBX width, stack dst/height. */
typedef unsigned char u8;
typedef unsigned int u32;
#pragma code_seg(".helper")
static __declspec(noinline) void __stdcall sub_0047EA60(u8 *destination,u32 source_stride,const u8 *source,u32 width,u32 height) {
 u32 source_skip=source_stride-width;
 u32 destination_skip=640-width;
 while(height) {
  u32 count=width;
  while(count) {
   if(*destination==0)*destination=*source;
   ++destination;++source;--count;
  }
  destination+=destination_skip;source+=source_skip;
  --height;
 }
}
#pragma code_seg(".context")
void __stdcall context_0047EA60(u32 source_stride,const u8 *source,u32 width,u8 *destination,u32 height) {
 sub_0047EA60(destination,source_stride,source,width,height);
}
