/* EDX input; complete 1,000-record pointer restoration with DWORD wrapping. */
typedef unsigned int U32;
typedef unsigned char U8;
typedef struct Unit {U8 opaque[336];} Unit;
typedef char sc_dword_width[(sizeof(U32)==4)?1:-1];
typedef char sc_unit_stride[(sizeof(Unit)==336)?1:-1];
extern Unit g_0059CCA8[];

#pragma code_seg(".unit")
static U32 unpack_unit(U32 value) {return value?(U32)&g_0059CCA8[(value&0x7FFu)-1u]:0;}
#pragma code_seg(".link")
static U8 *unpack_link(U32 value,U8 *base) {if(!value)return 0;return base+value*32u-32;}
#pragma code_seg(".pool")
void __fastcall sub_00402FB0(U32 unused,U8 *block) {
 U32 *fields=(U32*)(block+4);U32 count=1000;
 do {
  fields[2]=unpack_unit(fields[2]);
  fields[-1]=(U32)unpack_link(fields[-1],block);
  fields[0]=(U32)unpack_link(fields[0],block);
  fields+=8;
 }while(--count);
 *(U32*)(block+32000)=(U32)unpack_link(*(U32*)(block+32000),block);
}
