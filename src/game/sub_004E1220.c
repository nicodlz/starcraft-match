__attribute__((regparm(1))) void sub_004E1220(unsigned char *p) {
    unsigned short x = *(volatile unsigned short *)(p+4);
    *(volatile unsigned short *)(p+0x36) += x;
    *(volatile unsigned short *)(p+0x3a) += x;
    unsigned short y = *(volatile unsigned short *)(p+6);
    *(volatile unsigned short *)(p+0x38) += y;
    *(volatile unsigned short *)(p+0x3c) += y;
    unsigned int flags = *(volatile unsigned int *)(p+0x18);
    unsigned char value = (unsigned char)(flags >> 20) & 0x77;
    *(volatile unsigned int *)(p+0x2e)=0x004E1120;
    *(volatile unsigned char *)(p+0x4e)=value;
    *(volatile unsigned short *)(p+0x3e)=0;
}
