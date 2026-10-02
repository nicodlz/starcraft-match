/* Independent C reconstruction for the pinned i386 target. */
typedef char widths_00436C10[(sizeof(unsigned)==4 && sizeof(short)==2 && sizeof(void*)==4)?1:-1];
#if defined(_MSC_VER)
#define ABI __stdcall
#else
#define ABI __attribute__((stdcall))
#endif
unsigned ABI sub_00436C10(unsigned player,unsigned short region)
{
 unsigned char *table=*(unsigned char**)0x6D5BFCu;
 unsigned char *area=table+0x449FCu+(unsigned)region*64;
 unsigned short *next=*(unsigned short**)(area+12);
 int count=(int)area[7]-(int)*(signed char*)(area+33);
 unsigned char *base;
 if(count) {
  base=((unsigned char**)0x69A604u)[player];
  do {
   unsigned char *item=base+(unsigned)*next*52;
   --count; ++next;
   if(item[5]==3 || *(unsigned*)(item+28) || *(unsigned*)(item+32) || (item[8]&32))return 0;
  } while(count);
 }
 return 1;
}
