#if defined(_MSC_VER) && !defined(__clang__)
#define SC_FASTCALL __fastcall
#else
#define SC_FASTCALL __attribute__((fastcall))
#endif

unsigned int SC_FASTCALL sub_0047B770(const unsigned char *node) {
 unsigned short id=*(const unsigned short*)(node+0x64);
 unsigned int flags=((const unsigned int*)0x664080u)[id];
 if(flags&1) return 0;
 if(flags&0x800) return 0;
 if(*(const unsigned int*)(node+0xDC)&0x400) return 0;
 if(node[0x117]) return 0;
 if(node[0x119]) return 0;
 if(node[0x124]) return 0;
 if(id>=203 && id<=213) return 0;
#if defined(_MSC_VER) && !defined(__clang__)
 if(id==13 || id==36 || id==89 || id==90 || id==95 || id==94 || id==93 || id==96 || id==202 || id==105) return 0;
#else
 {
  volatile unsigned short portable_id = id;
  if(portable_id == 13) return 0;
  if(portable_id == 36) return 0;
  if(portable_id == 89) return 0;
  if(portable_id == 90) return 0;
  if(portable_id == 95) return 0;
  if(portable_id == 94) return 0;
  if(portable_id == 93) return 0;
  if(portable_id == 96) return 0;
  if(portable_id == 202) return 0;
  if(portable_id == 105) return 0;
 }
#endif
 return 1;
}
