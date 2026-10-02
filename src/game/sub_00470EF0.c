typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;
#ifdef _MSC_VER
#define NI __declspec(noinline)
#else
#define NI __attribute__((noinline))
#endif
extern void *__stdcall sub_0041006A(U32,const char *,U32,U32);
#pragma code_seg(".scmatch")
static NI void sub_00470EF0(U32 index)
{
 U32 slot=((U32 *)0x0057EEE4)[index*9u];
 if(slot<8u) {
  U16 x,y,z;
  U32 record_index;
  if(!((U8 **)0x006D5C50)[slot]) ((U8 **)0x006D5C50)[slot]=(U8 *)sub_0041006A(8,(const char *)0x0050467C,0x18A,0);
  ((U8 **)0x006D5C50)[slot][0]=0x3F;
  record_index=(U32)(U8)slot*34u;
  x=0; y=0; z=0;
  if(((const U8 *)0x0066FE20)[record_index]==1) {
   x=*(const U16 *)((const U8 *)0x0066FE22+record_index);
   y=*(const U16 *)((const U8 *)0x0066FE24+record_index);
   z=*(const U16 *)((const U8 *)0x0066FE26+record_index);
  }
  ((U8 **)0x006D5C50)[slot][1]=(U8)slot;
  *(U16 *)(((U8 **)0x006D5C50)[slot]+2)=x;
  *(U16 *)(((U8 **)0x006D5C50)[slot]+4)=y;
  *(U16 *)(((U8 **)0x006D5C50)[slot]+6)=z;
 }
}
#pragma code_seg(".scctx")
void hypothetical_context(U32 index) { sub_00470EF0(index); }
