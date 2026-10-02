typedef unsigned int U32;
#if defined(_MSC_VER)
#define SC __stdcall
#define NI __declspec(noinline)
#else
#define SC __attribute__((stdcall))
#define NI __attribute__((noinline))
#endif
extern void SC sub_00410070(U32,const char *,U32,U32);
#pragma code_seg(".scmatch")
static NI void SC sub_0047AB40(U32 *array,volatile int count)
{
 int length=count;
 if(length>0) {
  U32 next=1u;
  U32 *slot=array;
  U32 remaining=(U32)length;
  do {
   if(*slot) {
    U32 j;
    for(j=next;(int)j<length;++j) if(*slot==array[j]) array[j]=0;
    sub_00410070(*slot,(const char *)0x0050463C,0x14D,0);
    length=count;
    *slot=0;
   }
   ++next;
   ++slot;
  } while(--remaining);
 }
}
#pragma code_seg(".scctx")
void SC context_0047AB40(U32 *array,int count) { sub_0047AB40(array,count); }
#pragma code_seg()
