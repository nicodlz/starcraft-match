#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 STDCALL sub_0041008E(void *,const void *,u32);
#pragma code_seg(".scmatch")
static NOINLINE int sub_004ED3F0(u8 *object) {
 u32 index=object[0x48];
 u8 *node;
 if(index==255) goto missing;
 node=*(u8 * volatile *)0x0051A228;
 if((int)node<=0) goto missing;
 do {
  if(index--==0) goto found;
  node=*(u8 **)(node+4);
  if((int)node<=0) goto missing;
 } while(node);
missing:
 return 0;
found:
 if(!node) goto missing;
 *(volatile u16 *)0x0066FF30=0;
 sub_0041008E((void *)0x0057EE9C,node+0x14,25);
 return 1;
}
#pragma code_seg(".scctx")
int context_004ED3F0(u8 *p) {return sub_004ED3F0(p);}
