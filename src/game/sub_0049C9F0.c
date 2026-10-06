/* Reviewed complete121byte leaf: ECX y, EDI x, AX result. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 *g_006D5BFC;
#pragma code_seg(".helper")
static __declspec(noinline) u16 __stdcall sub_0049C9F0(int y,int x) {
 u16 index=*(u16*)(g_006D5BFC+12+2*(256*(y/32)+x/32));
 if(index>=8192){
  u16 *record=(u16*)(g_006D5BFC+0x1400c+6*(u32)index);
  u16 bit=(u16)(((y/8)&3)*4);bit+=(u16)((x/8)&3);
  if(record[0]&(1u<<bit))return record[2];
  return record[1];
 }
 return index;
}
#pragma code_seg(".context")
u32 __stdcall context_0049C9F0(int y,int x,u32 n) {
 u32 value=0;while(n--)value+=sub_0049C9F0(y++,x);return value;
}
