static __declspec(noinline) unsigned sub_004E5AD0(unsigned char *object)
{
    unsigned char *position = *(unsigned char **)(object + 0xc);
    int x = *(short *)(position + 0x14) / 32;
    int y = *(short *)(position + 0x16) / 32;
    int left = *(volatile unsigned short *)0x0057F1D0;
    int top;
    if (x + 2 < left ||
        y + 2 < (top = *(volatile unsigned short *)0x0057F1D2) ||
        x > left + 22 || y > top + 15)
        return 1;
    return 0;
}
unsigned context_004E5AD0(unsigned char *object)
{
    return sub_004E5AD0(object);
}
