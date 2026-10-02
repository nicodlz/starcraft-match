typedef unsigned char U8;
typedef unsigned short U16;
typedef signed short S16;
typedef unsigned long U32;
#define B(p,o) (*(volatile U8*)((U32)(p)+(o)))
#define W(p,o) (*(volatile U16*)((U32)(p)+(o)))
extern U8 *__fastcall sub_0047B230(U32 handle);
extern void __stdcall sub_0049AB00(long x,long y,U8 *node,U16 type,U8 byte9,U8 byte10);
#if defined(__clang__)
#define NOINLINE __attribute__((noinline))
#else
#define NOINLINE __declspec(noinline)
#endif
#pragma code_seg(".scmatch")
static NOINLINE void sub_004C2320(U8 *packet)
{
 U16 x,y;
 x=W(packet,1);
 if(x>=W(0x628450,0))return;
 y=W(packet,3);
 if(y>=W(0x6284b4,0))return;
 sub_0049AB00((S16)x,(S16)y,sub_0047B230(W(packet,5)),W(packet,7),B(packet,9),B(packet,10));
}
#pragma code_seg(".scctx")
void context_004C2320(U8 *packet){sub_004C2320(packet);}
