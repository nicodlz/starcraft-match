typedef unsigned char u8;
unsigned int __fastcall sub_0045A920(u8 value)
{
    unsigned int cursor = 0x0057f008;
    unsigned int previous;
    goto next;
scan:
    if (*(u8 *)(cursor + 2) == value && *(u8 *)cursor == 5)
        return 1;
next:
    previous = cursor;
    cursor -= 36;
    if (previous != 0x0057eee8)
        goto scan;
    return 0;
}
