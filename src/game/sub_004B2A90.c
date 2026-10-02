/* Independently reconstructed from the reviewed pinned PE region. */
#if defined(_MSC_VER) && !defined(__clang__)
#define SUB004B2A90_FAST __fastcall
#else
#define SUB004B2A90_FAST __attribute__((fastcall))
#endif

unsigned int SUB004B2A90_FAST sub_004B2A90(unsigned int *object,
                                        unsigned int index)
{
    const unsigned int *table_57f150 = (const unsigned int *)0x0057F150;
    const unsigned int *table_57f180 = (const unsigned int *)0x0057F180;
    const unsigned int *table_57f120 = (const unsigned int *)0x0057F120;
    const unsigned int *table_57f0f0 = (const unsigned int *)0x0057F0F0;
    unsigned int total;
    unsigned int net;

    object[0x19c / 4] = table_57f150[index];
    object[0x1a0 / 4] = table_57f180[index];
    total = table_57f150[index] + table_57f180[index];
    net = total - table_57f120[index] - table_57f0f0[index];
    object[0x24c / 4] = total;
    net = (int)net < 0 ? 0 : net;
    object[0x1a4 / 4] = net;
    return net;
}
