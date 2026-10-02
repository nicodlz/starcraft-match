#ifdef _MSC_VER
#define FAST __fastcall
#else
#define FAST __attribute__((fastcall))
#endif
unsigned long FAST sub_00484DF0(unsigned long unused, unsigned char value)
{
 unsigned char *p=(unsigned char *)0x0057F008;
 (void)unused;
 do {
  unsigned char key=p[-34];
  p-=36;
  if(key==value) {
   unsigned char kind=*p;
   if(kind==1 || kind==5) return 1;
  }
 } while(p!=(unsigned char *)0x0057EEE8);
 return 0;
}
