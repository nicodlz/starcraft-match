#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
typedef unsigned int u32;typedef struct Bound {u32 value;} Bound;typedef unsigned char u8;
extern u32 g_0051CA18;
#pragma code_seg(".leaf")
static NOINLINE u32 STDCALL sub_004DC550(u32 tag,u32 low,Bound high) {
 u32 random,state;
 if(*(u32*)0x006D11C8u==0u)random=0;
 else {
  ++*(u32*)(0x0051C610u+tag*4u);
  ++g_0051CA18;
  state=*(u32*)0x0051CA14u*0x015A4E35u+1u;
  random=(state>>16)&0x7fffu;
  *(u32*)0x0051CA14u=state;
 }
 return (((high.value-low+1u)*random)>>15)+low;
}
#pragma code_seg(".ctxl")
u32 STDCALL context_004DC550(u32 tag,u32 low,u32 high){Bound bound;bound.value=high;return sub_004DC550(tag,low,bound);}
