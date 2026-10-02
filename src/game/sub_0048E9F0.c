#if defined(_MSC_VER)
#define SC_FASTCALL __fastcall
#else
#define SC_FASTCALL __attribute__((fastcall))
#endif
unsigned int SC_FASTCALL sub_0048E9F0(unsigned char *value) {
    value[0x87] = 0x64;
    return 0;
}
