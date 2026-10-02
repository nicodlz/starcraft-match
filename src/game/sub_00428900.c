#if defined(_MSC_VER)
#define FASTCALL __fastcall
#else
#define FASTCALL __attribute__((fastcall))
#endif

unsigned int FASTCALL sub_00428900(unsigned int ignored_ecx,
                                 unsigned int ignored_edx,
                                 const unsigned char *object) {
    unsigned char value=object[0xc9];
    return value!=0x3d;
}
