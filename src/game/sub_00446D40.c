/* Pinned i386 ABI: index in EAX, selector in CL; EDX is unused. */
#if defined(__i386__)
#define SC_REG_ARGS __attribute__((regparm(3)))
#else
#define SC_REG_ARGS
#endif
SC_REG_ARGS void sub_00446D40(unsigned int index, unsigned int unused_edx,
                            unsigned int selector)
{
    volatile unsigned char *flags =
        (volatile unsigned char *)(0x00690100u + index * 0x4E8u);
    (void)unused_edx;
    if ((selector & 0xFFu) == 4)
        *flags |= 0x80u;
    else
        *flags &= 0x7Fu;
}
