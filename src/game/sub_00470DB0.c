#if defined(_MSC_VER)
#define STDCALL __stdcall
#else
#define STDCALL __attribute__((stdcall))
#endif
extern unsigned char *STDCALL sub_0041006A(unsigned int, const char *, unsigned int, unsigned int);
#if defined(_MSC_VER)
#pragma code_seg(".scmatch")
#else
#define MATCH_SECTION __attribute__((section(".scmatch")))
#endif
#ifndef MATCH_SECTION
#define MATCH_SECTION
#endif
MATCH_SECTION void STDCALL sub_00470DB0(unsigned char first, unsigned char second)
{
    unsigned char *buffer = *(unsigned char **)0x006d5c8c;
    if (!buffer) {
        buffer = sub_0041006A(3, (const char *)0x0050467c, 0x369, 0);
        *(unsigned char **)0x006d5c8c = buffer;
    }
    buffer[0] = 0x45;
    buffer[1] = first;
    buffer[2] = second;
}
