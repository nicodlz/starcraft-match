/* EDX low-word input; the fastcall ECX slot is ignored and needs no setup. */
#if defined(_MSC_VER)
#define SC_FASTCALL __fastcall
#elif defined(__i386__)
#define SC_FASTCALL __attribute__((fastcall))
#else
#define SC_FASTCALL
#endif

char *SC_FASTCALL sub_004BD0C0(unsigned int unused_ecx, unsigned int id)
{
    const unsigned short *table;
    unsigned short index;
    table = *(const unsigned short **)0x005993D4u;
    if (!table)
        return 0;
    index = (unsigned short)(id - 1u);
    if (!(unsigned short)id)
        return 0;
    if (index >= *table)
        return (char *)0x00501B7Du;
    return (char *)table + table[(unsigned int)index + 1u];
}
