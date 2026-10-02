typedef unsigned char u8; typedef unsigned short u16; typedef unsigned long u32;
#define A(T,N) ((T *)(N))
#ifdef _MSC_VER
#define NI __declspec(noinline)
#define SC __stdcall
#else
#define NI __attribute__((noinline))
#define SC __attribute__((stdcall))
#endif
#define F(T,P,O) (*(T *)((u8*)(P)+(O)))
typedef struct Pair {u32 a,b;} Pair;
void *memset(void*,int,unsigned int);
#if defined(_MSC_VER) && !defined(__clang__)
#pragma intrinsic(memset)
#else
static void *portable_zero_memory_004D5A50(void *destination, int value, unsigned int size) {
 volatile u8 *bytes = (volatile u8 *)destination;
 unsigned int offset;
 for (offset = 0; offset < size; ++offset) bytes[offset] = (u8)value;
 return destination;
}
#define memset portable_zero_memory_004D5A50
#endif
static void zero_pair(Pair *p) {memset(p,0,8);}
static NI void SC sub_004D5A50(void *s,u32 id,void *parent,u8 x,u8 y) {
 u32 *script;
 F(u16,s,8)=(u16)id; F(u32,s,44)=A(u32,0x51ced0)[id]; F(u16,s,12)=0;
 F(u16,s,12) |= (u16)((A(u8,0x66e860)[id]&1)<<3);
 F(u16,s,12)=(u16)((F(u16,s,12)&0xffdf)|((A(u8,0x66c150)[id]&1)<<5));
 F(u16,s,24)=0;F(u8,s,11)=0;F(u16,s,26)=0;F(u8,s,22)=0;F(u32,s,60)=(u32)parent;F(u8,s,14)=x;F(u8,s,15)=y;
 { Pair *q=(Pair*)((u8*)s+36); zero_pair(q); }
 script=(u32*)((u8*)s+48); memset(script,0,4);
 { Pair *q=(Pair*)((u8*)s+16); zero_pair(q); }
 if(A(u8,0x669e28)[F(u16,s,8)]==14) *script=((u8*)parent)[10];
 if(A(u8,0x669e28)[id]==9) *script=A(u32,0x5128fc)[A(u8,0x669a40)[id]*5];
}
void context(void *s,u32 id,void *p,u8 x,u8 y) { sub_004D5A50(s,id,p,x,y); }
