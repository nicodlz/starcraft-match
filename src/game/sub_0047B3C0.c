#if defined(_MSC_VER)
#define SC_STDCALL __stdcall
#else
#define SC_STDCALL __attribute__((stdcall))
#endif
#define SC_BYTE(address) (*(unsigned char *)(address))
typedef char Sub0047B3C0ShortWidth[sizeof(unsigned short) == 2 ? 1 : -1];

int SC_STDCALL sub_0047B3C0(void *ignored, unsigned short identifier,
                           unsigned char marker, unsigned char player)
{
    if (marker) {
        unsigned char value;
        if (identifier < 24)
            value = SC_BYTE(0x58CF44 + 24 * player + identifier);
        else
            value = SC_BYTE(0x58F128 + 20 * player + identifier);
        if (!value) {
            if (identifier < 24)
                SC_BYTE(0x58CF44 + 24 * player + identifier) = 1;
            else if (SC_BYTE(0x58F440))
                SC_BYTE(0x58F128 + 20 * player + identifier) = 1;
        }
    }
    return 1;
}
