/* Pinned 1.16.1 leaf: byte index in AL, zero-extended result in EAX. */
unsigned int __attribute__((regparm(1))) sub_004A8B90(unsigned char index)
{
    if (index >= 8)
        return 0;
    return ((const volatile unsigned char *)0x0059BDA8u)[index];
}
