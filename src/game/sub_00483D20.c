typedef unsigned int U32;
typedef unsigned short U16;
#ifdef _MSC_VER
#define NI __declspec(noinline)
#else
#define NI __attribute__((noinline))
#endif
extern void sub_0042BC30(void);
#pragma code_seg(".scmatch")
static NI void sub_00483D20(const U32 *source)
{
 int width,rows;
 U16 *destination;
 sub_0042BC30();
 rows=*(U16 *)0x0057F1D6;
 width=*(U16 *)0x0057F1D4;
 destination=(U16 *)(*(U32 *)0x006D5BFC+12u);
 while(rows>0) {
  int count=width;
  while(count>0) {
   U32 flags=*source;
   if(flags&0x410000u) {
    U32 category=flags&0x6010000u;
    U32 value;
    if(category) {
     if(category!=0x2010000u) value=0x1FFAu+(category!=0x4010000u);
     else value=0x1FF9;
    } else value=0x1FFD;
    *destination=(U16)value;
   } else *destination=0x1FFD;
   ++source; ++destination; --count;
  }
  destination+=256-(int)width;
  --rows;
 }
}
#pragma code_seg(".scctx")
void hypothetical_context(const U32 *source) { sub_00483D20(source); }
