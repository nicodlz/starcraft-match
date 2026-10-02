#if defined(_MSC_VER) && !defined(__clang__)
#define SC_NOINLINE __declspec(noinline)
#else
#define SC_NOINLINE __attribute__((noinline))
#endif

#define ROT(x) (((x)<<3)|((x)>>29))
SC_NOINLINE static unsigned int sub_004E2DA0(const unsigned char *node) {
 unsigned int h=*(const unsigned short*)(node+0x64);
 const unsigned char *sprite;
 h=ROT(h)^*(const unsigned int*)(node+0x60);
 h=ROT(h)^*(const unsigned short*)(node+0xA2);
 sprite=*(const unsigned char*const*)(node+0xC);
 h=ROT(h)^(unsigned int)(int)*(const short*)(sprite+0x14);
 h=ROT(h)^(unsigned int)(int)*(const short*)(sprite+0x16);
 h=ROT(h)^(unsigned int)(((int)(*(const unsigned int*)(node+8)+255u))>>8);
 return ROT(h);
}
unsigned int anchor004E2DA0(const unsigned char *node) { return sub_004E2DA0(node); }

#undef ROT
