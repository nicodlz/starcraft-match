#if defined(_MSC_VER)
#define SC_FASTCALL __fastcall
#else
#define SC_FASTCALL __attribute__((fastcall))
#endif
typedef struct Sub0041D7D0View {
    short field_00;
    unsigned short reserved_02;
    unsigned int field_04;
} Sub0041D7D0View;
unsigned int SC_FASTCALL sub_0041D7D0(unsigned int ignored_ecx, unsigned int height, unsigned int x, unsigned int y) {
    Sub0041D7D0View *view = *(Sub0041D7D0View * const *)0x006CF4A8u;
    unsigned int address = (unsigned int)((int)view->field_00 * (int)(unsigned short)y);
    unsigned int count;
    unsigned char color;
    (void)ignored_ecx;
    address += view->field_04;
    address += (unsigned int)(int)(short)x;
    if ((unsigned short)height > 0) {
        count = (unsigned short)height;
        color = *(const unsigned char *)0x006CF4ACu;
        do {
            *(unsigned char *)address = color;
            address += (unsigned int)(int)view->field_00;
        } while (--count);
    }
    return address;
}
