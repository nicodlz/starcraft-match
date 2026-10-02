#if defined(_MSC_VER)
#define SC_FASTCALL __fastcall
#else
#define SC_FASTCALL __attribute__((fastcall))
#endif
int SC_FASTCALL sub_00494F90(const unsigned char *object) {
    unsigned int speed = *(const unsigned int *)(object + 0x3C);
    if (speed != 0 && object[0x27] == 0) {
        unsigned int id = *(const unsigned short *)(object + 0x24);
        if (speed == ((const unsigned int *)0x006C9EF8u)[id] &&
            *(const unsigned short *)(object + 0x48) == ((const unsigned short *)0x006C9C78u)[id])
            return ((const int *)0x006C9930u)[id];
        return (int)(speed * speed) / (2 * (int)*(const unsigned short *)(object + 0x48));
    }
    return 0;
}
