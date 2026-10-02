static __declspec(noinline) unsigned int sub_004AB050(unsigned int first, unsigned int second)
{
    if (*(unsigned int *)0x006D0F14u != 0) return 1;
    if (*(unsigned char *)(0x0057EEE8u + first * 36u) != 9) {
        if (*(unsigned char *)(0x0057EEE8u + second * 36u) == 9) return 1;
        if (*(unsigned char *)0x00596874u == 1 &&
            *(unsigned char *)0x00596877u == 0) return 1;
    }
    return 0;
}
unsigned int context_004AB050(unsigned int first, unsigned int second)
{
    return sub_004AB050(first, second);
}
