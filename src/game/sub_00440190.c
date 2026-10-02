#if defined(_MSC_VER)
#define SC_FAST __fastcall
#else
#define SC_FAST __attribute__((fastcall))
#endif
unsigned int SC_FAST sub_00440190(const unsigned char *unit,unsigned int criterion){if((*(const volatile unsigned int *)(unit+0xdc)&0x400u)!=0 && (unsigned int)unit[0x4c]==criterion)return 1;return 0;}
