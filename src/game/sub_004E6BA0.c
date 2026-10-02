#if defined(_MSC_VER)
#define SC_FAST __fastcall
#else
#define SC_FAST __attribute__((fastcall))
#endif
unsigned int SC_FAST sub_004E6BA0(const unsigned char *unit){unsigned short type;if(*(const volatile unsigned int *)(unit+0xdc)&0x40000000u)return 0;type=*(const unsigned short *)(unit+0x64);if(type==0x2a && *(const volatile unsigned char *)(0x58d2c8u+(unsigned int)unit[0x4c]*46u)==0)return 0;return *(const volatile unsigned char *)(0x660988u+(unsigned int)type)!=0;}
