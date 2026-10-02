/* Independently reconstructed from the reviewed pinned PE region. */
#if defined(_MSC_VER) && !defined(__clang__)
#define SUB004401B0_LEAF static __declspec(noinline)
#else
#define SUB004401B0_LEAF __attribute__((noinline, regparm(1)))
#endif

SUB004401B0_LEAF unsigned int sub_004401B0(unsigned int index)
{
    unsigned int *row = (unsigned int *)(0x00695610 + index * 64);
    unsigned int count = ((const unsigned int *)0x006955EC)[index];
    unsigned int value;
    if (count == 1)
        return row[0];
    value = *(const unsigned int *)0x006D11C8;
    if (!value)
        return row[0u % count];
    {
        unsigned int next = *(unsigned int *)0x0051C65C + 1;
        ++*(unsigned int *)0x0051CA18;
        value = *(unsigned int *)0x0051CA14 * 0x015A4E35 + 1;
        *(unsigned int *)0x0051CA14 = value;
        value >>= 16;
        *(unsigned int *)0x0051C65C = next;
        value &= 0x7FFF;
    }
    return row[value % count];
}

/* Noncounted ordinary C compiler context; not a reconstructed game caller. */
unsigned int shape_call_004401B0(unsigned int index)
{
    return sub_004401B0(index);
}
