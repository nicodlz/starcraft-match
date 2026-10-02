#if defined(_MSC_VER)
#define SC_FAST __fastcall
#else
#define SC_FAST __attribute__((fastcall))
#endif
unsigned int SC_FAST sub_004C5520(const unsigned char *action)
{
    unsigned char mode;
    unsigned char label;
    mode = *(const volatile unsigned char *)(action + 0x1A);
    *(volatile unsigned short *)0x0065097Cu = 1;
    if (mode == 0x12 || mode == 0x22) {
        label = *(const volatile unsigned char *)action;
        if (label == 0 || label > 255) return 1;
        --label;
        *(volatile unsigned char *)0x0058D70Du = label;
    } else if (mode == 0x28) {
        *(volatile unsigned char *)0x0058D70Cu = mode;
        *(volatile unsigned int *)0x0058D710u = *(const volatile unsigned int *)(action + 0x14);
        *(volatile unsigned short *)0x0058D70Eu = 2;
        return 1;
    }
    *(volatile unsigned char *)0x0058D70Cu = *(const volatile unsigned char *)(action + 0x1A);
    *(volatile unsigned short *)0x0058D70Eu = *(const volatile unsigned short *)(action + 0x18);
    *(volatile unsigned int *)0x0058D710u = *(const volatile unsigned int *)(action + 0x14);
    *(volatile unsigned int *)0x0058D714u = *(const volatile unsigned int *)(action + 4);
    return 1;
}
