#if defined(_MSC_VER)
#define SC_FASTCALL __fastcall
#else
#define SC_FASTCALL __attribute__((fastcall))
#endif
unsigned int SC_FASTCALL sub_00447090(unsigned int player) {
    unsigned int offset = player * 0x4E8u;
    unsigned int *timer = (unsigned int *)(0x00690110u + offset);
    unsigned int started = *timer;
    unsigned int limit;
    unsigned int elapsed;
    unsigned int expired;
    if (!started) return 0;
    limit = (*(const unsigned char *)(0x00690100u + offset) & 0x20) ? 180u : 120u;
    elapsed = *(const unsigned int *)0x0058D6F8u - started;
    expired = elapsed >= limit;
    if (expired) *timer = 0;
    return expired;
}
