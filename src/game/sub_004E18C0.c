#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
static NOINLINE unsigned char *sub_004E18C0(unsigned char *root) {
 unsigned short initial=*(unsigned short *)(root+34);
 unsigned char *current=root;
 for(;;) {
  unsigned char *head=root; unsigned char *p; unsigned short wanted;
  if(initial) head=*(unsigned char **)(root+50);
  p=*(unsigned char **)(head+66);
  if(!p) return current;
  wanted=*(unsigned short *)(current+32)-1;
  while(p) { if(*(unsigned short *)(p+32)==wanted) break; p=*(unsigned char **)p; }
  if(!p) return current;
  if(*(unsigned short *)(p+34)!=3) return current;
  current=p;
 }
}
unsigned char *context(unsigned char *root) {unsigned char *r=sub_004E18C0(root); return r==root?root:r;}
