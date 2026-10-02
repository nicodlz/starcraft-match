#if defined(_MSC_VER)
#define SC_FASTCALL __fastcall
#else
#define SC_FASTCALL __attribute__((fastcall))
#endif
unsigned int SC_FASTCALL sub_00432320(unsigned int player) {
    const unsigned char *node = *(const unsigned char * const *)(0x006AA054u + player * 8u);
    unsigned int result = 0;
    while (node) {
        unsigned char cluster = node[0x1C];
        if (cluster) {
            unsigned int index = cluster;
            unsigned int amount;
            if (!index || index >= 0xFAu) amount = 0;
            else amount = ((const unsigned char *)0x0069268Cu)[index * 0x30u];
            result += amount;
        }
        node = *(const unsigned char * const *)node;
    }
    return result;
}
