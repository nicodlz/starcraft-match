#if defined(_MSC_VER)
#define NI __declspec(noinline)
#define CD __cdecl
#else
#define NI __attribute__((noinline))
#define CD
#endif
#if defined(_MSC_VER) && !defined(__clang__)
void * CD memcpy(void *,const void *,unsigned int);
#pragma intrinsic(memcpy)
#endif
static NI unsigned int sub_00436D80(unsigned char *state)
{
 unsigned char snapshot[2500];
 unsigned int changed;
 unsigned int index;
#if defined(_MSC_VER) && !defined(__clang__)
 memcpy(snapshot,state,2500);
#else
 for(index=0;index<2500u;++index)
  ((volatile unsigned char *)snapshot)[index]=((const volatile unsigned char *)state)[index];
#endif
 changed=0;index=0;
 do {
  if(snapshot[index]>=5) {
   unsigned char *region=(unsigned char *)*(volatile unsigned int *)0x006D5BFCu + 0x449FCu + (unsigned short)index*64u;
   unsigned short *neighbors=*(unsigned short * volatile *)(region+12);
   int difference=(int)*(volatile unsigned char *)(region+7)-(int)*(volatile signed char *)(region+33);
   if(difference) {
    unsigned int count=(unsigned int)difference;
    do {
     unsigned char *target=state+*neighbors;
     unsigned char value=*target;
     ++neighbors;
     if(value==1) { *target=2; changed=1; }
     else if(value==0) { *target=6; changed=1; }
    } while(--count);
   }
  }
  ++index;
 } while(index<2500u);
 return changed;
}
unsigned int context_00436D80(unsigned char *state) { return sub_00436D80(state); }
