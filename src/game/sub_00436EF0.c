#if defined(_MSC_VER)
#define FASTCALL __fastcall
#else
#define FASTCALL __attribute__((fastcall))
#endif

unsigned int FASTCALL sub_00436EF0(const unsigned char *object) {
    return *(const unsigned short *)(object + 0x64) == 0x20;
}
