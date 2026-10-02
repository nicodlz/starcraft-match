#if defined(_MSC_VER)
#define SC_STDCALL __stdcall
#else
#define SC_STDCALL __attribute__((stdcall))
#endif
unsigned int SC_STDCALL sub_00436B10(unsigned int player) {
    unsigned int offset = (unsigned int)(unsigned char)player * 4;
    unsigned int first = *(const unsigned int *)(0x005855F4u + offset);
    unsigned int second = *(const unsigned int *)(0x005868E4u + offset);
    unsigned int third = *(const unsigned int *)(0x00585504u + offset);
    return first + second * 2u + third;
}
