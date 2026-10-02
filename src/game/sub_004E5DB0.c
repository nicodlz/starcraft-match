/* Independent C reconstruction for the pinned i386 target. */
typedef char widths_004E5DB0[(sizeof(unsigned)==4 && sizeof(short)==2 && sizeof(void*)==4)?1:-1];
#if defined(_MSC_VER)
#define LEAF static __declspec(noinline)
#else
#define LEAF static __attribute__((noinline))
#endif
LEAF unsigned sub_004E5DB0(const unsigned char *unit)
{
 unsigned shift=unit[76];
 unsigned char *target=*(unsigned char*const*)(unit+92);
 unsigned mask=1u<<shift;
 if(target) {
  unsigned flags=*(unsigned*)(target+220);
  if((flags&0x300u) && !(*(unsigned*)(target+228)&mask))return 0;
  return (*(unsigned char**)(target+12))[12] & (unsigned char)mask;
 } else {
  int y=*(const short*)(unit+90)/32;
  unsigned width=*(unsigned short*)0x57F1D4u;
  int x=*(const short*)(unit+88)/32;
  unsigned *grid=*(unsigned**)0x6D1260u;
  return ~(grid[y*width+x]&255u)&mask;
 }
}
unsigned probe_004E5DB0(const unsigned char *unit){return sub_004E5DB0(unit);}
