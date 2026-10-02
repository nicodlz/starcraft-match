#if defined(_MSC_VER)
#define SC_FAST __fastcall
#else
#define SC_FAST __attribute__((fastcall))
#endif
unsigned int SC_FAST sub_00440220(const unsigned char *first,const unsigned char *second){if(*(const unsigned short *)(first+0x64)==0x7d && first[0x4c]==second[0x4c])return 1;return 0;}
