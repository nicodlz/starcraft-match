#if defined(_MSC_VER)
#define NI __declspec(noinline)
#define ST __stdcall
#else
#define NI __attribute__((noinline))
#define ST __attribute__((stdcall))
#endif
#define D(p,o) (*(unsigned int *)((unsigned char *)(p)+(o)))
#define W(p,o) (*(short *)((unsigned char *)(p)+(o)))
static NI unsigned int ST sub_004BFA80(unsigned int count, unsigned char *unit, unsigned int *items)
{
 unsigned int best=0, distance=0x7fffffffu;
 if(count) {
  unsigned int remaining=count;
  do {
   unsigned int candidate=*items;
   if(candidate) {
    unsigned char *other=(unsigned char *)D(candidate,12);
    unsigned char *own=(unsigned char *)D(unit,12);
    int dx=(int)W(other,20)-(int)W(own,20);
    int dy=(int)W(other,22)-(int)W(own,22);
    unsigned int squared=(unsigned int)dy*(unsigned int)dy+(unsigned int)dx*(unsigned int)dx;
    if(squared<distance) { *items=best;best=candidate;distance=squared; }
   }
   ++items;
  } while(--remaining);
 }
 return best;
}
unsigned int context_004BFA80(unsigned int n,unsigned char *u,unsigned int *a) { return sub_004BFA80(n,u,a); }
