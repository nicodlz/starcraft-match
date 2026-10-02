#if defined(_MSC_VER)
#define SC_004381D0_FASTCALL __fastcall
#else
#define SC_004381D0_FASTCALL __attribute__((fastcall))
#endif

/* ECX supplies the object; the DWORD EAX result is zero or one. */
unsigned int SC_004381D0_FASTCALL sub_004381D0(const unsigned char *unit) {
    const unsigned char *state =
        *(const unsigned char * const *)(unit + 0x134);
    if (state && state[8] == 4 &&
        *(const unsigned char * const *)(state + 0x0c) == unit &&
        !(*(const unsigned char *)(0x00664080u +
              4u * (*(const unsigned short *)(unit + 0x64))) & 1))
        return 1;
    return 0;
}
