#if defined(_MSC_VER)
#define SC_FAST __fastcall
#else
#define SC_FAST __attribute__((fastcall))
#endif
unsigned int SC_FAST sub_00453DC0(const unsigned char *unit,unsigned int criterion){return *(const unsigned short *)(unit+0x64)==criterion;}
