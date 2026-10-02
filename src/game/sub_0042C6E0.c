#if defined(_MSC_VER)
#define FASTCALL __fastcall
#else
#define FASTCALL __attribute__((fastcall))
#endif

unsigned int FASTCALL sub_0042C6E0(const unsigned char *condition) {
    unsigned int mode=condition[0x0e];
    unsigned int threshold=*(const unsigned int *)(condition+8);
    switch(mode) {
    case 0:
        return *(const unsigned int *)0x0058D6F8u>=threshold;
    case 1:
        return threshold>=*(const unsigned int *)0x0058D6F8u;
    case 10:
        return *(const unsigned int *)0x0058D6F8u==threshold;
    default:
        return 0u;
    }
}
