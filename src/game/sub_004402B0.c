#if defined(_MSC_VER)
#define SC_FAST __fastcall
#else
#define SC_FAST __attribute__((fastcall))
#endif
unsigned int SC_FAST sub_004402B0(const unsigned char *first,const unsigned char *second){const unsigned char *node;if(first[0x4c]==second[0x4c] && (*(const unsigned char *)(0x664080u+(unsigned int)*(const unsigned short *)(first+0x64)*4u)&8u)!=0 && (first[0xdc]&0x40u)==0){node=*(const unsigned char *const volatile *)(first+0x134);if(node){node=*(const unsigned char *const volatile *)(node+0x14);node=*(const unsigned char *const volatile *)(node+0x28);return node==first;}}return 0;}
