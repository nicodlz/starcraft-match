#if defined(_MSC_VER)
#define SC_STDCALL __stdcall
#else
#define SC_STDCALL __attribute__((stdcall))
#endif
unsigned int SC_STDCALL sub_004288E0(const unsigned char *value) {
    unsigned char field = value[0xC8];
    return field != 0x2C;
}
