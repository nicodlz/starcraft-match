typedef unsigned int u32;
#ifdef _MSC_VER
#define NI __declspec(noinline)
#else
#define NI __attribute__((noinline))
#endif
extern void *__stdcall sub_0041006A(u32,const char *,u32,u32);
void *__cdecl memset(void *,int,u32);
#if defined(_MSC_VER) && !defined(__clang__)
#pragma intrinsic(memset)
#endif
#pragma code_seg(".scmatch")
static NI void sub_00436A80(u32 count) {
 u32 size=count*52u;
 u32 i;
 for(i=0;i<32u;i+=4u) {
  void *p=sub_0041006A(size,(const char *)0x00505630,0x191u,0u);
  *(void **)(0x0069A604u+i)=p;
  memset(p,0,size);
 }
}
#pragma code_seg(".scctx")
void hypothetical_context(u32 count) { sub_00436A80(count); }
